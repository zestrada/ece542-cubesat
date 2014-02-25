#!/usr/bin/env Rscript
source('load_data.R')

data <- load_data() 
#Looks like we have the syndromes corresponding to x8, so let's assume that's
#what we have
#2.13.1 (page 246)
syndromes <- read.table('./data/ECC_correctable_syndromes.txt', header=TRUE, sep=' ')


#Part 1 - Breakdown of the memory errors % in Single, dual, triple,
#         quadruple bit errors 
#  Use a table to summarize the data, for all node types (ALL, compute, gpu,
#   service)

for (level in levels(data$Syndrome)) {
  #I gave up on regex capture
  #synd <- regexpr("=\\s+(?<synd>\\w+)", level, perl=TRUE)[[1]]
  synd <- strsplit(level,"= ")[[1]][2]
  if(nchar(synd)==4) {
    print(synd)
    #look it up in the syndrome table, based on the row we can tell how many 
    #bits are in error - if the mask has one bit, etc...
  }
}
