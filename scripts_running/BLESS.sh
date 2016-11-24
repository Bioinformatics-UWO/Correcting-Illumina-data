#!/bin/sh

# The following parameters will need to be modified for your particular system.
IN_PATH=/home/Data_Sets
OUT_PATH=/home/BLESS

# HiSeq Data Sets
bless -read $IN_PATH/M.tuberculosis_ERR400373.fastq -notrim -prefix $OUT_PATH/M.tuberculosis_ERR400373 -kmerlength 19
bless -read $IN_PATH/S.enterica_ERR230402.fastq -notrim -prefix $OUT_PATH/S.enterica_ERR230402 -kmerlength 19
bless -read $IN_PATH/S.cerevisiae_ERR422544.fastq -notrim -prefix $OUT_PATH/S.cerevisiae_ERR422544 -kmerlength 19
bless -read $IN_PATH/L.pneumophila_SRR801797.fastq -notrim -prefix $OUT_PATH/L.pneumophila_SRR801797 -kmerlength 19
bless -read $IN_PATH/E.coli_SRR1191655.fastq -notrim -prefix $OUT_PATH/E.coli_SRR1191655 -kmerlength 19
bless -read $IN_PATH/E.coli_SRR490124.fastq -notrim -prefix $OUT_PATH/E.coli_SRR490124 -kmerlength 19
bless -read $IN_PATH/C.elegans_SRX218989.fastq -notrim -prefix $OUT_PATH/C.elegans_SRX218989 -kmerlength 21
bless -read $IN_PATH/C.elegans_SRR543736.fastq -notrim -prefix $OUT_PATH/C.elegans_SRR543736 -kmerlength 21
bless -read $IN_PATH/D.melanogaster_SRR823377.fastq -notrim -prefix $OUT_PATH/D.melanogaster_SRR823377 -kmerlength 21
bless -read $IN_PATH/D.melanogaster_SRR988075.fastq -notrim -prefix $OUT_PATH/D.melanogaster_SRR988075 -kmerlength 21
bless -read $IN_PATH/Human_ERX069715.fastq -notrim -prefix $OUT_PATH/Human_ERX069715_corr.fastq -kmerlength 23
bless -read $IN_PATH/Human_ERX069504.fastq -notrim -prefix $OUT_PATH/Human_ERX069504_corr.fastq -kmerlength 23
bless -read $IN_PATH/Human_ERX069505.fastq -notrim -prefix $OUT_PATH/Human_ERX069505_corr.fastq -kmerlength 23

# MiSeq Data Sets
bless -read $IN_PATH/E.coli_SRR519926.fastq -notrim -prefix $OUT_PATH/E.coli_SRR519926 -kmerlength 19
bless -read $IN_PATH/M.tuberculosis_SRR1200797.fastq -notrim -prefix $OUT_PATH/M.tuberculosis_SRR1200797 -kmerlength 19
bless -read $IN_PATH/S.enterica_SRR1203044.fastq -notrim -prefix $OUT_PATH/S.enterica_SRR1203044 -kmerlength 19
bless -read $IN_PATH/S.enterica_SRR1206093.fastq -notrim -prefix $OUT_PATH/S.enterica_SRR1206093 -kmerlength 19
bless -read $IN_PATH/L.monocytogenes_SRR1198952.fastq -notrim -prefix $OUT_PATH/L.monocytogenes_SRR1198952 -kmerlength 19
bless -read $IN_PATH/P.syringae_SRR1119292.fastq -notrim -prefix $OUT_PATH/P.syringae_SRR1119292 -kmerlength 19
bless -read $IN_PATH/B.dentium_SRR1151311.fastq -notrim -prefix $OUT_PATH/B.dentium_SRR1151311 -kmerlength 19
bless -read $IN_PATH/E.coli_SRR522163.fastq -notrim -prefix $OUT_PATH/E.coli_SRR522163 -kmerlength 19
bless -read $IN_PATH/O.tsutsugamushi_SRR1202083.fastq -notrim -prefix $OUT_PATH/O.tsutsugamushi_SRR1202083 -kmerlength 19
