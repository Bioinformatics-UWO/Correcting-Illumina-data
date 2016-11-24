
//************************************************************
// readSearch searches for exact occurrences of reads in a genome
// compile: > make
// run:     > ./readSearch <genome_file> <original_reads> <corrected_reads>
// <genome_file> must be in fasta format
// read files can be in fasta or fastq format
// !!! reads containing letters not in {A,C,G,T} are assumed NOT FOUND (and not searched for) !!!!
//************************************************************


#ifndef DEBUG
#define DEBUG 0
#endif

#include <iostream>
#include <fstream>
#include <sstream>
#include <math.h>
#include <stdlib.h>
#include <stdint.h>
#include <omp.h>
#include "divsufsort.h"
#include <locale>
#include <iomanip>
using namespace std;


void LongestCommonPrefix(unsigned char* text, int64_t* SA, int64_t genomeLength, int64_t* LCP) // computes LCP
{
	int64_t i=0, j=0;
	int64_t* ISA = new int64_t[genomeLength];
	for (i=0; i<genomeLength; i++) 
		ISA[SA[i]] = i;
	LCP[0] = 0;
	for (i=0; i<genomeLength; i++) // compute LCP[ISA[i]]
	{
		if (ISA[i] != 0) 
		{
			if (i==0) 
				j = 0;
			else 
				j = (LCP[ISA[i-1]] >= 2) ? LCP[ISA[i-1]]-1 : 0;

			while (text[i+j] == text[SA[ISA[i]-1]+j])
				j++;

			LCP[ISA[i]] = j;
		}
	}
	delete[] ISA;

	return;

}
unsigned char ACTGfrom0123[4] = { 'A', 'C', 'T', 'G' }; // +2%4 gives the reverse complement; works also with ACTGto0123
int64_t ACTGto0123(unsigned char a) { // it is the inverse of characters (from main): ACTGfrom0123[ACTGto0123(c)] == c
	switch (a) {
	case 'A': return (0);
	case 'C': return (1);
	case 'T': return (2);
	case 'G': return (3);
	default:  return (4); 
	}
}


void Search(unsigned char* genome, int64_t* genomeSA, int64_t genomeLength, ifstream &readsFile, uint64_t numberOfReads, uint8_t* foundRead, uint64_t longestRead, int* readLengths, bool* uniqueReadArray)
// readLength = 0 if reads of different length, otherwise it stores common length
{
	string read, header, rubbish;
	uint64_t chunkSize = 10000000, lastIteration = 0;
	
	if (numberOfReads < chunkSize)
		chunkSize = numberOfReads;
		
	if(numberOfReads%chunkSize == 0)
		lastIteration = (numberOfReads/chunkSize);
	else
		lastIteration = (numberOfReads/chunkSize)+1;

	// create arrays to store the chunk of reads and their lengths
	char ** readsArray = new char*[chunkSize];
	for (uint64_t i=0; i<chunkSize; ++i)
		readsArray[i] = new char[longestRead];
	

	// loop to find the reads that align to the genome
	for (uint64_t timesThroughLoop=0;  timesThroughLoop < lastIteration; ++timesThroughLoop) 
	{								
		// loop to go through the input in chunks
		for (uint64_t readNumber=0; readNumber < chunkSize; ++readNumber)
		{	if((readNumber + ((timesThroughLoop)*chunkSize)) < numberOfReads)
			{
				getline(readsFile, header);
				getline(readsFile, read);
				
				// store the length of each read into readLengths[]
				readLengths[readNumber + ((timesThroughLoop)*chunkSize)] = read.length();
				 
				// copy the string to readsArray[][]
				for (uint64_t i=0; i<read.length(); i++)
					readsArray[readNumber][i] = read[i];
				
				if (header[0] == '@') { // next two lines are skipped in fastq files
					getline(readsFile, rubbish);
					getline(readsFile, rubbish);
				}
			}
		}
		
		// find which reads in this chunk align to the genome
		#pragma omp parallel
		{
			bool flag = false;
			bool found = false;
			string readRevCompl;
				
			uint64_t hasN = 0, thisReadLength = 0, l = 0, r = genomeLength, Hl = 0, Hr = 0, mid = 0, c = 0, len = 0;
			
			#pragma omp for
			for(uint64_t readNumber=0; readNumber < chunkSize; ++readNumber)
			{	if((readNumber + ((timesThroughLoop)*chunkSize)) < numberOfReads)
				{
					flag = false;
					found = false;
					
					hasN = 0;
					thisReadLength = readLengths[readNumber + ((timesThroughLoop)*chunkSize)];
					
					// check if it has letters not in {A,C,G,T}; if it does, found=0 without searching
					for (uint64_t i=0; i<thisReadLength; ++i)
					{	if (readsArray[readNumber][i] == 'a')
							readsArray[readNumber][i] = 'A';
						if (readsArray[readNumber][i] == 'c')
							readsArray[readNumber][i] = 'C';
						if (readsArray[readNumber][i] == 'g')
							readsArray[readNumber][i] = 'G';
						if (readsArray[readNumber][i] == 't')
							readsArray[readNumber][i] = 'T';
							
						if ((readsArray[readNumber][i] != 'A') && (readsArray[readNumber][i] != 'C') && (readsArray[readNumber][i] != 'G') && (readsArray[readNumber][i] != 'T')) {
							hasN = 1;
							found = false;
			#if DEBUG		
						#pragma omp critical
							cout << "\nread # " << (readNumber + ((timesThroughLoop)*chunkSize)) << " has length = " << thisReadLength << ")\n";
			#endif			
							break;
						}
					}
					
					if (!hasN) {
						
						l = 0;
						Hl = 0;
						Hr = 0;
						mid = 0;
						c = 0;
						r = genomeLength;
						len = genomeLength - genomeSA[l]; //length of suffix
						
						//compare read with the first element in genomeSA
						while (c < min(thisReadLength, len)) {
							if (readsArray[readNumber][c] < genome[genomeSA[l] + c]) {
								flag = true;
								break;
							} else {
								if (readsArray[readNumber][c] > genome[genomeSA[l] + c]) {
									flag = true;
									Hl = c;
									break;
								} else
									c++;
							}
						}
						if (c == thisReadLength) {
							found = true;
							uniqueReadArray[l]=true;
						}
						if (!found) 						
							while (r > l + 1) {
								flag = false;
								mid = (l + r) / 2;
								c = min(Hl, Hr);
								len = genomeLength - genomeSA[mid];
								while (c < min(thisReadLength, len)) {
									if (readsArray[readNumber][c] < genome[genomeSA[mid] + c]) {
										flag = true;
										Hr = c;
										r = mid;
										break;
									} else {
										if (readsArray[readNumber][c] > genome[genomeSA[mid] + c]) {
											flag = true;
											Hl = c;
											l = mid;
											break;
										} else
											c++;
									}
								}
								if (c == thisReadLength) {
									found = true;
									uniqueReadArray[mid]=true;
									break;
								} else if (!flag) {
									Hr = c;
									r = mid;
								}
							}
						
			#if DEBUG	
						#pragma omp critical
							cout << "\nread # " << (readNumber + ((timesThroughLoop)*chunkSize)) << " has length = " << thisReadLength << flush << endl;
						//cout << "\nread: " << read << (found?" ":" NOT ") << "found (length = " << thisReadLength << ")" << flush << endl;
			#endif			
						
						//check reverse complement
						if (!found) { // compute the reverse complement
							readRevCompl = "";
							for (uint64_t ind = 0; ind < thisReadLength; ind++)
								readRevCompl += ACTGfrom0123[(ACTGto0123(readsArray[readNumber][thisReadLength - 1 - ind]) + 2) % 4];
							for (uint64_t i=0; i<thisReadLength; i++)
								readsArray[readNumber][i] = readRevCompl[i];
							
							l = 0; r = genomeLength;
							flag = false; Hl = 0; Hr = 0; c = 0;
							len = genomeLength - genomeSA[l];
							
							//compare read with the first element in genomeSA
							while (c < min(thisReadLength, len)) {
								if (readsArray[readNumber][c] < genome[genomeSA[l] + c]) {
									flag = true;
									break;
								} else {
									if (readsArray[readNumber][c] > genome[genomeSA[l] + c]) {
										flag = true;
										Hl = c;
										break;
									} else
										c++;
								}
							}
							if (c == thisReadLength) {
								uniqueReadArray[l]=true;
								found = true;
							}
							if (!found) 						
								while (r > l + 1) {
									flag = false;
									mid = (l + r) / 2;
									c = min(Hl, Hr);
									len = genomeLength - genomeSA[mid];
									while (c < min(thisReadLength, len)) {
										if (readsArray[readNumber][c] < genome[genomeSA[mid] + c]) {
											flag = true;
											Hr = c;
											r = mid;
											break;
										} else {
											if (readsArray[readNumber][c] > genome[genomeSA[mid] + c]) {
												flag = true;
												Hl = c;
												l = mid;
												break;
											} else
												c++;
										}
									}
									if (c == thisReadLength) {
										found = true;
										uniqueReadArray[mid]=true;
										break;
									} else if (!flag) {
										Hr = c;
										r = mid;
									}
								}
				#if DEBUG	
							#pragma omp critical
							cout << "\nread # " << (readNumber + ((timesThroughLoop)*chunkSize)) << " has length = " << thisReadLength << flush << endl; 
							//cout << "\nreverse complement: " << readRevCompl << (found?" ":" NOT ") << "found (length = " << thisReadLength << ")" << flush << endl;
				#endif
						}
					}
						
					if (found)
						foundRead[readNumber + ((timesThroughLoop)*chunkSize)] = 1;
					else
						foundRead[readNumber + ((timesThroughLoop)*chunkSize)] = 0;
				}
			}
		}
	}
	
	for (uint64_t i=0; i<chunkSize; i++)
		delete [] readsArray[i];
	delete [] readsArray;
}


int main(int argc, char* argv[]) {
	
	if ((argc != 4) && (argc != 3))  {
		cout << "ERROR: Wrong number of arguments!\n";
		cout << "Usage: " << argv[0] << " <genome_file> <originalReads> [ <correctedReads> ]" << endl;
		cout << "<correctedReads> can be missing" << endl;
		exit(EXIT_FAILURE);
	}

	cout.imbue(std::locale(""));
	
	int64_t genomeLength = 0, 
			origReadsFoundBP = 0,  // total number of base pairs in the original reads found in the genome
			origReadsNotFoundBP = 0,  // total number of base pairs in the original reads NOT found in the genome
			origReadsTotalBP = 0,  //  = origReadsFoundBP + origReadsNotFoundBP
			corrReadsFoundBP = 0,  // total number of base pairs in the corrected reads found in the genome
			corrReadsNotFoundBP = 0,  // total number of base pairs in the corrected reads NOT found in the genome
			corrReadsTotalBP = 0,  //  = corrReadsFoundBP + corrReadsNotFoundBP
			genomeNs = 0;	// count how many N's are in the genome
	uint64_t numberOfReads = 0;
	double origCoverage = 0.0, origMeanError = 0.0, corrCoverage = 0.0, corrMeanError = 0.0; 

	time_t t1, t2, start, end;
	time(&start);
	
//***********************************************
// read genome from file and process it *********
//***********************************************

	cout << "\nProcessing genome file ... " << flush;
	time(&t1);

	FILE *pfile = fopen(argv[1], "r");
	if (!pfile) {
		cout << "ERROR: Unable to open text file " << endl;
		exit(EXIT_FAILURE);
	}
	fseek(pfile, 0, SEEK_END); // read file
	genomeLength = ftell(pfile);
	rewind(pfile);
	unsigned char *genome = new unsigned char[genomeLength];
	genomeLength = fread((void *) &genome[0], sizeof(unsigned char),
			genomeLength, pfile);
	fclose(pfile);

// process genome to keep only genomic information (remove description and end_of_lines)

	int64_t i = 0, j = 0, counter=0;
	while (i < genomeLength) {
		if (genome[i] == '>')
			while ((genome[i] != '\r') && (genome[i] != '\n'))
				++i;
		if ((genome[i] == '\r') || (genome[i] == '\n'))
			++i;
		else {
			switch (genome[i]) {
				case 'A': genome[j] = 'A'; break;
				case 'a': genome[j] = 'A'; break;
				case 'C': genome[j] = 'C'; break;
				case 'c': genome[j] = 'C'; break;
				case 'G': genome[j] = 'G'; break;
				case 'g': genome[j] = 'G'; break;
				case 'T': genome[j] = 'T'; break;
				case 't': genome[j] = 'T'; break;
				default:  genome[j] = 'N'; 
			}
			if (genome[j] == 'N')
				genomeNs++;
				
			++j; ++i;
		}
	}
	genome[j] = '\0';
	genomeLength = j;

	cout << "completed (";
	time(&t2);
	cout << difftime(t2,t1) << " seconds)\n"; // time for reading and processing genome
	cout << "Genome length = " << genomeLength << endl;
	cout << "Number of N's in the genome file = " << genomeNs;
	
//***********************************************
// compute suffix array of genome in genomeSA ***
//***********************************************
	
	cout << "\nBuilding suffix array and LCP of genome ... " << flush;

	time(&t1);
	genome[genomeLength] = 'z'; // to make any comparison fail here so that we do not have to check for end of genome
	genomeLength++;
	int64_t* genomeSA = new int64_t[genomeLength];
	int64_t* LCP = new int64_t[genomeLength];
	
	for (i = 0; i < genomeLength; i++)
	{	
		genomeSA[i] = i;
		LCP[i] = 0;
	}
	
	divsufsort(genome, genomeSA, genomeLength); // build suffix array for genome
	LongestCommonPrefix(genome, genomeSA, genomeLength, LCP); // build suffix array for genome
	
	cout << "completed (";
	time(&t2);
	cout << difftime(t2,t1) << " seconds)"; // time for reading and processing genome

//***********************************************
// searching for original reads *****************
//***********************************************
	
	cout << "\nSearching for original reads ... " << flush;
	time(&t1);

	ifstream origReadsFile(argv[2]);
	if (!origReadsFile) {
		cerr << "cannot open file: " << argv[2] << endl;
		exit(0);
	}
	
	// find the number of reads in the original file.	
	uint64_t longestRead = 0, shortestRead = 999999;
	string header, read;
	
	while (!origReadsFile.eof()) 
	{
		getline(origReadsFile, header);
		getline(origReadsFile, read);
		if (read.length() > longestRead)
			longestRead = read.length();
		
		if (read.length() < shortestRead)
			shortestRead = read.length();
			
		if (header[0] == '@') { // next two lines are skipped in fastq files
			getline(origReadsFile, header);
			getline(origReadsFile, read);
		}
		numberOfReads++;
	}
	
	numberOfReads--; // loop above adds 1 too many because it has to process the EOF line
	origReadsFile.clear();
	origReadsFile.seekg(0);
	origReadsFile.clear();
	
	// create arrays to keep track of which reads are found before and after correction and the read lengths.
	uint8_t* foundBefore = new uint8_t[numberOfReads];
	uint8_t* foundAfter = new uint8_t[numberOfReads];
	int* readLengthsOriginal = new int[numberOfReads];
	int* readLengthsCorrected = new int[numberOfReads];
	bool* uniqueReadOriginal = new bool[genomeLength];
	bool* uniqueReadCorrected = new bool[genomeLength];
	for (counter=0;counter<genomeLength;++counter)
	{
		uniqueReadOriginal[counter]=false;
		uniqueReadCorrected[counter]=false;
	}

	Search(genome, genomeSA, genomeLength, origReadsFile, numberOfReads, foundBefore, longestRead, readLengthsOriginal,uniqueReadOriginal);

	origReadsFile.close();
	cout << "completed (";
	time(&t2);
	cout << difftime(t2,t1) << " seconds)\n"; // time for reading and processing genome

	
//***********************************************
// searching for corrected reads ****************
//***********************************************
	if (argc == 4)
	{
		cout << "Searching for corrected reads ... " << flush;
		time(&t1);
		
		ifstream corrReadsFile(argv[3]);
		if (!corrReadsFile) {
			cerr << "cannot open file: " << argv[3] << endl;
			exit(0);
		}
		
		Search(genome, genomeSA, genomeLength, corrReadsFile, numberOfReads, foundAfter, longestRead, readLengthsCorrected,uniqueReadCorrected);
		
		origReadsFile.close();
		cout << "completed (";
		time(&t2);
		cout << difftime(t2,t1) << " seconds)\n"; // time for reading and processing genome
	}
	
//***********************************************
// printing results **********
//***********************************************
		
	uint64_t TP=0, TN=0, FP=0, FN=0, uniqueTN=0, uniqueTP=0, uniqueFP=0, uniqueFN=0, totalUnique=0;
	int64_t readLength;
	
	if (argc == 4)
	{
		/* Calculate the metrics for the reads. */
		for(uint64_t readNumber=0; readNumber < numberOfReads; ++readNumber)
		{
			if(foundBefore[readNumber] == 0 && foundAfter[readNumber] == 1)
			{
				origReadsNotFoundBP += readLengthsOriginal[readNumber];
				if(readLengthsOriginal[readNumber] == readLengthsCorrected[readNumber])
				{	
					corrReadsFoundBP += readLengthsOriginal[readNumber];
					TP += readLengthsOriginal[readNumber];
				}
				else
				{
					FN += readLengthsOriginal[readNumber];
					corrReadsNotFoundBP += readLengthsOriginal[readNumber];
				}
			}
			
			if(foundBefore[readNumber] == 1 && foundAfter[readNumber] == 0)
			{
				FP += readLengthsOriginal[readNumber];
				origReadsFoundBP += readLengthsOriginal[readNumber];
				corrReadsNotFoundBP += readLengthsOriginal[readNumber];
			}
			
			if(foundBefore[readNumber] == 1 && foundAfter[readNumber] == 1)
			{
				origReadsFoundBP += readLengthsOriginal[readNumber];
				if(readLengthsOriginal[readNumber] == readLengthsCorrected[readNumber])
				{
					corrReadsFoundBP += readLengthsOriginal[readNumber];
					TN += readLengthsOriginal[readNumber];
				}
				else
				{
					FP += readLengthsOriginal[readNumber];
					corrReadsNotFoundBP += readLengthsOriginal[readNumber];
				}
			}
			
			if(foundBefore[readNumber] == 0 && foundAfter[readNumber] == 0)
			{
				FN += readLengthsOriginal[readNumber];
				origReadsNotFoundBP += readLengthsOriginal[readNumber];
				corrReadsNotFoundBP += readLengthsOriginal[readNumber];
			}	
		}
	}
	else
	{
		for(uint64_t readNumber=0; readNumber < numberOfReads; ++readNumber)
		{
			if(foundBefore[readNumber] == 0)
				origReadsNotFoundBP += readLengthsOriginal[readNumber];
			else
				origReadsFoundBP += readLengthsOriginal[readNumber];
		}
	}

	origReadsTotalBP = origReadsFoundBP + origReadsNotFoundBP;
	if (argc == 4)
	{
		corrReadsTotalBP = corrReadsFoundBP + corrReadsNotFoundBP;
		
		/* Calculate the metrics for the unique reads. */
		readLength=origReadsTotalBP/numberOfReads;
		for(counter=0;counter<genomeLength;++counter)
		{
			if(uniqueReadOriginal[counter]==true && uniqueReadCorrected[counter]==true)
				++uniqueTN;
			if(uniqueReadOriginal[counter]==false && uniqueReadCorrected[counter]==true)
				++uniqueTP;
			if(uniqueReadOriginal[counter]==true && uniqueReadCorrected[counter]==false)
				++uniqueFP;
			if(LCP[counter]<=(readLength-1))
				++totalUnique;
		}
		uniqueFN = totalUnique-(uniqueTN+uniqueTP+uniqueFP);
	}
	
//***********************************************
// printing results for original reads **********
//***********************************************

	double	x = 0, y = 0;  //for calculating the per base error rate
			// error = 1 - (1 - E/n)^(1/l) 
			// l = read length
			// E = errorneous reads (not found)
			// n = total reads

	origCoverage = (double)origReadsTotalBP/genomeLength;

	y = (double)numberOfReads/origReadsTotalBP;  //  = 1/l
	x = 1 - (double)origReadsNotFoundBP/origReadsTotalBP;  // = 1 - E/n
	origMeanError = (1 - pow(x,y))*100;
	
	
	cout << "\n ======================== Original Reads ======================== \n";
	if (shortestRead == longestRead)
		cout << "                              Read length = " << right << setw(16) << longestRead << endl;
	else 
	{
		cout << "                     Shortest read length = " << right << setw(16) << shortestRead << endl;
		cout << "                      Longest read length = " << right << setw(16) << longestRead << endl;
	}
	
	cout << "                          Number of reads = " << right << setw(16) << numberOfReads << endl;
	cout << "                         Total base pairs = " << right << setw(16) << origReadsTotalBP << endl;
	cout << "                                 Coverage = " << right << setw(16) << origCoverage << endl << endl;

	cout << "              Base pairs in correct reads = " << right << setw(16) << origReadsFoundBP << endl;
	cout << "            Base pairs in erroneous reads = " << right << setw(16) << origReadsNotFoundBP << endl;
	cout << "   Percent of base pairs in correct reads = " << right << setw(15) << (double)100*origReadsFoundBP/origReadsTotalBP << "%" << endl;
	cout << " Percent of base pairs in erroneous reads = " << right << setw(15) << (double)100*origReadsNotFoundBP/origReadsTotalBP << "%" << endl;
	cout << "            Estimated mean per-base error = " << right << setw(15) << origMeanError << "%" << endl;

	if (argc == 4)
	{
		corrCoverage = (double)corrReadsTotalBP/genomeLength;
		
		y = (double)numberOfReads/corrReadsTotalBP;  //  = 1/l
		x = 1 - (double)corrReadsNotFoundBP/corrReadsTotalBP;  // = 1 - E/n
		corrMeanError = (1 - pow(x,y))*100;
			
		cout << "\n ======================= Corrected Reads ======================= \n";
		
		cout << "                         Total base pairs = " << right << setw(16) << corrReadsTotalBP << endl;
		cout << "                                 Coverage = " << right << setw(16) << corrCoverage << endl << endl;
		
		cout << "              Base pairs in correct reads = " << right << setw(16) << corrReadsFoundBP << endl;
		cout << "            Base pairs in erroneous reads = " << right << setw(16) << corrReadsNotFoundBP << endl;
		cout << "   Percent of base pairs in correct reads = " << right << setw(15) << (double)100*corrReadsFoundBP/corrReadsTotalBP << "%" << endl;
		cout << "   Percent of base pairs in correct reads = " << right << setw(15) << (double)100*corrReadsNotFoundBP/corrReadsTotalBP << "%" << endl;
		cout << "            Estimated mean per-base error = " << right << setw(15) << corrMeanError << "%" << endl << endl;
		
		cout << "       Total base pairs that were removed = " << right << setw(16) << origReadsTotalBP - corrReadsTotalBP << endl;
		cout << "  Percent of base pairs that were removed = " << right << setw(15) << (double)100*(origReadsTotalBP - corrReadsTotalBP)/origReadsTotalBP << "%" << endl;
		cout << "      Total base pairs in erroneous reads = " << right << setw(16) << corrReadsNotFoundBP + origReadsTotalBP - corrReadsTotalBP << endl;
		cout << " Percent of base pairs in erroneous reads = " << right << setw(15) << (double)100*(corrReadsNotFoundBP + origReadsTotalBP - corrReadsTotalBP)/origReadsTotalBP << "%"  << endl;

		cout << "\n ========================== Accuracy =========================== \n";
		
		cout << "                        TP = " << right << setw(16) << TP << endl;
		cout << "                        FP = " << right << setw(16) << FP << endl;
		cout << "                        FN = " << right << setw(16) << FN << endl;
		cout << "                        TN = " << right << setw(16) << TN << endl;
		cout << "                      Gain = " << right << setw(15) << (double)100*((int64_t)TP-(int64_t)FP)/((int64_t)TP+(int64_t)FN) << "%" << endl;
		cout << "               Sensitivity = " << right << setw(15) << (double)100*TP/(TP+FN) << "%" << endl;
		cout << "               Specificity = " << right << setw(15) << (double)100*TN/(TN+FP) << "%" << endl;
			
		cout << "\n ======================== Unique Reads ========================= \n";
		cout << "                        TP = " << right << setw(16) << uniqueTP << endl;
		cout << "                        FP = " << right << setw(16) << uniqueFP << endl;
		cout << "                        FN = " << right << setw(16) << uniqueFN << endl;
		cout << "                        TN = " << right << setw(16) << uniqueTN << endl;
		cout << "                      Gain = " << right << setw(15) << (double)100*((int64_t)uniqueTP-(int64_t)uniqueFP)/((int64_t)uniqueTP+(int64_t)uniqueFN) << "%" << endl << endl;

	}	
	time(&end);
	cout << "                Total time = " << difftime(end,start) << " seconds" << endl;
	
	
	return 0;
}
