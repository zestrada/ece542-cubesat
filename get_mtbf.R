# Task 0.3 functions.

# Gets the mean time between failures for a given type,
# or for all of the data if the all parameter is TRUE.
get_mtbf <- function(data, type, all=FALSE) {
  if(all==FALSE) {
    data <- data[data$nodeType == type,]    
  }
  # I define mtbf as <8 days> / <number of failures>.
  total_time <- 8 * 24
  num_failures <- nrow(data)
  
  if(num_failures == 0) {
    return(Inf)
  }
  
  total_time / num_failures
}

# Function called on the data to get all MTBF values from it.
get_all_mtbfs <- function(data) {
  nodeType <- vector()
  mtbf <- vector()
  for (level in levels(data$nodeType)) {
    nodeType <- c(nodeType, level)
    mtbf <- c(mtbf, get_mtbf(data, level))
  }
  nodeType <- c(nodeType, "ALL")
  mtbf <- c(mtbf, get_mtbf(data, NA, TRUE))
  df <- data.frame(nodeType, mtbf)
  df
}