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

get_mce_mtbf <- function(data) {
  total_time <- data$Timestamp[length(data$Timestamp)] - data$Timestamp[1]
  num_failures <- nrow(data)
  total_time / num_failures  
}

get_mce_mtbfs <- function(data) {
  bank <- vector()
  nodeType <- vector()
  type <- vector()
  mtbf <- vector()
  banks <- unique(data$Bank)
  for (b in banks) {
    nodeTypes <- levels(data$nodeType)
    for (n in nodeTypes) {
      nodeTypeData <- data[data$nodeType %in% n, ]
      types <- levels(nodeTypeData$Type)
      for (t in types) {
        typeData <- nodeTypeData[nodeTypeData$Type %in% t, ]
        if (nrow(typeData) != 0) {
          bank <- c(bank, b)
          nodeType <- c(nodeType, n)
          type <- c(type, t)
          mtbf <- c(mtbf, get_mce_mtbf(typeData)) 
        }
      }
    }
  }
  df = data.frame(bank, nodeType, type, mtbf)
  df
}

get_mtbf_per_day <- function(data) {
  bank <- vector()
  day <- vector()
  mtbf <- vector()
  banks <- unique(data$Bank)
  for (b in banks) {
    # 1349499600 is the timestamp of the start of October 6 (5am GMT = 12am CDT).
    # 86400 seconds/day.
    # Ends at October 13 (7 days later)
    day_num <- c(0, 1, 2, 3, 4, 5, 6, 7)
    for (d in day_num) {
      lower <- 1349499600 + 86400 * d
      upper <- 1349499600 + 86400 * (d + 1)
      day_data <- data[data$Timestamp >= lower & data$Timestamp <= upper &
                        data$Bank == b,]
      bank <- c(bank, b)
      day <- c(day, d)
      mtbf <- c(mtbf, 86400/nrow(day_data))
    }
  }
  df = data.frame(bank, day, mtbf)
  df
}

plot_tbf <- function(data, bank, ntype, all_types = FALSE, ...) {
  data <- data[data$Bank == bank, ]
  if (all_types == FALSE) {
    data <- data[data$nodeType == ntype, ]
  }
  tbf <- diff(data$Timestamp)
  print (data$Timestamp)
  hist(tbf, ...)
}

plot_haz <- function(data, bank, ntype, all_types = FALSE) {
  data <- data[data$Bank == bank, ]
  if (all_types == FALSE) {
    data <- data[data$nodeType == ntype, ]
  }
  diffs <- diff(data$Timestamp)
  plot(muhaz(data$Timestamp))
}