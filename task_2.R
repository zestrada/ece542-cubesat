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

#Two timestamp vectors: one for single bit errors, antoher for multi_bit
single_bit_times<-vector()
multi_bit_times<-vector()

for( i in 1:nrow(data)) {
  row = data[i,]
  if(row['Syndrome'] == '-1')
    next
  #Get this data in a vector:
  #numbits, ntype, TimeStamp
  errs <- get_biterr(row)
  bit_row <- errs[1]
  node_type <- errs[2]
  timestamp <- errs[3]
  #Only count single, double quadruple - bunch everything else up
  if(strtoi(bit_row) == 1) {
    single_bit_times<-append(single_bit_times,timestamp)
  } else {
    multi_bit_times<-append(multi_bit_times,timestamp)
  }
  if(strtoi(bit_row) > 4) {
    bit_row="5+"
  }
  bit_counts[bit_row,node_type] <- bit_counts[bit_row,node_type] + 1 
}

bit_counts <- cbind(bit_counts,rowSums(bit_counts))
dimnames(bit_counts)[[2]][[length(colnames)+1]] <- "ALL"
bit_percentages <- prop.table(bit_counts,2)
print("Memory error breakdown:")
print(bit_percentages)

#Part 2
#How frequent (time) are multiple (>1) bit errors? Provide one or
#two charts of your choice to motivate your answer. Do different types
#of nodes behave differently?
ndays<-8
total_time<-ndays*24

#Now sum all rows except the first
print("Frequency of multi-bit errors 1/hr")
multi_bit_hr<-print(colSums(bit_counts[-1,])/total_time)

#Part 3
#How many uncorrectable errors would Blue Waters have if using
#only ECC? How effective is Chipkill w.r.t ECC?
#- Compare the FIT and MTBF (only for uncorrectable errors) considering the same
#  system with and without Chipkill. Motivate the answer with 2-3 bullets.

#looks like 1 uncorrectable error
#> print(data[data$ucc!=0,])
#      EntryNum  Timestamp nodeType CompleteNode Core Bank Syndrome      Type
#10581    10581 1349896318  compute   c5-4c2s3n3   24    4       -1 ECC Error
#           Addr Socket Apic err_CPU_bit scrub L3_low L3_high ucc ecc pcc
#10581 dcd371590      1   28           0     0      1       1   1   0   0
#      miscInfo ue over                Date weeknumber
#10581        0  0    0 2012-10-10 14:11:58         41

#Reusing our standard definition of MTBF:
#One FIT=1/10^9 hours
ucorr_errs <- matrix(0,2,2,dimnames=list(c('Chipkill','No Chipkill'),c('FIT/Mbit','MTBF')))
per_mbit<-(8*1024*8) #8GB, 1024GB to MB, 8bit to B

print('These are system wide, MTBFs are in hours')
ucorr_errs['Chipkill','FIT/Mbit'] <- (1/total_time)*1E9*(1/per_mbit)
ucorr_errs['Chipkill','MTBF'] <- total_time
ucorr_errs['No Chipkill','FIT/Mbit'] <- ((1+length(multi_bit_times))/total_time)*1E9*(1/per_mbit)
ucorr_errs['No Chipkill','MTBF'] <- ((1+length(multi_bit_times))/total_time)
print(ucorr_errs)
#Really R, sprintf but no printf? :-P
print(sprintf("Uncorrectable Errors if only using ECC: %d",length(multi_bit_times)))
