#Should really fix this by reading in the syndrome table and storing the data
#instead of strings
get_biterr <-  function(row) {
  ntype <- toString(row[1,'nodeType'])
  synd_str <- toString(row[1,'Syndrome']) #e.g. " Chipkill ECC syndrome = 8fd"
  loc <- find_syndrome(synd_str)
  bin<-hex2bin(sprintf('%x',loc[1]))
  numbits <- toString(length(grep('1',bin)))
  return(c(numbits,ntype))
}

find_syndrome <- function(synd_str) {
  synd <- strsplit(synd_str,"= ")[[1]][2]
  #Fix 3 character syndromes for hex2bin, can't remember if it needs nibbles
  if(nchar(synd)==3) {
    synd<-paste('0',synd,sep='')
  }
  #look it up in the syndrome table, based on the row we can tell how many 
  #bits are in error - if the mask has one bit, etc...
  which(syndromes==toupper(synd),arr.ind=TRUE)
}

get_symbols <- function(syndrome) {
  synd<-find_syndrome(syndrome)
  print(synd)
  print(synd[1,'col'])
  print("--")
}
