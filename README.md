# Correcting-Illumina-data

Following programs are used for evaluating the quality of error correction in Illumina data reported in the paper "Correcting Illumina data" by Michael Molnar and Lucian Ilie:

- Folder readSearch contains program for searching whole reads

- Folder kmerSearch contains program for searching k-mers

- Folder scripts_running contains scripts for downloading the datasets used in the paper and running the error correcting programs: BLESS, Coral, HiTEC, Musket, RACER, SGA, SHREC

- Folder scripts_searching contains scripts for downloading the reference genome sequences and running readSearch and kmerSearch

It is assumed that the user has properly installed the error correction programs and has them listed in their PATH. For downloading and extracting the datasets and genome sequences the user will need to have installed wget, cat, gunzip, fastq-dump (part of the NCBI Toolkit), and perl for the shuffleSequences_fastq.pl script (from the Velvet package). 

###CITE

If you find this work useful, please cite our paper:

M. Molnar, L. Ilie [Correcting Illumina data](http://bib.oxfordjournals.org/content/16/4/588) Bioinformatics, 2014
