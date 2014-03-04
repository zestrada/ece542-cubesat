# Task 0, Item 2.
get_summary <- function(data){
  num_nodes <- length(levels(data$CompleteNode))
  # Read from the data using head and tail: 10-6-12 through 10-13-12.
  num_days <- 8
  num_entries <- nrow(data)
  # Uncorrectable errors set either the ucc or ue bits.
  num_uncorrectable_errors <- nrow(data[data$ucc == 1 | data$ue == 1,])
  num_machine_check_exception_types <- length(levels(data$Type))

  df <- data.frame(num_nodes, num_days, num_entries, num_uncorrectable_errors, num_machine_check_exception_types)
  df
}