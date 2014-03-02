#Gets bits in error, used for Task 2.1
get_biterr <-  function(row) {
  ntype <- toString(row[1,'nodeType'])
  synd_str <- toString(row[1,'Syndrome']) #e.g. " Chipkill ECC syndrome = 8fd"
  numbits <- get_bitsinerr(synd_str)
  return(c(numbits,ntype,strtoi(row[1,'Timestamp'])))
}

find_syndrome <- function(synd_str) {
  synd <- strsplit(synd_str,"= ")[[1]][2]
  #Fix 3 character syndromes for hex2bin, can't remember if it needs nibbles
  if(nchar(synd)<4) {
    for( i in seq(1:(4-nchar(synd)))) {
      synd<-paste('0',synd,sep='')
    }
  }
  #look it up in the syndrome table, based on the row we can tell how many 
  #bits are in error - if the mask has one bit, etc...
  which(syndromes==toupper(synd),arr.ind=TRUE)
}

get_symbol <- function(syndrome) {
  synd<-find_syndrome(syndrome)
  synd[1,"col"]
}

#Helper function that actually returns the number of bits in error
get_bitsinerr <- function(synd_str) {
  loc <- find_syndrome(synd_str)
  bin<-hex2bin(sprintf('%x',loc[1]))
  numbits <- toString(length(grep('1',bin)))
}
