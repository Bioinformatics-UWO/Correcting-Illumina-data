#!/bin/sh

# The following parameters will need to be modified for your particular system.
IN_PATH=/home/Data_Sets
OUT_PATH=/home/Musket
NUM_PROC=1

# HiSeq Data Sets
musket -inorder -p $NUM_PROC -o $OUT_PATH/M.tuberculosis_ERR400373_corr.fastq $IN_PATH/M.tuberculosis_ERR400373.fastq
musket -inorder -p $NUM_PROC -o $OUT_PATH/S.enterica_ERR230402_corr.fastq  $IN_PATH/S.enterica_ERR230402.fastq
musket -inorder -p $NUM_PROC -o $OUT_PATH/S.cerevisiae_ERR422544_corr.fastq $IN_PATH/S.cerevisiae_ERR422544.fastq
musket -inorder -p $NUM_PROC -o $OUT_PATH/L.pneumophila_SRR801797_corr.fastq $IN_PATH/L.pneumophila_SRR801797.fastq
musket -inorder -p $NUM_PROC -o $OUT_PATH/E.coli_SRR1191655_corr.fastq  $IN_PATH/E.coli_SRR1191655.fastq
musket -inorder -p $NUM_PROC -o $OUT_PATH/E.coli_SRR490124_corr.fastq $IN_PATH/E.coli_SRR490124.fastq
musket -inorder -p $NUM_PROC -o $OUT_PATH/C.elegans_SRX218989_corr.fastq  $IN_PATH/C.elegans_SRX218989.fastq
musket -inorder -p $NUM_PROC -o $OUT_PATH/C.elegans_SRR543736_corr.fastq  $IN_PATH/C.elegans_SRR543736.fastq
musket -inorder -p $NUM_PROC -o $OUT_PATH/D.melanogaster_SRR823377_corr.fastq $IN_PATH/D.melanogaster_SRR823377.fastq
musket -inorder -p $NUM_PROC -o $OUT_PATH/D.melanogaster_SRR988075_corr.fastq $IN_PATH/D.melanogaster_SRR988075.fastq
musket -inorder -p $NUM_PROC -o $OUT_PATH/Human_ERX069715_corr.fastq $IN_PATH/Human_ERX069715.fastq
musket -inorder -p $NUM_PROC -o $OUT_PATH/Human_ERX069504_corr.fastq $IN_PATH/Human_ERX069504.fastq
musket -inorder -p $NUM_PROC -o $OUT_PATH/Human_ERX069505_corr.fastq $IN_PATH/Human_ERX069505.fastq

# MiSeq Data Sets
musket -inorder -p $NUM_PROC -o $OUT_PATH/E.coli_SRR519926_corr.fastq $IN_PATH/E.coli_SRR519926.fastq
musket -inorder -p $NUM_PROC -o $OUT_PATH/M.tuberculosis_SRR1200797_corr.fastq $IN_PATH/M.tuberculosis_SRR1200797.fastq
musket -inorder -p $NUM_PROC -o $OUT_PATH/S.enterica_SRR1203044_corr.fastq $IN_PATH/S.enterica_SRR1203044.fastq
musket -inorder -p $NUM_PROC -o $OUT_PATH/S.enterica_SRR1206093_corr.fastq $IN_PATH/S.enterica_SRR1206093.fastq
musket -inorder -p $NUM_PROC -o $OUT_PATH/L.monocytogenes_SRR1198952_corr.fastq $IN_PATH/L.monocytogenes_SRR1198952.fastq
musket -inorder -p $NUM_PROC -o $OUT_PATH/P.syringae_SRR1119292_corr.fastq $IN_PATH/P.syringae_SRR1119292.fastq
musket -inorder -p $NUM_PROC -o $OUT_PATH/B.dentium_SRR1151311_corr.fastq $IN_PATH/B.dentium_SRR1151311.fastq
musket -inorder -p $NUM_PROC -o $OUT_PATH/E.coli_SRR522163_corr.fastq $IN_PATH/E.coli_SRR522163.fastq
musket -inorder -p $NUM_PROC -o $OUT_PATH/O.tsutsugamushi_SRR1202083_corr.fastq $IN_PATH/O.tsutsugamushi_SRR1202083.fastq
