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
err_due_faulty_drams<-0
multi_bit_due_faulty_drams<-0

#Thresholds
# *1 uncorrectable
# *mean correctable 3351-4530. So > 2*((5000/year)*(year/(52.14weeks)))
#We consider: "ECC Error" or "DRAM Parity Error"
#corr_thresh=2*(5000/(52.14))
ndays <- 8
total_time<-ndays*24
corr_thresh<-ndays*(5000/(365))
select_list=c('CompleteNode','nodeType','Syndrome','Type','Addr','ucc','ecc')
mem_errs <- subset(data, Type =="ECC Error"|Type=="DRAM Parity Error",select=select_list)
#We don't have uptime or repair data, so count each type of error once
#Each DIMM have 8GiB of address space, interleaving? 
#Need to check syndrome table: each symbol corresponds to DRAM,
# so symbol == unique DRAM
#failures are uniformaly distributed across data center, fengshui study
#assume probability of faults small, failures independent chipkill implicitly
# designed with that assumption in mind
for(machine in levels(mem_errs$CompleteNode)) {
  mach_frame <- droplevels(subset(mem_errs, CompleteNode  == machine & Syndrome
!="-1"))
  if(nrow(mach_frame) <= 0 | !(any(mach_frame$ucc == 1) | (nrow(mach_frame[mach_frame$ecc=="1",]) >= corr_thresh))) { 
    next
  }
  symbol_list<-list()
  for(syndrome in levels(mach_frame$Syndrome)) {
    symbol_list<-c(symbol_list,get_symbol(syndrome))
    loc <- find_syndrome(syndrome)
    bin<-hex2bin(sprintf('%x',loc[1]))
    numbits <- toString(length(grep('1',bin)))
    if(strtoi(numbits) > 1) {
      multi_bit_due_faulty_drams<-1+multi_bit_due_faulty_drams
    }
  }   
  #Here we make the "no repair" assumption and also only consider symbols
  faulty_drams <- length(unique(symbol_list))+faulty_drams
  err_due_faulty_drams <- nrow(mach_frame)+err_due_faulty_drams
}
#not sure about this
print("Percentage of faulty_drams:")
print(faulty_drams/total_drams)

#b.  How MTBF would change if would fix ALL the faulty DRAM?
#    filter DRAMs, subtract number of failures caused by faulty DRAMs
print("MTBF w/o faulty DRAMs")
print(3600*total_time/(nrow(data)-err_due_faulty_drams))

print("Memory MTBF w faulty DRAMs")
print(3600*total_time/nrow(mem_errs))

print("Memory MTBF w/o faulty DRAMs")
print(3600*total_time/(nrow(mem_errs)-err_due_faulty_drams))

print("Percent of multibit errors due to faulty DRAM")
print(100*multi_bit_due_faulty_drams/nrow(mem_errs))
