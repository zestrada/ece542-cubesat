# Function used to load the data into memory in R.
# Could be viewed as part of Task 0, Item 2.
load_data <- function() {
  data1 <- read.table('data/machineCheckData_week_40.txt', header=TRUE, sep='\t')
  data2 <- read.table('data/machineCheckData_week_41.txt', header=TRUE, sep='\t')
  data <- rbind(data1, data2)
  data
}
