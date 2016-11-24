#!/bin/sh

# The following parameters will need to be modified for your particular system.
IN_PATH=/home/Data_Sets
OUT_PATH=/home/SGA
KMER_LENGTH=41
NUM_PROC=1

# HiSeq Data Sets
sga preprocess --pe-mode 2 --permute-ambiguous --no-primer-check -m 1 -o $OUT_PATH/M.tuberculosis_ERR400373_temp.fastq $IN_PATH/M.tuberculosis_ERR400373.fastq
sga index -a ropebwt -t $NUM_PROC $OUT_PATH/M.tuberculosis_ERR400373_temp.fastq
sga correct -k $KMER_LENGTH -t $NUM_PROC -o $OUT_PATH/M.tuberculosis_ERR400373_corr.fastq $OUT_PATH/M.tuberculosis_ERR400373_temp.fastq

sga preprocess --pe-mode 2 --permute-ambiguous --no-primer-check -m 1 -o $OUT_PATH/S.enterica_ERR230402_temp.fastq $IN_PATH/S.enterica_ERR230402.fastq
sga index -a ropebwt -t $NUM_PROC $OUT_PATH/S.enterica_ERR230402_temp.fastq
sga correct -k $KMER_LENGTH -t $NUM_PROC -o $OUT_PATH/S.enterica_ERR230402_corr.fastq $OUT_PATH/S.enterica_ERR230402_temp.fastq

sga preprocess --pe-mode 2 --permute-ambiguous --no-primer-check -m 1 -o $OUT_PATH/S.cerevisiae_ERR422544_temp.fastq $IN_PATH/S.cerevisiae_ERR422544.fastq
sga index -a ropebwt -t $NUM_PROC $OUT_PATH/S.cerevisiae_ERR422544_temp.fastq
sga correct -k $KMER_LENGTH -t $NUM_PROC -o $OUT_PATH/S.cerevisiae_ERR422544_corr.fastq $OUT_PATH/S.cerevisiae_ERR422544_temp.fastq

sga preprocess --pe-mode 2 --permute-ambiguous --no-primer-check -m 1 -o $OUT_PATH/L.pneumophila_SRR801797_temp.fastq $IN_PATH/L.pneumophila_SRR801797.fastq
sga index -a ropebwt -t $NUM_PROC $OUT_PATH/L.pneumophila_SRR801797_temp.fastq
sga correct -k $KMER_LENGTH -t $NUM_PROC -o $OUT_PATH/L.pneumophila_SRR801797_corr.fastq $OUT_PATH/L.pneumophila_SRR801797_temp.fastq

sga preprocess --pe-mode 2 --permute-ambiguous --no-primer-check -m 1 -o $OUT_PATH/E.coli_SRR1191655_temp.fastq $IN_PATH/E.coli_SRR1191655.fastq
sga index -a ropebwt -t $NUM_PROC $OUT_PATH/E.coli_SRR1191655_temp.fastq
sga correct -k $KMER_LENGTH -t $NUM_PROC -o $OUT_PATH/E.coli_SRR1191655_corr.fastq $OUT_PATH/E.coli_SRR1191655_temp.fastq

sga preprocess --pe-mode 2 --permute-ambiguous --no-primer-check -m 1 -o $OUT_PATH/E.coli_SRR490124_temp.fastq $IN_PATH/E.coli_SRR490124.fastq
sga index -a ropebwt -t $NUM_PROC $OUT_PATH/E.coli_SRR490124_temp.fastq
sga correct -k $KMER_LENGTH -t $NUM_PROC -o $OUT_PATH/E.coli_SRR490124_corr.fastq $OUT_PATH/E.coli_SRR490124_temp.fastq

sga preprocess --pe-mode 2 --permute-ambiguous --no-primer-check -m 1 -o $OUT_PATH/C.elegans_SRX218989_temp.fastq $IN_PATH/C.elegans_SRX218989.fastq
sga index -a ropebwt -t $NUM_PROC $OUT_PATH/C.elegans_SRX218989_temp.fastq
sga correct -k $KMER_LENGTH -t $NUM_PROC -o $OUT_PATH/C.elegans_SRX218989_corr.fastq $OUT_PATH/C.elegans_SRX218989_temp.fastq

sga preprocess --pe-mode 2 --permute-ambiguous --no-primer-check -m 1 -o $OUT_PATH/C.elegans_SRR543736_temp.fastq $IN_PATH/C.elegans_SRR543736.fastq
sga index -a ropebwt -t $NUM_PROC $OUT_PATH/C.elegans_SRR543736_temp.fastq
sga correct -k $KMER_LENGTH -t $NUM_PROC -o $OUT_PATH/C.elegans_SRR543736_corr.fastq $OUT_PATH/C.elegans_SRR543736_temp.fastq

sga preprocess --pe-mode 2 --permute-ambiguous --no-primer-check -m 1 -o $OUT_PATH/D.melanogaster_SRR823377_temp.fastq $IN_PATH/D.melanogaster_SRR823377.fastq
sga index -a ropebwt -t $NUM_PROC $OUT_PATH/D.melanogaster_SRR823377_temp.fastq
sga correct -k $KMER_LENGTH -t $NUM_PROC -o $OUT_PATH/D.melanogaster_SRR823377_corr.fastq $OUT_PATH/D.melanogaster_SRR823377_temp.fastq

sga preprocess --pe-mode 2 --permute-ambiguous --no-primer-check -m 1 -o $OUT_PATH/D.melanogaster_SRR988075_temp.fastq $IN_PATH/D.melanogaster_SRR988075.fastq
sga index -a ropebwt -t $NUM_PROC $OUT_PATH/D.melanogaster_SRR988075_temp.fastq
sga correct -k $KMER_LENGTH -t $NUM_PROC -o $OUT_PATH/D.melanogaster_SRR988075_corr.fastq $OUT_PATH/D.melanogaster_SRR988075_temp.fastq

sga preprocess --pe-mode 2 --permute-ambiguous --no-primer-check -m 1 -o $OUT_PATH/Human_ERX069715_temp.fastq $IN_PATH/Human_ERX069715.fastq
sga index -a ropebwt -t $NUM_PROC $OUT_PATH/Human_ERX069715_temp.fastq
sga correct -k $KMER_LENGTH -t $NUM_PROC -o $OUT_PATH/Human_ERX069715_corr.fastq $OUT_PATH/Human_ERX069715_temp.fastq

sga preprocess --pe-mode 2 --permute-ambiguous --no-primer-check -m 1 -o $OUT_PATH/Human_ERX069504_temp.fastq $IN_PATH/Human_ERX069504.fastq
sga index -a ropebwt -t $NUM_PROC $OUT_PATH/Human_ERX069504_temp.fastq
sga correct -k $KMER_LENGTH -t $NUM_PROC -o $OUT_PATH/Human_ERX069504_corr.fastq $OUT_PATH/Human_ERX069504_temp.fastq

sga preprocess --pe-mode 2 --permute-ambiguous --no-primer-check -m 1 -o $OUT_PATH/Human_ERX069505_temp.fastq $IN_PATH/Human_ERX069505.fastq
sga index -a ropebwt -t $NUM_PROC $OUT_PATH/Human_ERX069505_temp.fastq
sga correct -k $KMER_LENGTH -t $NUM_PROC -o $OUT_PATH/Human_ERX069505_corr.fastq $OUT_PATH/Human_ERX069505_temp.fastq

# MiSeq Data Sets

sga preprocess --pe-mode 2 --permute-ambiguous --no-primer-check -m 1 -o $OUT_PATH/E.coli_SRR519926_temp.fastq $IN_PATH/E.coli_SRR519926.fastq
sga index -a ropebwt -t $NUM_PROC $OUT_PATH/E.coli_SRR519926_temp.fastq
sga correct -k $KMER_LENGTH -t $NUM_PROC -o $OUT_PATH/E.coli_SRR519926_corr.fastq $OUT_PATH/E.coli_SRR519926_temp.fastq

sga preprocess --pe-mode 2 --permute-ambiguous --no-primer-check -m 1 -o $OUT_PATH/M.tuberculosis_SRR1200797_temp.fastq $IN_PATH/M.tuberculosis_SRR1200797.fastq
sga index -a ropebwt -t $NUM_PROC $OUT_PATH/M.tuberculosis_SRR1200797_temp.fastq
sga correct -k $KMER_LENGTH -t $NUM_PROC -o $OUT_PATH/M.tuberculosis_SRR1200797_corr.fastq $OUT_PATH/M.tuberculosis_SRR1200797_temp.fastq

sga preprocess --pe-mode 2 --permute-ambiguous --no-primer-check -m 1 -o $OUT_PATH/S.enterica_SRR1203044_temp.fastq $IN_PATH/S.enterica_SRR1203044.fastq
sga index -a ropebwt -t $NUM_PROC $OUT_PATH/S.enterica_SRR1203044_temp.fastq
sga correct -k $KMER_LENGTH -t $NUM_PROC -o $OUT_PATH/S.enterica_SRR1203044_corr.fastq $OUT_PATH/S.enterica_SRR1203044_temp.fastq

sga preprocess --pe-mode 2 --permute-ambiguous --no-primer-check -m 1 -o $OUT_PATH/S.enterica_SRR1206093_temp.fastq $IN_PATH/S.enterica_SRR1206093.fastq
sga index -a ropebwt -t $NUM_PROC $OUT_PATH/S.enterica_SRR1206093_temp.fastq
sga correct -k $KMER_LENGTH -t $NUM_PROC -o $OUT_PATH/S.enterica_SRR1206093_corr.fastq $OUT_PATH/S.enterica_SRR1206093_temp.fastq

sga preprocess --pe-mode 2 --permute-ambiguous --no-primer-check -m 1 -o $OUT_PATH/L.monocytogenes_SRR1198952_temp.fastq $IN_PATH/L.monocytogenes_SRR1198952.fastq
sga index -a ropebwt -t $NUM_PROC $OUT_PATH/L.monocytogenes_SRR1198952_temp.fastq
sga correct -k $KMER_LENGTH -t $NUM_PROC -o $OUT_PATH/L.monocytogenes_SRR1198952_corr.fastq $OUT_PATH/L.monocytogenes_SRR1198952_temp.fastq

sga preprocess --pe-mode 2 --permute-ambiguous --no-primer-check -m 1 -o $OUT_PATH/P.syringae_SRR1119292_temp.fastq $IN_PATH/P.syringae_SRR1119292.fastq
sga index -a ropebwt -t $NUM_PROC $OUT_PATH/P.syringae_SRR1119292_temp.fastq
sga correct -k $KMER_LENGTH -t $NUM_PROC -o $OUT_PATH/P.syringae_SRR1119292_corr.fastq $OUT_PATH/P.syringae_SRR1119292_temp.fastq

sga preprocess --pe-mode 2 --permute-ambiguous --no-primer-check -m 1 -o $OUT_PATH/B.dentium_SRR1151311_temp.fastq $IN_PATH/B.dentium_SRR1151311.fastq
sga index -a ropebwt -t $NUM_PROC $OUT_PATH/B.dentium_SRR1151311_temp.fastq
sga correct -k $KMER_LENGTH -t $NUM_PROC -o $OUT_PATH/B.dentium_SRR1151311_corr.fastq $OUT_PATH/B.dentium_SRR1151311_temp.fastq

sga preprocess --pe-mode 2 --permute-ambiguous --no-primer-check -m 1 -o $OUT_PATH/E.coli_SRR522163_temp.fastq $IN_PATH/E.coli_SRR522163.fastq
sga index -a ropebwt -t $NUM_PROC $OUT_PATH/E.coli_SRR522163_temp.fastq
sga correct -k $KMER_LENGTH -t $NUM_PROC -o $OUT_PATH/E.coli_SRR522163_corr.fastq $OUT_PATH/E.coli_SRR522163_temp.fastq

sga preprocess --pe-mode 2 --permute-ambiguous --no-primer-check -m 1 -o $OUT_PATH/O.tsutsugamushi_SRR1202083_temp.fastq $IN_PATH/O.tsutsugamushi_SRR1202083.fastq
sga index -a ropebwt -t $NUM_PROC $OUT_PATH/O.tsutsugamushi_SRR1202083_temp.fastq
sga correct -k $KMER_LENGTH -t $NUM_PROC -o $OUT_PATH/O.tsutsugamushi_SRR1202083_corr.fastq $OUT_PATH/O.tsutsugamushi_SRR1202083_temp.fastq
