#ifndef _REDUNDANT_CONTROLLER_FLASH_REWARD_PVMODEL_
#define _REDUNDANT_CONTROLLER_FLASH_REWARD_PVMODEL_
#include "redundant_controller_flash_rewardPVNodes.h"
#include "Cpp/Performance_Variables/PVModel.hpp"
#include "Composed/redundant_controller_flash_model/redundant_controller_flash_modelRJ__flash_rep.h"
#include "Composed/redundant_controller_flash_model/redundant_controller_flash_modelRJ.h"
class redundant_controller_flash_rewardPVModel:public PVModel {
 protected:
  PerformanceVariableNode *createPVNode(int pvindex, int timeindex);
 public:
  redundant_controller_flash_rewardPVModel(bool expandtimepoints);
};

#endif
