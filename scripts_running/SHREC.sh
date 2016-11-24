#!/bin/sh

# The following parameters will need to be modified for your particular system.
IN_PATH=/home/Data_Sets
OUT_PATH=/home/SHREC
NUM_PROC=1
JAVA_SPACE=-Xmx940g

# HiSeq Data Sets
java $JAVA_SPACE Shrec -p $NUM_PROC $IN_PATH/M.tuberculosis_ERR400373.fastq $OUT_PATH/M.tuberculosis_ERR400373_corr.fastq
java $JAVA_SPACE Shrec -p $NUM_PROC $IN_PATH/S.enterica_ERR230402.fastq $OUT_PATH/S.enterica_ERR230402_corr.fastq
java $JAVA_SPACE Shrec -p $NUM_PROC $IN_PATH/S.cerevisiae_ERR422544.fastq $OUT_PATH/S.cerevisiae_ERR422544_corr.fastq
java $JAVA_SPACE Shrec -p $NUM_PROC $IN_PATH/L.pneumophila_SRR801797.fastq $OUT_PATH/L.pneumophila_SRR801797_corr.fastq
java $JAVA_SPACE Shrec -p $NUM_PROC $IN_PATH/E.coli_SRR1191655.fastq $OUT_PATH/E.coli_SRR1191655_corr.fastq
java $JAVA_SPACE Shrec -p $NUM_PROC $IN_PATH/E.coli_SRR490124.fastq $OUT_PATH/E.coli_SRR490124_corr.fastq
java $JAVA_SPACE Shrec -p $NUM_PROC $IN_PATH/C.elegans_SRX218989.fastq $OUT_PATH/C.elegans_SRX218989_corr.fastq
java $JAVA_SPACE Shrec -p $NUM_PROC $IN_PATH/C.elegans_SRR543736.fastq $OUT_PATH/C.elegans_SRR543736_corr.fastq
java $JAVA_SPACE Shrec -p $NUM_PROC $IN_PATH/D.melanogaster_SRR823377.fastq $OUT_PATH/D.melanogaster_SRR823377_corr.fastq
java $JAVA_SPACE Shrec -p $NUM_PROC $IN_PATH/D.melanogaster_SRR988075.fastq $OUT_PATH/D.melanogaster_SRR988075_corr.fastq
java $JAVA_SPACE Shrec -p $NUM_PROC $IN_PATH/ERX069715.fastq $OUT_PATH/Human_ERX069715_corr.fastq
java $JAVA_SPACE Shrec -p $NUM_PROC $IN_PATH/ERX069504.fastq $OUT_PATH/Human_ERX069504_corr.fastq
java $JAVA_SPACE Shrec -p $NUM_PROC $IN_PATH/ERX069505.fastq $OUT_PATH/Human_ERX069505_corr.fastq

# MiSeq Data Sets
java $JAVA_SPACE Shrec -p $NUM_PROC $IN_PATH/E.coli_SRR519926.fastq $OUT_PATH/E.coli_SRR519926_corr.fastq
java $JAVA_SPACE Shrec -p $NUM_PROC $IN_PATH/M.tuberculosis_SRR1200797.fastq $OUT_PATH/M.tuberculosis_SRR1200797_corr.fastq
java $JAVA_SPACE Shrec -p $NUM_PROC $IN_PATH/S.enterica_SRR1203044.fastq $OUT_PATH/S.enterica_SRR1203044_corr.fastq
java $JAVA_SPACE Shrec -p $NUM_PROC $IN_PATH/S.enterica_SRR1206093.fastq $OUT_PATH/S.enterica_SRR1206093_corr.fastq
java $JAVA_SPACE Shrec -p $NUM_PROC $IN_PATH/L.monocytogenes_SRR1198952.fastq $OUT_PATH/L.monocytogenes_SRR1198952_corr.fastq
java $JAVA_SPACE Shrec -p $NUM_PROC $IN_PATH/P.syringae_SRR1119292.fastq $OUT_PATH/P.syringae_SRR1119292_corr.fastq
java $JAVA_SPACE Shrec -p $NUM_PROC $IN_PATH/B.dentium_SRR1151311.fastq $OUT_PATH/B.dentium_SRR1151311_corr.fastq
java $JAVA_SPACE Shrec -p $NUM_PROC $IN_PATH/E.coli_SRR522163.fastq $OUT_PATH/E.coli_SRR522163_corr.fastq
java $JAVA_SPACE Shrec -p $NUM_PROC $IN_PATH/O.tsutsugamushi_SRR1202083.fastq $OUT_PATH/O.tsutsugamushi_SRR1202083_corr.fastq
