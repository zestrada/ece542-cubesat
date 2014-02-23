# Gets the mean time between failures for a given type,
# or all of the data if the all parameter is TRUE.
get_mtbf <- function(data, type, all=FALSE) {
  if(all==FALSE) {
    data <- data[data$Type == type,]    
  }
  # I define mtbf as <total time between all failures> / <number of failures>.
  # What should we do if there's one failure?  Returns 0 now.
  total_time <- data$Timestamp[length(data$Timestamp)] - data$Timestamp[1]
  num_failures <- nrow(data)
  total_time / num_failures
}

get_all_mtbfs <- function(data) {
  for (level in levels(data$Type)) {
    print(level)
    print(get_mtbf(data, level))
  }
  print("All")
  print(get_mtbf(data, NA, TRUE))
}