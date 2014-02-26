#!/usr/bin/env Rscript
source('load_data.R')
source('get_memdata.R')
library("BMS") #requires install.packages("BMS")

data <- load_data()
#Looks like we have the syndromes corresponding to x8, so let's assume that's
#what we have
#2.13.1 (page 246)
syndromes <- read.table('./data/ECC_correctable_syndromes.txt', header=TRUE, sep=' ')
#syndromes <- read.table('./data/Table131_x4_ECC_Correctable_syndromes', header=TRUE, sep=' ', skip_col=1)


#Part 1 - Breakdown of the memory errors % in Single, dual, triple,
#         quadruple bit errors 
#  Use a table to summarize the data, for all node types (ALL, compute, gpu,
#   service)

#by(data, list(nodeType=data$nodeType, Syndrome=data$Syndrome), get_biterr)
#bit_counts <- data.frame(type=character(),Bits.In.Error=integer())
#df <- data[data$Syndrome!='-1',]
#apply(data[data$Syndrome!='-1',], 1, get_biterr)
#Gave up on apply, moving to sequential. This is likely the wrong way to do this
rownames <- seq(1:4)
colnames <- levels(data$nodeType)
bit_counts <- matrix(0,length(rownames),length(colnames))
dimnames(bit_counts) <- list(rownames,colnames)

for( i in 1:nrow(data)) {
  row = data[i,]
  if(row['Syndrome'] == '-1')
    next
  errs <- get_biterr(row)
  print(errs)
  bit_counts[errs[0],errs[1]] <- bit_counts[errs[0],errs[1]] + 1
  print(bit_counts)
  quit()
}
