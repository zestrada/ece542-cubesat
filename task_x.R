#!/usr/bin/env Rscript
source('load_data.R')
#Identify faulty motherboards with a threshold of ncompfail exhibiting failures
distinct_fail <- function(data, ncompfail) {
  count <- 0
  for(node in levels(data$CompleteNode)) {  
    nerror <- length(levels(droplevels(data[data$CompleteNode==node,]$Type)))
    if(nerror >= ncompfail) {
      count <- count+1
    }
  }
  count
}

data <- load_data()
ntypes <- length(levels(data$Type))
fail_distribution <- vector()
for(i in seq(1:ntypes)) {
  fail_distribution<-c(fail_distribution,distinct_fail(data,i))
}
print(fail_distribution)
#pdf("task_x.pdf")
#plot(fail_distribution,main="Count of Nodes with Various Types of Errors",xlab="Number of error types",ylab="Number of nodes (log scale)", log='y')
#dev.off()
