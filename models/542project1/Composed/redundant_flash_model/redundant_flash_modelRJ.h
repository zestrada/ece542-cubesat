#ifndef redundant_flash_modelRJ_H_
#define redundant_flash_modelRJ_H_
#include <math.h>
#include "Cpp/Composer/Join.h"
#include "Cpp/Composer/AllStateVariableTypes.h"
#include "Atomic/ram_system/ram_systemSAN.h"
#include "Atomic/redundant_flash_system/redundant_flash_systemSAN.h"

//State variable headers
#include "Cpp/BaseClasses/SAN/Place.h"
extern float flash_size;
extern float ram_size;
extern float random_failure_rate;
extern float power_cycle_rate;
extern short num_replicas;

class redundant_flash_modelRJ: public Join {
 public:
  ram_systemSAN * ram_system;
  redundant_flash_systemSAN * redundant_flash_system;
  Place * flash_corrupted;

  redundant_flash_modelRJ();
  ~redundant_flash_modelRJ();
};

#endif
