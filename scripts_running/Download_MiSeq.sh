#!/bin/sh

# Insert and run this script in the directory that you want to download the files.

# E.coli_SRR519926
wget ftp://ftp-trace.ncbi.nlm.nih.gov/sra/sra-instant/reads/ByRun/sra/SRR/SRR519/SRR519926/SRR519926.sra
fastq-dump --split-files SRR519926.sra
shuffleSequences_fastq.pl SRR519926_1.fastq SRR519926_2.fastq E.coli_SRR519926.fastq

# M.tuberculosis_SRR1200797
wget ftp://ftp-trace.ncbi.nlm.nih.gov/sra/sra-instant/reads/ByRun/sra/SRR/SRR120/SRR1200797/SRR1200797.sra
fastq-dump --split-files SRR1200797.sra
shuffleSequences_fastq.pl SRR1200797_1.fastq SRR1200797_2.fastq M.tuberculosis_SRR1200797.fastq

# S.enterica_SRR1203044
wget ftp://ftp-trace.ncbi.nlm.nih.gov/sra/sra-instant/reads/ByRun/sra/SRR/SRR120/SRR1203044/SRR1203044.sra
fastq-dump --split-files SRR1203044.sra
shuffleSequences_fastq.pl SRR1203044_1.fastq SRR1203044_2.fastq S.enterica_SRR1203044.fastq

# S.enterica_SRR1206093
wget ftp://ftp-trace.ncbi.nlm.nih.gov/sra/sra-instant/reads/ByRun/sra/SRR/SRR120/SRR1206093/SRR1206093.sra
fastq-dump --split-files SRR1206093.sra
shuffleSequences_fastq.pl SRR1206093_1.fastq SRR1206093_2.fastq S.enterica_SRR1206093.fastq

# L.monocytogenes_SRR1198952
wget ftp://ftp-trace.ncbi.nlm.nih.gov/sra/sra-instant/reads/ByRun/sra/SRR/SRR119/SRR1198952/SRR1198952.sra
fastq-dump --split-files SRR1198952.sra
shuffleSequences_fastq.pl SRR1198952_1.fastq SRR1198952_2.fastq L.monocytogenes_SRR1198952.fastq

# P.syringae_SRR1119292
wget ftp://ftp-trace.ncbi.nlm.nih.gov/sra/sra-instant/reads/ByRun/sra/SRR/SRR111/SRR1119292/SRR1119292.sra
fastq-dump --split-files SRR1119292.sra
shuffleSequences_fastq.pl SRR1119292_1.fastq SRR1119292_2.fastq P.syringae_SRR1119292.fastq

# B.dentium_SRR1151311
wget ftp://ftp-trace.ncbi.nlm.nih.gov/sra/sra-instant/reads/ByRun/sra/SRR/SRR115/SRR1151311/SRR1151311.sra
fastq-dump --split-files SRR1151311.sra
shuffleSequences_fastq.pl SRR11513111.fastq SRR1151311_2.fastq B.dentium_SRR1151311.fastq

# E.coli_SRR522163
wget ftp://ftp-trace.ncbi.nlm.nih.gov/sra/sra-instant/reads/ByRun/sra/SRR/SRR522/SRR522163/SRR522163.sra
fastq-dump --split-files SRR522163.sra
shuffleSequences_fastq.pl SRR522163_1.fastq SRR522163_2.fastq E.coli_SRR522163.fastq

# O.tsutsugamushi_SRR1202083
wget ftp://ftp-trace.ncbi.nlm.nih.gov/sra/sra-instant/reads/ByRun/sra/SRR/SRR120/SRR1202083/SRR1202083.sra
fastq-dump --split-files SRR1202083.sra
shuffleSequences_fastq.pl SRR1202083_1.fastq SRR1202083_2.fastq O.tsutsugamushi_SRR1202083.fastq
