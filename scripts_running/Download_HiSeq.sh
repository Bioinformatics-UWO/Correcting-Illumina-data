#!/bin/sh

# Insert and run this script in the directory that you want to download the files.

# M.tuberculosis_ERR400373
wget ftp://ftp-trace.ncbi.nlm.nih.gov/sra/sra-instant/reads/ByRun/sra/ERR/ERR400/ERR400373/ERR400373.sra
fastq-dump --split-files ERR400373.sra
shuffleSequences_fastq.pl ERR400373_1.fastq ERR400373_2.fastq M.tuberculosis_ERR400373.fastq

# S.enterica_ERR230402
wget ftp://ftp-trace.ncbi.nlm.nih.gov/sra/sra-instant/reads/ByRun/sra/ERR/ERR230/ERR230402/ERR230402.sra
fastq-dump --split-files ERR230402.sra
shuffleSequences_fastq.pl ERR230402_1.fastq ERR230402_2.fastq S.enterica_ERR230402.fastq

# S.cerevisiae_ERR422544
wget ftp://ftp-trace.ncbi.nlm.nih.gov/sra/sra-instant/reads/ByRun/sra/ERR/ERR422/ERR422544/ERR422544.sra
fastq-dump --split-files ERR422544.sra
shuffleSequences_fastq.pl ERR422544_1.fastq ERR422544_2.fastq S.cerevisiae_ERR422544.fastq

# L.pneumophila_SRR801797
wget ftp://ftp-trace.ncbi.nlm.nih.gov/sra/sra-instant/reads/ByRun/sra/SRR/SRR801/SRR801797/SRR801797.sra
fastq-dump --split-files SRR801797.sra
shuffleSequences_fastq.pl SRR801797_1.fastq SRR801797_2.fastq L.pneumophila_SRR801797.fastq

# E.coli_SRR1191655
wget ftp://ftp-trace.ncbi.nlm.nih.gov/sra/sra-instant/reads/ByRun/sra/SRR/SRR119/SRR1191655/SRR1191655.sra
fastq-dump --split-files SRR1191655.sra
shuffleSequences_fastq.pl SRR1191655_1.fastq SRR1191655_2.fastq E.coli_SRR1191655.fastq

# E.coli_SRR490124
wget ftp://ftp-trace.ncbi.nlm.nih.gov/sra/sra-instant/reads/ByRun/sra/SRR/SRR490/SRR490124/SRR490124.sra
fastq-dump --split-files SRR490124.sra
shuffleSequences_fastq.pl SRR490124_1.fastq SRR490124_2.fastq E.coli_SRR490124.fastq

# C.elegans_SRX218989
wget ftp://ftp-trace.ncbi.nlm.nih.gov/sra/sra-instant/reads/ByRun/sra/SRR/SRR651/SRR651847/SRR651847.sra
wget ftp://ftp-trace.ncbi.nlm.nih.gov/sra/sra-instant/reads/ByRun/sra/SRR/SRR651/SRR651848/SRR651848.sra
wget ftp://ftp-trace.ncbi.nlm.nih.gov/sra/sra-instant/reads/ByRun/sra/SRR/SRR651/SRR651849/SRR651849.sra
wget ftp://ftp-trace.ncbi.nlm.nih.gov/sra/sra-instant/reads/ByRun/sra/SRR/SRR651/SRR651850/SRR651850.sra
wget ftp://ftp-trace.ncbi.nlm.nih.gov/sra/sra-instant/reads/ByRun/sra/SRR/SRR651/SRR651851/SRR651851.sra
wget ftp://ftp-trace.ncbi.nlm.nih.gov/sra/sra-instant/reads/ByRun/sra/SRR/SRR651/SRR651852/SRR651852.sra
fastq-dump --split-files SRR651847.sra
fastq-dump --split-files SRR651848.sra
fastq-dump --split-files SRR651849.sra
fastq-dump --split-files SRR651850.sra
fastq-dump --split-files SRR651851.sra
fastq-dump --split-files SRR651852.sra
cat SRR651847_1.fastq SRR651848_1.fastq SRR651849_1.fastq SRR651850_1.fastq SRR651851_1.fastq SRR651852_1.fastq > C.elegans_SRX218989_1.fastq
cat SRR651847_2.fastq SRR651848_2.fastq SRR651849_2.fastq SRR651850_2.fastq SRR651851_2.fastq SRR651852_2.fastq > C.elegans_SRX218989_2.fastq
shuffleSequences_fastq.pl C.elegans_SRX218989_1.fastq C.elegans_SRX218989_2.fastq C.elegans_SRX218989.fastq

# C.elegans_SRR543736
wget ftp://ftp-trace.ncbi.nlm.nih.gov/sra/sra-instant/reads/ByRun/sra/SRR/SRR543/SRR543736/SRR543736.sra
fastq-dump --split-files SRR543736.sra
shuffleSequences_fastq.pl SRR543736_1.fastq SRR543736_2.fastq C.elegans_SRR543736.fastq

# D.melanogaster_SRR823377
wget ftp://ftp-trace.ncbi.nlm.nih.gov/sra/sra-instant/reads/ByRun/sra/SRR/SRR823/SRR823377/SRR823377.sra
fastq-dump --split-files SRR823377.sra
shuffleSequences_fastq.pl SRR823377_1.fastq SRR823377_2.fastq D.melanogaster_SRR823377.fastq

# D.melanogaster_SRR988075
wget ftp://ftp-trace.ncbi.nlm.nih.gov/sra/sra-instant/reads/ByRun/sra/SRR/SRR988/SRR988075/SRR988075.sra
fastq-dump --split-files SRR988075.sra
shuffleSequences_fastq.pl SRR988075_1.fastq SRR988075_2.fastq D.melanogaster_SRR988075.fastq

# Human_ERX069715
wget ftp://ftp-trace.ncbi.nlm.nih.gov/sra/sra-instant/reads/ByRun/sra/ERR/ERR091/ERR091787/ERR091787.sra
wget ftp://ftp-trace.ncbi.nlm.nih.gov/sra/sra-instant/reads/ByRun/sra/ERR/ERR091/ERR091788/ERR091788.sra
wget ftp://ftp-trace.ncbi.nlm.nih.gov/sra/sra-instant/reads/ByRun/sra/ERR/ERR091/ERR091789/ERR091789.sra
wget ftp://ftp-trace.ncbi.nlm.nih.gov/sra/sra-instant/reads/ByRun/sra/ERR/ERR091/ERR091790/ERR091790.sra
fastq-dump --split-files ERR091787.sra
fastq-dump --split-files ERR091788.sra
fastq-dump --split-files ERR091789.sra
fastq-dump --split-files ERR091790.sra
cat ERR091787_1.fatsq ERR091788_1.fatsq ERR091789_1.fatsq ERR091790_1.fatsq > Human_ERX069715_1.fastq
cat ERR091787_2.fatsq ERR091788_2.fatsq ERR091789_2.fatsq ERR091790_2.fatsq > Human_ERX069715_2.fastq
shuffleSequences_fastq.pl Human_ERX069715_1.fatsq Human_ERX069715_2.fastq Human_ERX069715.fastq

# Human_ERX069504
wget ftp://ftp-trace.ncbi.nlm.nih.gov/sra/sra-instant/reads/ByRun/sra/ERR/ERR091/ERR091567/ERR091567.sra
wget ftp://ftp-trace.ncbi.nlm.nih.gov/sra/sra-instant/reads/ByRun/sra/ERR/ERR091/ERR091568/ERR091568.sra
wget ftp://ftp-trace.ncbi.nlm.nih.gov/sra/sra-instant/reads/ByRun/sra/ERR/ERR091/ERR091569/ERR091569.sra
wget ftp://ftp-trace.ncbi.nlm.nih.gov/sra/sra-instant/reads/ByRun/sra/ERR/ERR091/ERR091570/ERR091570.sra
fastq-dump --split-files ERR091567.sra
fastq-dump --split-files ERR091568.sra
fastq-dump --split-files ERR091569.sra
fastq-dump --split-files ERR091570.sra
cat ERR091567_1.fatsq ERR091568_1.fatsq ERR091569_1.fatsq ERR091570_1.fatsq > Human_ERX069504_1.fastq
cat ERR091567_2.fatsq ERR091568_2.fatsq ERR091569_2.fatsq ERR091570_2.fatsq > Human_ERX069504_2.fastq
shuffleSequences_fastq.pl Human_ERX069504_1.fatsq Human_ERX069504_2.fastq Human_ERX069504.fastq

# Human_ERX069505
wget ftp://ftp-trace.ncbi.nlm.nih.gov/sra/sra-instant/reads/ByRun/sra/ERR/ERR091/ERR091571/ERR091571.sra
wget ftp://ftp-trace.ncbi.nlm.nih.gov/sra/sra-instant/reads/ByRun/sra/ERR/ERR091/ERR091572/ERR091572.sra
wget ftp://ftp-trace.ncbi.nlm.nih.gov/sra/sra-instant/reads/ByRun/sra/ERR/ERR091/ERR091573/ERR091573.sra
wget ftp://ftp-trace.ncbi.nlm.nih.gov/sra/sra-instant/reads/ByRun/sra/ERR/ERR091/ERR091574/ERR091574.sra
fastq-dump --split-files ERR091571.sra
fastq-dump --split-files ERR091572.sra
fastq-dump --split-files ERR091573.sra
fastq-dump --split-files ERR091574.sra
cat ERR091571_1.fatsq ERR091572_1.fatsq ERR091573_1.fatsq ERR091574_1.fatsq > Human_ERX069505_1.fastq
cat ERR091571_2.fatsq ERR091572_2.fatsq ERR091573_2.fatsq ERR091574_2.fatsq > Human_ERX069505_2.fastq
shuffleSequences_fastq.pl Human_ERX069505_1.fatsq Human_ERX069505_2.fastq Human_ERX069505.fastq
