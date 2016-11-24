#!/bin/sh

# Insert and run this script in the directory that you want to download the files.

# Bacterial genomes
wget ftp://ftp.ncbi.nih.gov/genomes/Bacteria/Mycobacterium_tuberculosis_H37Rv_uid57777/NC_000962.fna
wget ftp://ftp.ncbi.nih.gov/genomes/Bacteria/Salmonella_enterica_serovar_Heidelberg_SL476_uid58973/NC_011083.fna
wget ftp://ftp.ncbi.nih.gov/genomes/Bacteria/Legionella_pneumophila_Philadelphia_1_uid57609/NC_002942.fna
wget ftp://ftp.ncbi.nih.gov/genomes/Bacteria/Escherichia_coli_K_12_substr__MG1655_uid57779/NC_000913.fna
wget ftp://ftp.ncbi.nih.gov/genomes/Bacteria/Listeria_monocytogenes_FSL_R2_561_uid54441/NC_017546.fna
wget ftp://ftp.ncbi.nih.gov/genomes/Bacteria/Pseudomonas_syringae_B728a_uid57931/NC_007005.fna
wget ftp://ftp.ncbi.nih.gov/genomes/Bacteria/Bifidobacterium_dentium_Bd1_uid43091/NC_013714.fna
wget ftp://ftp.ncbi.nih.gov/genomes/Bacteria/Orientia_tsutsugamushi_Boryong_uid61621/NC_009488.fna

# C.elegans WS222
wget ftp://ftp.wormbase.org/pub/wormbase/species/c_elegans/sequence/genomic/c_elegans.WS222.genomic.fa.gz
gunzip c_elegans.WS222.genomic.fa.gz

# S.cerevisiae R64-1-1
wget ftp://ftp.ncbi.nih.gov/genomes/Fungi/Saccharomyces_cerevisiae_uid128/NC_001133.fna
wget ftp://ftp.ncbi.nih.gov/genomes/Fungi/Saccharomyces_cerevisiae_uid128/NC_001134.fna
wget ftp://ftp.ncbi.nih.gov/genomes/Fungi/Saccharomyces_cerevisiae_uid128/NC_001135.fna
wget ftp://ftp.ncbi.nih.gov/genomes/Fungi/Saccharomyces_cerevisiae_uid128/NC_001136.fna
wget ftp://ftp.ncbi.nih.gov/genomes/Fungi/Saccharomyces_cerevisiae_uid128/NC_001137.fna
wget ftp://ftp.ncbi.nih.gov/genomes/Fungi/Saccharomyces_cerevisiae_uid128/NC_001138.fna
wget ftp://ftp.ncbi.nih.gov/genomes/Fungi/Saccharomyces_cerevisiae_uid128/NC_001139.fna
wget ftp://ftp.ncbi.nih.gov/genomes/Fungi/Saccharomyces_cerevisiae_uid128/NC_001140.fna
wget ftp://ftp.ncbi.nih.gov/genomes/Fungi/Saccharomyces_cerevisiae_uid128/NC_001141.fna
wget ftp://ftp.ncbi.nih.gov/genomes/Fungi/Saccharomyces_cerevisiae_uid128/NC_001142.fna
wget ftp://ftp.ncbi.nih.gov/genomes/Fungi/Saccharomyces_cerevisiae_uid128/NC_001143.fna
wget ftp://ftp.ncbi.nih.gov/genomes/Fungi/Saccharomyces_cerevisiae_uid128/NC_001144.fna
wget ftp://ftp.ncbi.nih.gov/genomes/Fungi/Saccharomyces_cerevisiae_uid128/NC_001145.fna
wget ftp://ftp.ncbi.nih.gov/genomes/Fungi/Saccharomyces_cerevisiae_uid128/NC_001146.fna
wget ftp://ftp.ncbi.nih.gov/genomes/Fungi/Saccharomyces_cerevisiae_uid128/NC_001147.fna
wget ftp://ftp.ncbi.nih.gov/genomes/Fungi/Saccharomyces_cerevisiae_uid128/NC_001224.fna
cat NC_001133.fna NC_001134.fna NC_001135.fna NC_001136.fna NC_001137.fna NC_001138.fna NC_001139.fna NC_001140.fna NC_001141.fna NC_001142.fna NC_001143.fna NC_001144.fna NC_001145.fna NC_001146.fna NC_001147.fna NC_001224.fna > S.cerevisiae_R64-1-1

# D.melanogaster Release5 48
wget ftp://ftp.ncbi.nih.gov/genomes/Drosophila_melanogaster/RELEASE_5_48/CHR_3/NT_033777.fna
wget ftp://ftp.ncbi.nih.gov/genomes/Drosophila_melanogaster/RELEASE_5_48/CHR_2/NT_033778.fna
wget ftp://ftp.ncbi.nih.gov/genomes/Drosophila_melanogaster/RELEASE_5_48/CHR_2/NT_033779.fna
wget ftp://ftp.ncbi.nih.gov/genomes/Drosophila_melanogaster/RELEASE_5_48/CHR_3/NT_037436.fna
wget ftp://ftp.ncbi.nih.gov/genomes/Drosophila_melanogaster/RELEASE_5_48/CHR_4/NC_004353.fna
wget ftp://ftp.ncbi.nih.gov/genomes/Drosophila_melanogaster/RELEASE_5_48/CHR_X/NC_004354.fna
cat NT_033777.fna NT_033779.fna NT_033778.fna NT_037436.fna NC_004353.fna NC_004354.fna > D.melanogaster_Release5_48

# Human genome build 38
wget ftp://ftp.ncbi.nih.gov/genomes/H_sapiens/special_requests/GRCh38_top_level.fa.gz
gunzip GRCh38_top_level.fa.gz