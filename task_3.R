#!/usr/bin/env Rscript
source('load_data.R')
source('get_memdata.R')
library("BMS") #requires install.packages("BMS")

data <- load_data()
syndromes <- read.table('./data/ECC_correctable_syndromes.txt', header=TRUE, sep=' ')
#Total number of machines - https://piazza.com/class/hqsape7o34yz7?cid=25
#DRAMs = 205632 DIMM * 9 DRAM/DIMM
total_drams<-205632*9
faulty_drams<-0

#Thresholds
# *1 uncorrectable
# *mean correctable 3351-4530. So > 2*((5000/year)*(year/(52.14weeks)))
#We consider: "ECC Error" or "DRAM Parity Error"
#corr_thresh=2*(5000/(52.14))
ndays <- 8
corr_thresh<-ndays*(5000/(365))
select_list=c('CompleteNode','nodeType','Syndrome','Type','Addr','ucc','ecc')
mem_errs <- subset(data, Type =="ECC Error"|Type=="DRAM Parity Error",select=select_list)
#We don't have uptime or repair data, so count each type of error once
#Each DIMM have 8GiB of address space, interleaving? 
#Need to check syndrome table: each symbol corresponds to DRAM,
# so symbol == unique DRAM
for(machine in levels(mem_errs$CompleteNode)) {
  mach_frame <- droplevels(subset(mem_errs, CompleteNode  == machine))
  symbol_list<-list()
  for(syndrome in levels(mach_frame$Syndrome)) {
    if(syndrome!="-1") {
      symbol_list<-c(symbol_list,get_symbols(syndrome))
    }
  }   
  if(nrow(mach_frame) > 0) {
  #Here we make the "no repair" assumption and also only consider symbols
    if(any(mach_frame$ucc == 1) | (table(mach_frame$ecc)['1'][[1]] >= corr_thresh) ){
        faulty_drams <- length(unique(symbol_list))+faulty_drams
    }
  }
}
#not sure about this
print(corr_thresh)
print("Percentage of faulty_drams:")
print(faulty_drams/total_drams)
