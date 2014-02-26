get_biterr <-  function(row) {
  ntype <- row['nodeType']
  synd_str <- row['Syndrome'] #The syndrome string
  if(syndStr!='-1') {
    print(row)
    return(NA)
  }
  synd <- strsplit(synd_str,"= ")[[1]][2]
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
    #TODO Need to organize by type
  }
}
