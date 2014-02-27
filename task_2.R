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
#Probably should find a way to do this by using a function to transform the 
#syndrome column"5+")
rownames <- c(seq(1:4),"5+")
colnames <- levels(data$nodeType)
bit_counts <- matrix(0,length(rownames),length(colnames))
dimnames(bit_counts) <- list(rownames,colnames)

for( i in 1:nrow(data)) {
  row = data[i,]
  if(row['Syndrome'] == '-1')
    next
  errs <- get_biterr(row)
  bit_row <- errs[1]
  #Only count single, double quadruple - bunch everything else up
  if(strtoi(bit_row) > 4) {
    bit_row="5+"
  }
  bit_counts[bit_row,errs[2]] <- bit_counts[bit_row,errs[2]] + 1 
}

bit_counts <- cbind(bit_counts,rowSums(bit_counts))
dimnames(bit_counts)[[2]][[length(colnames)]] <- "ALL"
bit_percentages <- prop.table(bit_counts,2)
print(bit_percentages)

#Part 2
#How frequent (time) are multiple (>1) bit errors? Provide one or
#two charts of your choice to motivate your answer. Do different types
#of nodes behave differently?
