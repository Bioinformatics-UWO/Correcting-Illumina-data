
//***************************************************************************************************
// kmerSearch searches for k-mer occurrences of reads in a genome
// compile: > make
// run:     > ./kmerSearch <k-mer length> <genome_file> <original_reads> <corrected_reads>
// <genome_file> must be in fasta format.
// <k-mer length> must be between 5 and 32.
// read files can be in fasta or fastq format.
// !!! k-mers in the genome containing letters not in {A,C,G,T} are not stored in the hash table !!!!
// !!! k-mers containing letters not in {A,C,G,T} are assumed NOT FOUND (and not searched for) !!!!
//***************************************************************************************************


#ifndef DEBUG
#define DEBUG 0
#endif

#include <iostream>
#include <fstream>
#include <sstream>
#include <math.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include <string.h>
#include <sys/time.h>
#include <locale>
#include <iomanip>
#include <omp.h>

using namespace std;

int main(int argc, char* argv[]) {
	
	cout.imbue(std::locale(""));
	
	if (argc != 5)  {
		cout << "ERROR: Wrong number of arguments!\n";
		cout << "Usage = " << argv[0] << " <k-mer length> <genome file> <original reads> <corrected reads>" << endl;
		exit(EXIT_FAILURE);
	}
	
	uint64_t kmerLength=atoi(argv[1]);
	if (kmerLength > 32 || kmerLength < 5)  {
		cout << "ERROR: k-mer length must be between 5 and 32.\n";
		exit(EXIT_FAILURE);
	}	

	time_t t_start=0, t_end=0, t_start1=0, t_end1=0;
	uint64_t genomeLength = 0, genomeNs = 0, numChromosomes = 0, i = 0, j = 0;  	

/******************************************************************************************************************
 Read the genome from the file and store it into an array.  Then process the array to remove any characters that 
 are not part of the genome.  N's are kept in the genome array to maintain the genome size.  All letters in the 
 genome are converted to upper-case.
******************************************************************************************************************/

	cout << "*******************************************************************" << endl << flush;
	cout << "*                       Genome File Results                       *" << endl;
	cout << "*******************************************************************" << endl << flush;
	
	/* Read in the genome file and store it in the array. */
	FILE *pfile = fopen(argv[2], "r");
	if (!pfile) {
		cout << "Cannot open the genome file. " << endl;
		exit(EXIT_FAILURE);
	}
	time(&t_start);
	fseek(pfile, 0, SEEK_END);
	genomeLength = ftell(pfile);
	rewind(pfile);
	unsigned char *genome = new unsigned char[genomeLength];
	genomeLength = fread((void *) &genome[0], sizeof(unsigned char), genomeLength, pfile);
	fclose(pfile);

	/* Process genome to keep only the genomic information. */
	while (i < genomeLength) 
	{
		if (genome[i] == '>')
		{
			++numChromosomes;
			while ((genome[i] != '\r') && (genome[i] != '\n'))
				++i;
		}
		
		if ((genome[i] == '\r') || (genome[i] == '\n'))
			++i;
		else 
		{
			switch (genome[i]) 
			{		
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
			// Count the number of N's that appear in the genome file.
			if (genome[j] == 'N')
				genomeNs++;
				
			++j; ++i;
		}
	}
	genome[j] = '\0';
	genomeLength = j;

	cout << "                           Length of the genome = " << right << setw(14) << genomeLength << endl;
	cout << "               Number of N's in the genome file = " << right << setw(14) << genomeNs << endl;
	cout << "       Number of chromosomes in the genome file = " << right << setw(14) << numChromosomes << endl << endl;

/******************************************************************************************************************
 Build the hash table for the genome using the k-mer size provided by the user. k-mers that contain an N are not 
 hashed.  A separate array is used to store the number of times a k-mer appears in the genome, and another array 
 stores the locations that each k-mer begins.
******************************************************************************************************************/
	
	/* Create and initialize array to store hash table sizes. All values are prime numbers. */
	uint64_t hashTableSize[450]={10, 20, 30, 40, 50, 100, 200, 500, 1200, 2500, 1769627, 1835027, 1900667, 1966127, 2031839, 2228483, 2359559, 2490707, 2621447, 2752679, 2883767, 3015527, 3145739, 3277283, 3408323, 3539267, 3670259, 3801143, 3932483, 4063559, 4456643, 4718699, 4980827, 5243003, 5505239, 5767187, 6029603, 6291563, 6553979, 6816527, 7079159, 7340639, 7602359, 7864799, 8126747, 8913119, 9437399, 9962207, 10485767, 11010383, 11534819, 12059123, 12583007, 13107923, 13631819, 14156543, 14680067, 15204467, 15729647, 16253423, 17825999, 18874379, 19923227, 20971799, 22020227, 23069447, 24117683, 25166423, 26214743, 27264047, 28312007, 29360147, 30410483, 31457627, 32505983, 35651783, 37749983, 39845987, 41943347, 44040383, 46137887, 48234623, 50331707, 52429067, 54526019, 56623367, 58720307, 60817763, 62915459, 65012279, 71303567, 75497999, 79691867, 83886983, 88080527, 92275307, 96470447, 100663439, 104858387, 109052183, 113246699, 117440699, 121635467, 125829239, 130023683, 142606379, 150994979, 159383759, 167772239, 176160779, 184549559, 192938003, 201327359, 209715719, 218104427, 226493747, 234882239, 243269639, 251659139, 260047367, 285215507, 301989959, 318767927, 335544323, 352321643, 369100463, 385876703, 402654059, 419432243, 436208447, 452986103, 469762067, 486539519, 503316623, 520094747, 570425399, 603979919, 637534763, 671089283, 704643287, 738198347, 771752363, 805307963, 838861103, 872415239, 905971007, 939525143, 973079279, 1006633283, 1040187419, 1140852767, 1207960679, 1275069143, 1342177379, 1409288183, 1476395699, 1543504343, 1610613119, 1677721667, 1744830587, 1811940419, 1879049087, 1946157419, 2013265967, 2080375127, 2281701827, 2415920939, 2550137039, 2684355383, 2818572539, 2952791147, 3087008663, 3221226167, 3355444187, 3489661079, 3623878823, 3758096939, 3892314659, 4026532187, 4160749883, 4563403379, 4831838783, 5100273923, 5368709219, 5637144743, 5905580687, 6174015503, 6442452119, 6710886467, 6979322123, 7247758307, 7516193123, 7784629079, 8053065599, 8321499203, 9126806147, 9663676523, 10200548819, 10737418883, 11274289319, 11811160139, 12348031523, 12884902223, 13421772839, 13958645543, 14495515943, 15032386163, 15569257247, 16106127887, 16642998803, 18253612127, 19327353083, 20401094843, 21474837719, 22548578579, 23622320927, 24696062387, 25769803799, 26843546243, 27917287907, 28991030759, 30064772327, 31138513067, 32212254947, 33285996803, 36507222923, 38654706323, 40802189423, 42949673423, 45097157927, 47244640319, 49392124247, 51539607599, 53687092307, 55834576979, 57982058579, 60129542339, 62277026327, 64424509847, 66571993199, 73014444299, 77309412407, 81604379243, 85899346727, 90194314103, 94489281203, 98784255863, 103079215439, 107374183703, 111669150239, 115964117999, 120259085183, 124554051983, 128849019059, 133143986399, 146028888179, 154618823603, 163208757527, 171798693719, 180388628579, 188978561207, 197568495647, 206158430447, 214748365067, 223338303719, 231928234787, 240518168603, 249108103547, 257698038539, 266287975727, 292057776239, 309237645803, 326417515547, 343597385507, 360777253763, 377957124803, 395136991499, 412316861267, 429496730879, 446676599987, 463856468987, 481036337207, 498216206387, 515396078039, 532575944723, 584115552323, 618475290887, 652835029643, 687194768879, 721554506879, 755914244627, 790273985219, 824633721383, 858993459587, 893353198763, 927712936643, 962072674643, 996432414899, 1030792152539, 1065151889507, 1168231105859, 1236950582039, 1305670059983, 1374389535587, 1443109012607, 1511828491883, 1580547965639, 1649267441747, 1717986918839, 1786706397767, 1855425872459, 1924145348627, 1992864827099, 2061584304323, 2130303780503, 2336462210183, 2473901164367, 2611340118887, 2748779070239, 2886218024939, 3023656976507, 3161095931639, 3298534883999, 3435973836983, 3573412791647, 3710851743923, 3848290698467, 3985729653707, 4123168604483, 4260607557707, 4672924419707, 4947802331663, 5222680234139, 5497558138979, 5772436047947, 6047313952943, 6322191860339, 6597069767699, 6871947674003, 7146825580703, 7421703488567, 7696581395627, 7971459304163, 8246337210659, 8521215117407, 9345848837267, 9895604651243, 10445360463947, 10995116279639, 11544872100683, 12094627906847, 12644383722779, 13194139536659, 13743895350023, 14293651161443, 14843406975659, 15393162789503, 15942918604343, 16492674420863, 17042430234443, 18691697672867, 19791209300867, 20890720927823, 21990232555703, 23089744183799, 24189255814847, 25288767440099, 26388279068903, 27487790694887, 28587302323787, 29686813951463, 30786325577867, 31885837205567, 32985348833687, 34084860462083, 37383395344739, 39582418600883, 41781441856823, 43980465111383, 46179488367203, 48378511622303, 50577534878987, 52776558134423, 54975581392583, 57174604644503, 59373627900407, 61572651156383, 63771674412287, 65970697666967, 68169720924167, 74766790688867, 79164837200927, 83562883712027, 87960930223163, 92358976733483, 96757023247427, 101155069756823, 105553116266999, 109951162779203, 114349209290003, 118747255800179, 123145302311783, 127543348823027, 131941395333479, 136339441846019, 149533581378263, 158329674402959, 167125767424739, 175921860444599, 184717953466703, 193514046490343, 202310139514283, 211106232536699, 219902325558107, 228698418578879, 237494511600287, 246290604623279, 255086697645023, 263882790666959, 272678883689987, 299067162755363, 316659348799919, 334251534845303, 351843720890723, 369435906934019, 387028092977819, 404620279022447, 422212465067447, 439804651111103, 457396837157483, 474989023199423, 492581209246163, 510173395291199, 527765581341227, 545357767379483, 598134325510343, 633318697599023, 668503069688723, 703687441776707, 738871813866287, 774056185954967, 809240558043419, 844424930134187, 879609302222207, 914793674313899, 949978046398607, 985162418489267, 1020346790579903, 1055531162666507, 1090715534754863};
	
	/* Set the initial size of the hash table to 2 times the size of the genome. */
	uint64_t hashTableSizeIndex=0, currHashTabSize=0; 
	for (i=0; i<450; ++i) 
		if (hashTableSize[i] > (genomeLength*2)) 
		{
			hashTableSizeIndex = i;
			break;
		}
	currHashTabSize = hashTableSize[hashTableSizeIndex];  //Store the size of the hash table.
	

	/* Create the witness, counter, and genome position arrays. */
	uint64_t * witness;				// Array to store the witnesses.
	uint64_t * counters;			// Array to store the counters for each witness.
	assert(witness = new uint64_t[currHashTabSize]);
	assert(counters = new uint64_t[currHashTabSize]);
	
	/* Initialize the hash table and counter arrays. */
	for (i=0; i < currHashTabSize; ++i) 
	{
		witness[i] = 0;
		counters[i] = 0;
	}

	/* Create and initialize variables needed for hashing the genome file. */
	uint64_t kmerBinary=0, kmerBinaryRev=0, witnessValue=0, badKmer=0, numCollisionsKmer=0, increment=0, witnessValueTemp=0, kmersInGenome=0, genomeKmerNs=0, moreThan1=0, moreThan10=0, moreThan100=0, moreThan50=0;
	int64_t x=0;
	
	/* For loop to insert all the witnesses from the genome into the hash table. */
	for(i=0; i<=genomeLength-kmerLength;++i)
	{		
		/* Get the value of the k-mer in binary. */
		kmerBinary=0; kmerBinaryRev=0; witnessValue=0; numCollisionsKmer=0; badKmer=0;;  

		for(j=0;j<kmerLength;++j)
		{
			switch(genome[i+j]) 
			{
				case 'A': kmerBinary <<= 2;	break;
				case 'C': kmerBinary <<= 2;	kmerBinary |= 1; break;
				case 'G': kmerBinary <<= 2;	kmerBinary |= 2; break;
				case 'T': kmerBinary <<= 2;	kmerBinary |= 3; break;
				default:  badKmer=1;
			}
		}
		
		/* Get the value of the reverse complement k-mer in binary. */
		
		for(x=(kmerLength-1);x>=0;--x)
		{
			switch(genome[i+x]) 
			{
				case 'T': kmerBinaryRev <<= 2;	break;
				case 'G': kmerBinaryRev <<= 2;	kmerBinaryRev |= 1; break;
				case 'C': kmerBinaryRev <<= 2;	kmerBinaryRev |= 2; break;
				case 'A': kmerBinaryRev <<= 2;	kmerBinaryRev |= 3; break;
				default:  badKmer=1;
			}
		}
					
		if(badKmer==0)
		{
			// Only use the direction with the smallest binary value.
			if(kmerBinaryRev<=kmerBinary)
				kmerBinary = kmerBinaryRev;
		
			/* Use double probing if the hash value is already taken in the hash table. */
			witnessValue = kmerBinary % currHashTabSize;
			witnessValueTemp = witnessValue;
			increment = 1 + (kmerBinary % hashTableSize[hashTableSizeIndex-1]);
			
			while (witness[witnessValueTemp] != kmerBinary && witness[witnessValueTemp] != 0)
			{	
				++numCollisionsKmer;
				witnessValueTemp = witnessValue+(numCollisionsKmer*increment);
				while(witnessValueTemp>=currHashTabSize)
					witnessValueTemp-=currHashTabSize;
			}
			witnessValue=witnessValueTemp;
			
			/* Insert the hash value into the array. */
			if(counters[witnessValue]==0)
			{
				++kmersInGenome;
				witness[witnessValue] = kmerBinary;
				counters[witnessValue]++;				
			}
			else
				counters[witnessValue]++;
		}
		else
			++genomeKmerNs;  // If the k-mer is not good then it must have an N in the k-mer.
	}
	
	/* Find how many k-mers appear more than once, 10 times, 50 times, and 100 times  in the genome. */
	for(i=0;i<currHashTabSize;++i)
	{	
		if(counters[i] > 1)	 ++moreThan1;
		if(counters[i] > 10) ++moreThan10;
		if(counters[i] > 50) ++moreThan50;
		if(counters[i] > 100) ++moreThan100;
	}
	time(&t_end);
	
	delete [] counters;  //no longer needed.
		
	cout << "          Number of unique k-mers in the genome = " << right << setw(14) << kmersInGenome << endl;
	cout << "      Number of k-mers appearing more than once = " << right << setw(14) << moreThan1 << endl;
	cout << "  Number of k-mers appearing more than 10 times = " << right << setw(14) << moreThan10 << endl;
	cout << "  Number of k-mers appearing more than 50 times = " << right << setw(14) << moreThan50 << endl;
	cout << " Number of k-mers appearing more than 100 times = " << right << setw(14) << moreThan100 << endl << endl;

/******************************************************************************************************************
 Find the k-mers in the original and corrected files.  The two files are processed at the same time in parallel.  
 The reads are processed 1,000,000 at a time in parallel.
******************************************************************************************************************/
	time(&t_start1);
	ifstream origReadsFile(argv[3]);
	if (!origReadsFile) {
		cerr << "Cannot open the original reads file = " << argv[3] << endl;
		exit(0);
	}
	
	ifstream corrReadsFile(argv[4]);
	if (!corrReadsFile) {
		cerr << "Cannot open the corrected reads file = " << argv[4] << endl;
		exit(0);
	}

	/* Create and initialize variable needed to find the k-mers in the original and corrected files. */
	uint64_t longestRead = 0, shortestRead = 999999, numberOfReads=0, TP=0, TN=0, FP=0, FN=0, chunkSize = 1000000, lastIteration = 0, totalGoodOriginal=0, totalGoodCorrected=0, totalBadOriginal=0, totalBadCorrected=0, readNumber=0;
	string headerOriginal, headerCorrected, readOriginal, readCorrected, rubbish;
	
	/* Find the longest and shortest read lengths in the original file. */
	while (!origReadsFile.eof()) 
	{
		getline(origReadsFile, headerOriginal);
		getline(origReadsFile, readOriginal);
		if (readOriginal.length() > longestRead)
			longestRead = readOriginal.length();
		
		if (readOriginal.length() < shortestRead)
			shortestRead = readOriginal.length();
			
		if (headerOriginal[0] == '@') { // next two lines are skipped in fastq files
			getline(origReadsFile, headerOriginal);
			getline(origReadsFile, readOriginal);
		}
		numberOfReads++;
	}
	
	numberOfReads--; // loop above adds 1 too many because it has to process the EOF line
	origReadsFile.clear();
	origReadsFile.seekg(0);
	origReadsFile.clear();
	
	/* The chuck size is 1,000,000 but needs to be adjusted for files with less than 1,000,000 reads. */
	if (numberOfReads < chunkSize)
		chunkSize = numberOfReads;
	
	/* Find the number of iterations needed to process all of the reads. */
	if(numberOfReads%chunkSize == 0)
		lastIteration = (numberOfReads/chunkSize);
	else
		lastIteration = (numberOfReads/chunkSize)+1;

		
	/* Create and initialize arrays to store the chunk of reads and their lengths. */
	char ** readsArrayOriginal;				// Stores the original reads.
	char ** readsArrayCorrected;			// Stores the corrected reads.
	int readLengthsOriginal[chunkSize];		// Stores the original read lengths.
	int readLengthsCorrected[chunkSize];	// Stores the corrected read lengths.	
	assert(readsArrayOriginal = new char*[chunkSize]);
	assert(readsArrayCorrected = new char*[chunkSize]);
	
	for (i=0; i<chunkSize; ++i)
	{
		assert(readsArrayOriginal[i] = new char[longestRead]);
		assert(readsArrayCorrected[i] = new char[longestRead]);
		readLengthsOriginal[i] = 0;
		readLengthsCorrected[i] = 0;
	}
	
	/* Create and initialize the genome coverage arrays for the original and corrected reads. */
	bool * kmerFoundBefore;	// Array to mark positions in the hash table covered by the original reads.
	bool * kmerFoundAfter;	// Array to mark positions in the hash table covered by the corrected reads.
	assert(kmerFoundBefore = new bool[currHashTabSize]);
	assert(kmerFoundAfter = new bool[currHashTabSize]);

	for (i=0; i<currHashTabSize; ++i) 
	{
		kmerFoundBefore[i] = false;
		kmerFoundAfter[i] = false;
	}
	
	/* For loop to find the k-mers that align to the genome for the original and corrected files. */
	for (uint64_t timesThroughLoop=0;  timesThroughLoop < lastIteration; ++timesThroughLoop) 
	{								
		/* For loop to store the reads in chunks so they can be processed in parallel. */
		for (readNumber=0; readNumber < chunkSize; ++readNumber)
		{	if((readNumber + ((timesThroughLoop)*chunkSize)) < numberOfReads)
			{
				getline(origReadsFile, headerOriginal);
				getline(origReadsFile, readOriginal);
				getline(corrReadsFile, headerCorrected);
				getline(corrReadsFile, readCorrected);
				
				// store the length of each read into readLengths[]
				readLengthsOriginal[readNumber] = readOriginal.length();
				readLengthsCorrected[readNumber] = readCorrected.length();
				 
				// copy the string to readsArray[][]
				for (i=0; i<readOriginal.length(); ++i)
					readsArrayOriginal[readNumber][i] = readOriginal[i];

				for (i=0; i<readCorrected.length(); ++i)
					readsArrayCorrected[readNumber][i] = readCorrected[i];
				
				// if the corrected read is trimmed then fill the rest of the array with N's.
				if (readCorrected.length() < readOriginal.length())
				{
					for(i=i; i<readOriginal.length();++i)
						readsArrayCorrected[readNumber][i] = 'N';
				}
				
				if (headerOriginal[0] == '@') { // next two lines are skipped in fastq files
					getline(origReadsFile, rubbish);
					getline(origReadsFile, rubbish);
				}
				if (headerCorrected[0] == '@') { // next two lines are skipped in fastq files
					getline(corrReadsFile, rubbish);
					getline(corrReadsFile, rubbish);
				}
			}
		}				
				
		#pragma omp parallel
		{
			/* Create and initialize variables that are private to each thread. */
			uint64_t badKmer=0, TP_Thread=0, TN_Thread=0, FP_Thread=0, FN_Thread=0,kmerBinaryForward=0,kmerBinaryReverse=0,witnessValue=0,witnessValueTemp=0,increment=0,numCollisionsKmer=0,readPosition=0,kmerPosition=0, totalGoodOriginalThread=0, totalGoodCorrectedThread=0, totalBadOriginalThread=0, totalBadCorrectedThread=0, kmerBinarySmallest=0;
			bool foundOriginal = false, foundCorrected = false;
			int64_t kmerPositionRev=0;
			
			#pragma omp for
			for(readNumber=0; readNumber < chunkSize; ++readNumber)
			{	if((readNumber + ((timesThroughLoop)*chunkSize)) < numberOfReads)
				{
					for(readPosition=0; readPosition<=readLengthsOriginal[readNumber]-kmerLength;++readPosition)
					{
						/* Search for the original k-mer. */
						kmerBinaryForward=0; kmerBinaryReverse=0; badKmer=0; witnessValue=0; numCollisionsKmer=0; foundOriginal = false;
						
						/* Get the value of the k-mer in binary. */
						for(kmerPosition=0;kmerPosition<kmerLength;++kmerPosition)
						{
							switch(readsArrayOriginal[readNumber][readPosition+kmerPosition]) 
							{
								case 'A': kmerBinaryForward <<= 2;	break;
								case 'a': kmerBinaryForward <<= 2;	break;
								case 'C': kmerBinaryForward <<= 2;	kmerBinaryForward |= 1; break;
								case 'c': kmerBinaryForward <<= 2;	kmerBinaryForward |= 1; break;
								case 'G': kmerBinaryForward <<= 2;	kmerBinaryForward |= 2; break;
								case 'g': kmerBinaryForward <<= 2;	kmerBinaryForward |= 2; break;
								case 'T': kmerBinaryForward <<= 2;	kmerBinaryForward |= 3; break;
								case 't': kmerBinaryForward <<= 2;	kmerBinaryForward |= 3; break;
								default:  badKmer=1;
							}
						}
						
						/* Get the value of the reverse complement k-mer in binary. */
						for(kmerPositionRev=(kmerLength-1);kmerPositionRev>=0;--kmerPositionRev)
						{
							switch(readsArrayOriginal[readNumber][readPosition+kmerPositionRev]) 
							{
								case 'T': kmerBinaryReverse <<= 2;	break;
								case 't': kmerBinaryReverse <<= 2;	break;
								case 'G': kmerBinaryReverse <<= 2;	kmerBinaryReverse |= 1; break;
								case 'g': kmerBinaryReverse <<= 2;	kmerBinaryReverse |= 1; break;
								case 'C': kmerBinaryReverse <<= 2;	kmerBinaryReverse |= 2; break;
								case 'c': kmerBinaryReverse <<= 2;	kmerBinaryReverse |= 2; break;
								case 'A': kmerBinaryReverse <<= 2;	kmerBinaryReverse |= 3; break;
								case 'a': kmerBinaryReverse <<= 2;	kmerBinaryReverse |= 3; break;
								default:  badKmer=1;
							}
						}
						
						if(badKmer==0)
						{
							// Only use the direction with the smallest binary value.
							if(kmerBinaryReverse<=kmerBinaryForward)
								kmerBinarySmallest = kmerBinaryReverse;
							else
								kmerBinarySmallest = kmerBinaryForward;
								
							/* Use double probing if the hash value is already taken in the hash table. */
							witnessValue = kmerBinarySmallest % currHashTabSize;
							witnessValueTemp = witnessValue;
							increment = 1 + (kmerBinarySmallest % hashTableSize[hashTableSizeIndex-1]);
							while (witness[witnessValueTemp] != kmerBinarySmallest && witness[witnessValueTemp] != 0)
							{	
								++numCollisionsKmer;
								witnessValueTemp = witnessValue+(numCollisionsKmer*increment);
								while(witnessValueTemp>=currHashTabSize)
									witnessValueTemp-=currHashTabSize;
							}
							witnessValue=witnessValueTemp;
							
							if(witness[witnessValue]==kmerBinarySmallest)							
							{	
								foundOriginal=true;
								kmerFoundBefore[witnessValue]=true;
							}
						}
						
						/* Search for the corrected k-mer. */
						kmerBinaryForward=0; kmerBinaryReverse=0; badKmer=0; witnessValue=0; numCollisionsKmer=0; foundCorrected = false;
						
						/* Get the value of the k-mer in binary. */
						for(kmerPosition=0;kmerPosition<kmerLength;++kmerPosition)
						{
							switch(readsArrayCorrected[readNumber][readPosition+kmerPosition]) 
							{
								case 'A': kmerBinaryForward <<= 2;	break;
								case 'a': kmerBinaryForward <<= 2;	break;
								case 'C': kmerBinaryForward <<= 2;	kmerBinaryForward |= 1; break;
								case 'c': kmerBinaryForward <<= 2;	kmerBinaryForward |= 1; break;
								case 'G': kmerBinaryForward <<= 2;	kmerBinaryForward |= 2; break;
								case 'g': kmerBinaryForward <<= 2;	kmerBinaryForward |= 2; break;
								case 'T': kmerBinaryForward <<= 2;	kmerBinaryForward |= 3; break;
								case 't': kmerBinaryForward <<= 2;	kmerBinaryForward |= 3; break;
								default:  badKmer=1;
							}
						}
						
						/* Get the value of the reverse complement k-mer in binary. */
						for(kmerPositionRev=(kmerLength-1);kmerPositionRev>=0;--kmerPositionRev)
						{
							switch(readsArrayCorrected[readNumber][readPosition+kmerPositionRev]) 
							{
								case 'T': kmerBinaryReverse <<= 2;	break;
								case 't': kmerBinaryReverse <<= 2;	break;
								case 'G': kmerBinaryReverse <<= 2;	kmerBinaryReverse |= 1; break;
								case 'g': kmerBinaryReverse <<= 2;	kmerBinaryReverse |= 1; break;
								case 'C': kmerBinaryReverse <<= 2;	kmerBinaryReverse |= 2; break;
								case 'c': kmerBinaryReverse <<= 2;	kmerBinaryReverse |= 2; break;
								case 'A': kmerBinaryReverse <<= 2;	kmerBinaryReverse |= 3; break;
								case 'a': kmerBinaryReverse <<= 2;	kmerBinaryReverse |= 3; break;
								default:  badKmer=1;
							}
						}
						
						if(badKmer==0)
						{
							// Only use the direction with the smallest binary value.
							if(kmerBinaryReverse<=kmerBinaryForward)
								kmerBinarySmallest = kmerBinaryReverse;
							else
								kmerBinarySmallest = kmerBinaryForward;
								
							/* Use double probing if the hash value is already taken in the hash table. */
							witnessValue = kmerBinarySmallest % currHashTabSize;
							witnessValueTemp = witnessValue;
							increment = 1 + (kmerBinarySmallest % hashTableSize[hashTableSizeIndex-1]);
							while (witness[witnessValueTemp] != kmerBinarySmallest && witness[witnessValueTemp] != 0)
							{	
								++numCollisionsKmer;
								witnessValueTemp = witnessValue+(numCollisionsKmer*increment);
								while(witnessValueTemp>=currHashTabSize)
									witnessValueTemp-=currHashTabSize;
							}
							witnessValue=witnessValueTemp;
							
							if(witness[witnessValue]==kmerBinarySmallest)							
							{	
								foundCorrected=true;
								kmerFoundAfter[witnessValue]=true;
							}
						}
				
						if(foundOriginal==false && foundCorrected==true)
						{	++TP_Thread; ++totalBadOriginalThread; ++totalGoodCorrectedThread; }
						if(foundOriginal==true && foundCorrected==false)
						{	++FP_Thread; ++totalGoodOriginalThread; ++totalBadCorrectedThread; }
						if(foundOriginal==true && foundCorrected==true)
						{	++TN_Thread; ++totalGoodOriginalThread; ++totalGoodCorrectedThread; }
						if(foundOriginal==false && foundCorrected==false)
						{	++FN_Thread; ++totalBadOriginalThread; ++totalBadCorrectedThread;	}
					}
		
				}
			}
			#pragma omp critical
			{
				TP+=TP_Thread; FP+=FP_Thread; TN+=TN_Thread; FN+=FN_Thread;
				totalGoodOriginal+=totalGoodOriginalThread;
				totalBadOriginal+=totalBadOriginalThread;
				totalGoodCorrected+=totalGoodCorrectedThread;
				totalBadCorrected+=totalBadCorrectedThread;
			}
		}
	}
	time(&t_end1);

	/* Find the unique k-mers found in the original and corrected data sets. */
	uint64_t TP_kmer=0, FP_kmer=0, TN_kmer=0, FN_kmer=0, kmerTotalBefore=0, kmerTotalAfter=0;
	for (i=0; i <currHashTabSize; ++i) 
	{
		if(kmerFoundBefore[i]==false && kmerFoundAfter[i]==true)
		{	++TP_kmer;++kmerTotalAfter; }
		if(kmerFoundBefore[i]==true && kmerFoundAfter[i]==false)
		{	++FP_kmer; ++kmerTotalBefore; }
		if(kmerFoundBefore[i]==true && kmerFoundAfter[i]==true)
		{	++TN_kmer; ++kmerTotalBefore; ++kmerTotalAfter; }
	}
	FN_kmer = kmersInGenome-(TP_kmer+FP_kmer+TN_kmer);
	
	cout << "*******************************************************************" << endl;
	cout << "*                  Original Reads File Results                    *" << endl;
	cout << "*******************************************************************" << endl;
	
	cout << "        Total k-mers found in the original file = " << right << setw(16) << totalGoodOriginal << endl;
	cout << "    Total k-mers not found in the original file = " << right << setw(16) << totalBadOriginal << endl;
	cout << "              Total k-mers in the original file = " << right << setw(16) << totalGoodOriginal+totalBadOriginal << endl;
	cout << "    Percent of good k-mers in the original file = " << right << setw(15) << (double)100*totalGoodOriginal/(totalGoodOriginal+totalBadOriginal) << "%" << endl << endl;
	cout << "               Total k-mers in the genome found = " << right << setw(16) << kmerTotalBefore << endl;
	cout << "   Percent of k-mers found in the original file = " << right << setw(15) << (double)100*kmerTotalBefore/kmersInGenome << "%" << endl << endl;

	cout << "*******************************************************************" << endl;
	cout << "*                  Corrected Reads File Results                   *" << endl;
	cout << "*******************************************************************" << endl;
	
	cout << "       Total k-mers found in the corrected file = " << right << setw(16) << totalGoodCorrected << endl;
	cout << "   Total k-mers not found in the corrected file = " << right << setw(16) << totalBadCorrected << endl;
	cout << "             Total k-mers in the corrected file = " << right << setw(16) << totalGoodCorrected+totalBadCorrected << endl;
	cout << "   Percent of good k-mers in the corrected file = " << right << setw(15) << (double)100*totalGoodCorrected/(totalGoodCorrected+totalBadCorrected) << "%" << endl << endl;
	cout << "               Total k-mers in the genome found = " << right << setw(16) << kmerTotalAfter << endl;
	cout << "  Percent of k-mers found in the corrected file = " << right << setw(15) << (double)100*kmerTotalAfter/kmersInGenome << "%" << endl << endl;

	cout << "*******************************************************************" << endl;
	cout << "*                          k-mer Results                          *" << endl;
	cout << "*******************************************************************" << endl;
	
	cout << "                      TP = " << right << setw(16) << TP << endl;
	cout << "                      FP = " << right << setw(16) << FP << endl;
	cout << "                      FN = " << right << setw(16) << FN << endl;
	cout << "                      TN = " << right << setw(16) << TN << endl;
	cout << "                    Gain = " << right << setw(15) << (double)100*((int64_t)TP-(int64_t)FP)/((int64_t)TP+(int64_t)FN) << "%" << endl;
	cout << "             Sensitivity = " << right << setw(15) << (double)100*TP/(TP+FN) << "%" << endl;
	cout << "             Specificity = " << right << setw(15) << (double)100*TN/(TN+FP) << "%"  << endl << endl;

	cout << "*******************************************************************" << endl;
	cout << "*                      Unique k-mer Results                       *" << endl;
	cout << "*******************************************************************" << endl;
	
	cout << "                      TP = " << right << setw(16) << TP_kmer << endl;
	cout << "                      FP = " << right << setw(16) << FP_kmer << endl;
	cout << "                      FN = " << right << setw(16) << FN_kmer << endl;
	cout << "                      TN = " << right << setw(16) << TN_kmer << endl;
	cout << "                    Gain = " << right << setw(15) << (double)100*((int64_t)TP_kmer-(int64_t)FP_kmer)/((int64_t)TP_kmer+(int64_t)FN_kmer) << "%" << endl << endl;

	cout << "    Total time to build the hash table = " << right << setw(8) << difftime(t_end,t_start) << " seconds" << endl;
	cout << "  Total time to find the k-mer results = " << right << setw(8) << difftime(t_end1,t_start1) << " seconds" << endl << endl << flush;

	delete [] witness;
	delete [] kmerFoundBefore;
	delete [] kmerFoundAfter;
	
	for (i=0; i<chunkSize; ++i)
	{
		delete [] readsArrayOriginal[i];
		delete [] readsArrayCorrected[i];
	}
	delete [] readsArrayOriginal;
	delete [] readsArrayCorrected;

	return 0;
}
