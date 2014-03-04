#!/usr/bin/env Rscript
source('load_data.R')
#Number of nodes that have this many types of failures
distinct_fail <- function(data, ncompfail) {
  count <- 0
  errs_caused <- 0
  c(count,errs_caused)
}

data <- load_data()
ntypes <- length(levels(data$Type))
fail_distribution <- rep(0,ntypes)
errs_caused <- rep(0,ntypes)
for(node in levels(data$CompleteNode)) {  
  nerror <- length(levels(droplevels(data[data$CompleteNode==node,]$Type)))
  fail_distribution[[nerror]] <- fail_distribution[[nerror]] +1
  errs_caused[[nerror]] <- errs_caused[[nerror]] + nrow(data[data$CompleteNode==node,])
}
print(fail_distribution)
fail_mat<-matrix(fail_distribution,ncol=length(fail_distribution),nrow=1)
#pdf("task_x.pdf")
# plot(fail_distribution,main="Count of Nodes with Various Types of Errors",xlab="Number of error types",ylab="Number of nodes (log scale)", log='y',xlim=c(1,8))
#dev.off()

#pdf("task_x_types.pdf")
# barplot(errs_caused,xlab="Number of Error Types",ylab="Number of Errors",names.arg=seq(1:length(errs_caused)),main="Number of Errors Caused by Nodes Exhibiting Error Types")
#dev.off()

