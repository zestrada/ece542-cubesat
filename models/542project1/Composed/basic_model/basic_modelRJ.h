#ifndef basic_modelRJ_H_
#define basic_modelRJ_H_
#include <math.h>
#include "Cpp/Composer/Join.h"
#include "Cpp/Composer/AllStateVariableTypes.h"
#include "Atomic/flash_system/flash_systemSAN.h"
#include "Atomic/ram_system/ram_systemSAN.h"

//State variable headers
#include "Cpp/BaseClasses/SAN/Place.h"
extern float flash_size;
extern float ram_size;
extern float random_failure_rate;
extern float power_cycle_rate;

class basic_modelRJ: public Join {
 public:
  flash_systemSAN * flash_system;
  ram_systemSAN * ram_system;
  Place * flash_corrupted;

  basic_modelRJ();
  ~basic_modelRJ();
};

#endif
