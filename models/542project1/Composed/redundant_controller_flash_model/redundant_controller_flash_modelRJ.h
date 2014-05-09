#ifndef redundant_controller_flash_modelRJ_H_
#define redundant_controller_flash_modelRJ_H_
#include <math.h>
#include "Cpp/Composer/Join.h"
#include "Cpp/Composer/AllStateVariableTypes.h"
#include "Atomic/ram_system/ram_systemSAN.h"
#include "Composed/redundant_controller_flash_model/redundant_controller_flash_modelRJ__flash_rep.h"

//State variable headers
#include "Cpp/BaseClasses/SAN/Place.h"
extern float flash_size;
extern float ram_size;
extern float random_failure_rate;
extern float power_cycle_rate;
extern short num_replicas;
extern short num_devices;

class redundant_controller_flash_modelRJ: public Join {
 public:
  ram_systemSAN * ram_system;
  redundant_controller_flash_modelRJ__flash_rep * flash_rep;
  Place * flash_corrupted;

  redundant_controller_flash_modelRJ();
  ~redundant_controller_flash_modelRJ();
};

#endif
