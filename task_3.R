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
# *mean correctable 3351-4530. So > (5000/year)*(year/(2*52.14weeks))
#We consider: "ECC Error" or "DRAM Parity Error"
corr_thresh=5000/(2*52.14)
mem_errs <- subset(data, data$Type=="ECC Error" | data$Type=="DRAM Parity Error")

#We don't have uptime or repair data, so count each type of error once
#Need to check syndrome table: each symbol corresponds to DRAM,
# so symbol == unique DRAM
for(machine in levels(mem_errs$CompleteNode)) {
  mach_frame <- subset(data, data$CompleteNode  == machine)
  symbol_list<-list()
  for(syndrome in levels(mach_frame$Syndrome)) {
    #No matter how I tried, I couldn't filter this thing out
    if(syndrome!="-1") {
      symbol_list<-c(symbol_list,get_symbols(syndrome))
    }
  }   
  print(symbol_list)
  quit()
}
