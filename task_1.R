# Task 1, Item 1, Part a.
# Gets the number and percentage of errors for a particular fault type
# (or vector of fault types) given a node type (or vector of node types).
get_mce_percentage <- function(data, ntype, type) {
  # Count the total number of errors in the data.
  data <- data[data$nodeType %in% ntype,]
  total_errors <- nrow(data)
  
  if(total_errors == 0) {
    return(list(0, 0))
  }
  # Calculate the number of errors that are our desired type.
  data <- data[data$Type %in% type,]
  ne <- nrow(data)
  
  pe <- ne / total_errors
  
  return(list(ne, pe))
}

# Get all of the relevant error percentages. 
get_mce_percentages <- function(data) {
  nodeType <- vector()
  type <- vector()
  nerr <- vector()
  perr <- vector()
  
  # Node type definitions.
  L1_errors <- c("L1 cache Fill ECC error", "L1 tag load", "L1 TLB IC load")
  L2_errors <- c("L2 cache Fill ECC error", "L2 cache Fill ECC Error", "L2 ECC Error", "L2 IC cache parity error", "L2 TLB")
  mem_errors <- c("DRAM Parity Error", "ECC Error")
  other_errors <- c("NB Array Error", "Table Walk Data Error", "Data copy back Evict", "Link Retry")
  types <- list(L1_errors, L2_errors, mem_errors, other_errors)
  
  # Perform calculations for individual node types.
  for (nt in levels(data$nodeType)) {
    for (t in types) {
      result <- get_mce_percentage(data, nt, t)
      nodeType <- c(nodeType, nt)
      type <- c(type, get_type_name(t))
      nerr <- c(nerr, result[[1]])
      perr <- c(perr, result[[2]])
    }
  }
  # Perform calculations for all node types.
  for (t in types) {
    result <- get_mce_percentage(data, levels(data$nodeType), t)
    nodeType <- c(nodeType, "all")
    type <- c(type, get_type_name(t))
    nerr <- c(nerr, result[[1]])
    perr <- c(perr, result[[2]])
  }
  df <- data.frame(nodeType, type, nerr, perr)
  df
}

# Given a vector of types, returns a character vector summarizing them.
# Used in Task 1, Item 1.
get_type_name <- function(type) {
  L1_errors <- c("L1 cache Fill ECC error", "L1 tag load", "L1 TLB IC load")
  L2_errors <- c("L2 cache Fill ECC error", "L2 cache Fill ECC Error", "L2 ECC Error", "L2 IC cache parity error", "L2 TLB")
  mem_errors <- c("DRAM Parity Error", "ECC Error")
  other_errors <- c("NB Array Error", "Table Walk Data Error", "Data copy back Evict", "Link Retry")
  
  # Check type length first (short-circuiting out any comparisons 
  #if they don't match).  Then check for a match.
  if(length(type) == length(L1_errors) && all(type == L1_errors)) {
    return("L1")
  }
  else if (length(type) == length(L2_errors) && all(type == L2_errors)) {
    return("L2")
  }
  else if (length(type) == length(mem_errors) && all(type == mem_errors)) {
    return("mem")
  }
  else if (length(type) == length(other_errors) && all(type == other_errors)) {
    return("other")
  }
  else {
    return(NA)
  }
}

# Task 1, Item 1, Part b.
# Given a bank number (or vector thereof), node type (or vector thereof),
# and type (or vector thereof), calculates the MTBF.
get_mce_mtbf <- function(data, bank, ntype, type) {
  data <- data[data$Bank %in% bank & data$nodeType %in% ntype & data$Type %in% type,]

  total_time <- 8 * 24
  num_failures <- nrow(data)
  
  if(num_failures == 0) {
    return(Inf)
  }
  
  total_time / num_failures  
}

# Get all MTBFs from a given data set.
get_mce_mtbfs <- function(data) {
  bank <- vector()
  nodeType <- vector()
  type <- vector()
  mtbf <- vector()
  
  # Node type definitions.
  L1_errors <- c("L1 cache Fill ECC error", "L1 tag load", "L1 TLB IC load")
  L2_errors <- c("L2 cache Fill ECC error", "L2 cache Fill ECC Error", "L2 ECC Error", "L2 IC cache parity error", "L2 TLB")
  mem_errors <- c("DRAM Parity Error", "ECC Error")
  other_errors <- c("NB Array Error", "Table Walk Data Error", "Data copy back Evict", "Link Retry")
  types <- list(L1_errors, L2_errors, mem_errors, other_errors)
  
  banks <- unique(data$Bank)
  nodeTypes <- levels(data$nodeType)
  
  for (b in banks) {
    # Compute the result for individual node types.
    for (n in nodeTypes) {
      for (t in types) {
        bank <- c(bank, b)
        nodeType <- c(nodeType, n)
        type <- c(type, get_type_name(t))
        mtbf <- c(mtbf, get_mce_mtbf(data, b, n, t)) 
      }
    }
    # Compute the result for all node types.
    for (t in types) {
      bank <- c(bank, b)
      nodeType <- c(nodeType, "all")
      type <- c(type, get_type_name(t))
      mtbf <- c(mtbf, get_mce_mtbf(data, b, levels(data$nodeType), t)) 
    }
  }
  df = data.frame(bank, nodeType, type, mtbf)
  df
}

# Task 1, Item 2, Part a.
# Computes the MTBF for each day, for each bank.
get_mtbf_per_day <- function(data) {
  banks <- unique(data$Bank)
  for (b in banks) {
    # 1349499600 is the timestamp of the start of October 6 (5am GMT = 12am CDT).
    # 86400 seconds/day.
    # 24 hours/day.
    # Ends at October 13 (7 days later)
    bank <- vector()
    day <- vector()
    mtbf <- vector()
    day_num <- c(0, 1, 2, 3, 4, 5, 6, 7)
    for (d in day_num) {
      lower <- 1349499600 + 86400 * d
      upper <- 1349499600 + 86400 * (d + 1)
      day_data <- data[data$Timestamp >= lower & data$Timestamp <= upper &
                        data$Bank == b,]
      bank <- c(bank, b)
      day <- c(day, d)
      mtbf <- c(mtbf, 24/nrow(day_data))
    }
    title_string <- paste('MTBF by Day for Bank', as.character(b))
    print(title_string)
    plot(day, mtbf, log='y', xlab = 'Days since October 6, 2012', ylab = 'MTBF (hours)', main = title_string)
  }
  #df = data.frame(bank, day, mtbf)
  #df
}

# Task 1, Part 2, Item b.
# Plots the time between failures for a given bank and node type.
# Does not filter by type is all_types is true.
plot_tbf <- function(data, bank, ntype, all_types = FALSE, ...) {
  data <- data[data$Bank == bank, ]
  if (all_types == FALSE) {
    data <- data[data$nodeType == ntype, ]
  }
  if (length(data$Timestamp) > 2) {
    tbf <- diff(data$Timestamp)
    return(hist(tbf, ...))
  }
  else
  {
    return(NA)
  }
}

# Plots all relevant tbfs.
plot_tbfs <- function(data) {
  banks <- unique(data$Bank)
  nodeTypes <- levels(data$nodeType)
  for (b in banks) {
    for (n in nodeTypes) {
      title_string <- paste("TBF for bank", as.character(b), "for", n, "nodes")
      plot_tbf(data, b, n, FALSE, xlab = 'TBF (s)', ylab = 'Frequency', main = title_string, breaks = 20)
    }
    title_string <- paste("TBF for bank", as.character(b), "for", "ALL", "nodes")
    plot_tbf(data, b, NA, TRUE, xlab = 'TBF (s)', ylab = 'Frequency', main = title_string, breaks = 20)
  }
}

# Task 1, Part 2, Item c.
# Plots the hazard rate for a given bank and node type.
# Does not filter by type is all_types is true.
plot_haz <- function(data, bank, ntype, all_types = FALSE) {
  data <- data[data$Bank == bank, ]
  if (all_types == FALSE) {
    data <- data[data$nodeType == ntype, ]
  }
  diffs <- diff(data$Timestamp)
  plot(muhaz(diffs))
}