#!/bin/sh

# The following parameters will need to be modified for your particular system.
IN_PATH=/home/Data_Sets
CORR_PATH=/home/Program
GENOME_PATH=/home/Genomes

# HiSeq Data Sets
readSearch $GENOME_PATH/NC_000962.fna $IN_PATH/M.tuberculosis_ERR400373.fastq $CORR_PATH/M.tuberculosis_ERR400373_corr.fastq
readSearch $GENOME_PATH/NC_011083.fna $IN_PATH/S.enterica_ERR230402.fastq $CORR_PATH/S.enterica_ERR230402_corr.fastq
readSearch $GENOME_PATH/S.cerevisiae_R64-1-1 $IN_PATH/S.cerevisiae_ERR422544.fastq $CORR_PATH/S.cerevisiae_ERR422544_corr.fastq
readSearch $GENOME_PATH/NC_002942.fna $IN_PATH/L.pneumophila_SRR801797.fastq $CORR_PATH/L.pneumophila_SRR801797_corr.fastq
readSearch $GENOME_PATH/NC_000913.fna $IN_PATH/E.coli_SRR1191655.fastq $CORR_PATH/E.coli_SRR1191655_corr.fastq
readSearch $GENOME_PATH/NC_000913.fna $IN_PATH/E.coli_SRR490124.fastq $CORR_PATH/E.coli_SRR490124_corr.fastq
readSearch $GENOME_PATH/c_elegans.WS222.genomic.fa $IN_PATH/C.elegans_SRX218989.fastq $CORR_PATH/C.elegans_SRX218989_corr.fastq
readSearch $GENOME_PATH/c_elegans.WS222.genomic.fa $IN_PATH/C.elegans_SRR543736.fastq $CORR_PATH/C.elegans_SRR543736_corr.fastq
readSearch $GENOME_PATH/D.melanogaster_Release5_48 $IN_PATH/D.melanogaster_SRR823377.fastq $CORR_PATH/D.melanogaster_SRR823377_corr.fastq
readSearch $GENOME_PATH/D.melanogaster_Release5_48 $IN_PATH/D.melanogaster_SRR988075.fastq $CORR_PATH/D.melanogaster_SRR988075_corr.fastq
readSearch $GENOME_PATH/GRCh38_top_level.fa $IN_PATH/Human_ERX069715.fastq $CORR_PATH/Human_ERX069715_corr.fastq
readSearch $GENOME_PATH/GRCh38_top_level.fa $IN_PATH/Human_ERX069504.fastq $CORR_PATH/Human_ERX069504_corr.fastq
readSearch $GENOME_PATH/GRCh38_top_level.fa $IN_PATH/Human_ERX069505.fastq $CORR_PATH/Human_ERX069505_corr.fastq

# MiSeq Data Sets
readSearch $GENOME_PATH/NC_000913.fna $IN_PATH/E.coli_SRR519926.fastq $CORR_PATH/E.coli_SRR519926_corr.fastq
readSearch $GENOME_PATH/NC_000962.fna $IN_PATH/M.tuberculosis_SRR1200797.fastq $CORR_PATH/M.tuberculosis_SRR1200797_corr.fastq
readSearch $GENOME_PATH/NC_011083.fna $IN_PATH/S.enterica_SRR1203044.fastq $CORR_PATH/S.enterica_SRR1203044_corr.fastq
readSearch $GENOME_PATH/NC_011083.fna $IN_PATH/S.enterica_SRR1206093.fastq $CORR_PATH/S.enterica_SRR1206093_corr.fastq
readSearch $GENOME_PATH/NC_017546.fna $IN_PATH/L.monocytogenes_SRR1198952.fastq $CORR_PATH/L.monocytogenes_SRR1198952_corr.fastq
readSearch $GENOME_PATH/NC_007005.fna $IN_PATH/P.syringae_SRR1119292.fastq $CORR_PATH/P.syringae_SRR1119292_corr.fastq
readSearch $GENOME_PATH/NC_013714.fna $IN_PATH/B.dentium_SRR1151311.fastq $CORR_PATH/B.dentium_SRR1151311_corr.fastq
readSearch $GENOME_PATH/NC_000913.fna $IN_PATH/E.coli_SRR522163.fastq $CORR_PATH/E.coli_SRR522163_corr.fastq
readSearch $GENOME_PATH/NC_009488.fna $IN_PATH/O.tsutsugamushi_SRR1202083.fastq $CORR_PATH/O.tsutsugamushi_SRR1202083_corr.fastq
