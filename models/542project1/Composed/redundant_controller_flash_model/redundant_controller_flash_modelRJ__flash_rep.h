#ifndef redundant_controller_flash_modelRJ__flash_rep_H_
#define redundant_controller_flash_modelRJ__flash_rep_H_
#include <math.h>
#include "Cpp/Composer/Rep.h"
#include "Cpp/Composer/AllStateVariableTypes.h"

//Submodel header files
#include "Atomic/redundant_controller_flash_system/redundant_controller_flash_systemSAN.h"

//State variable headers
#include "Cpp/BaseClasses/SAN/Place.h"
extern float flash_size;
extern float ram_size;
extern float random_failure_rate;
extern float power_cycle_rate;
extern short num_replicas;
extern short num_devices;

class redundant_controller_flash_modelRJ__flash_rep: public Rep {
 public:
  redundant_controller_flash_systemSAN ** InstanceArray;

  redundant_controller_flash_modelRJ__flash_rep();
  ~redundant_controller_flash_modelRJ__flash_rep();

  // Declare new variables
  Place * devices_available;
  Place * flash_corrupted;
};

#endif
