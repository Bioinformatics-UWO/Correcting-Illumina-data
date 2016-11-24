#!/bin/sh

# The following parameters will need to be modified for your particular system.
IN_PATH=/home/Data_Sets
OUT_PATH=/home/Coral
NUM_PROC=1

# HiSeq Data Sets
coral -fq $IN_PATH/M.tuberculosis_ERR400373.fastq -o $OUT_PATH/M.tuberculosis_ERR400373_corr.fastq -illumina -p $NUM_PROC
coral -fq $IN_PATH/S.enterica_ERR230402.fastq -o $OUT_PATH/S.enterica_ERR230402_corr.fastq -illumina -p $NUM_PROC
coral -fq $IN_PATH/S.cerevisiae_ERR422544.fastq -o $OUT_PATH/S.cerevisiae_ERR422544_corr.fastq -illumina -p $NUM_PROC
coral -fq $IN_PATH/L.pneumophila_SRR801797.fastq -o $OUT_PATH/L.pneumophila_SRR801797_corr.fastq -illumina -p $NUM_PROC
coral -fq $IN_PATH/E.coli_SRR1191655.fastq -o $OUT_PATH/E.coli_SRR1191655_corr.fastq -illumina -p $NUM_PROC
coral -fq $IN_PATH/E.coli_SRR490124.fastq -o $OUT_PATH/E.coli_SRR490124_corr.fastq -illumina -p $NUM_PROC
coral -fq $IN_PATH/C.elegans_SRX218989.fastq -o $OUT_PATH/C.elegans_SRX218989_corr.fastq -illumina -p $NUM_PROC
coral -fq $IN_PATH/C.elegans_SRR543736.fastq -o $OUT_PATH/C.elegans_SRR543736_corr.fastq -illumina -p $NUM_PROC
coral -fq $IN_PATH/D.melanogaster_SRR823377.fastq -o $OUT_PATH/D.melanogaster_SRR823377_corr.fastq -illumina -p $NUM_PROC
coral -fq $IN_PATH/D.melanogaster_SRR988075.fastq -o $OUT_PATH/D.melanogaster_SRR988075_corr.fastq -illumina -p $NUM_PROC
coral -fq $IN_PATH/Human_ERX069715.fastq -o $OUT_PATH/Human_ERX069715_corr.fastq -illumina -p $NUM_PROC
coral -fq $IN_PATH/Human_ERX069504.fastq -o $OUT_PATH/Human_ERX069504_corr.fastq -illumina -p $NUM_PROC
coral -fq $IN_PATH/Human_ERX069505.fastq -o $OUT_PATH/Human_ERX069505_corr.fastq -illumina -p $NUM_PROC

# MiSeq Data Sets
coral -fq $IN_PATH/E.coli_SRR519926.fastq -o $OUT_PATH/E.coli_SRR519926_corr.fastq -illumina -p $NUM_PROC
coral -fq $IN_PATH/M.tuberculosis_SRR1200797.fastq -o $OUT_PATH/M.tuberculosis_SRR1200797_corr.fastq -illumina -p $NUM_PROC
coral -fq $IN_PATH/S.enterica_SRR1203044.fastq -o $OUT_PATH/S.enterica_SRR1203044_corr.fastq -illumina -p $NUM_PROC
coral -fq $IN_PATH/S.enterica_SRR1206093.fastq -o $OUT_PATH/S.enterica_SRR1206093_corr.fastq -illumina -p $NUM_PROC
coral -fq $IN_PATH/L.monocytogenes_SRR1198952.fastq -o $OUT_PATH/L.monocytogenes_SRR1198952_corr.fastq -illumina -p $NUM_PROC
coral -fq $IN_PATH/P.syringae_SRR1119292.fastq -o $OUT_PATH/P.syringae_SRR1119292_corr.fastq -illumina -p $NUM_PROC
coral -fq $IN_PATH/B.dentium_SRR1151311.fastq -o $OUT_PATH/B.dentium_SRR1151311_corr.fastq -illumina -p $NUM_PROC
coral -fq $IN_PATH/E.coli_SRR522163.fastq -o $OUT_PATH/E.coli_SRR522163_corr.fastq -illumina -p $NUM_PROC
coral -fq $IN_PATH/O.tsutsugamushi_SRR1202083.fastq -o $OUT_PATH/O.tsutsugamushi_SRR1202083_corr.fastq -illumina -p $NUM_PROC
