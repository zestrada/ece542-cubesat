get_mce_percentage <- function(data, ntype, all=FALSE) {
  nerr <- vector()
  perr <- vector()
  if (all == FALSE) {
    data <- data[data$nodeType == ntype,]
  }
  total_errors <- nrow(data)
  type <- levels(data$Type)
  for (t in type)
  {
    type_errors <- nrow(data[data$Type == t,])
    type_percent <- type_errors / total_errors
    nerr <- c(nerr, type_errors)
    perr <- c(perr, type_percent)
  }
  type <- c(type, "All")
  nerr <- c(nerr, total_errors)
  perr <- c(perr, 1)
  df = data.frame(type, nerr, perr)
  df
}

get_mce_percentages <- function(data) {
  for (level in levels(data$nodeType)) {
    print(level)
    print(get_mce_percentage(data, level))
  }
  print("All")
  print(get_mce_percentage(data, NA, TRUE))
}