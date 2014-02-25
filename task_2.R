#!/usr/bin/env Rscript
source('load_data.R')
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

for (level in levels(data$Syndrome)) {
  #I gave up on regex capture
  #synd <- regexpr("=\\s+(?<synd>\\w+)", level, perl=TRUE)[[1]]
  synd <- strsplit(level,"= ")[[1]][2]
  #For 2, 3, 4 bit errors
  if(nchar(synd)>=3) {
    #Fix 3 character syndromes for hex2bin
    if(nchar(synd)==3) {
      synd<-paste('0',synd,sep='')
    }
    #look it up in the syndrome table, based on the row we can tell how many 
    #bits are in error - if the mask has one bit, etc...
    loc<-which(syndromes==toupper(synd),arr.ind=TRUE)
    bin<-hex2bin(sprintf('%x',loc[1]))
    numbits = length(grep('1',bin))
  }
}
