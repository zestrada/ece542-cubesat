#ifndef _REDUNDANT_FLASH_REWARD_PVMODEL_
#define _REDUNDANT_FLASH_REWARD_PVMODEL_
#include "redundant_flash_rewardPVNodes.h"
#include "Cpp/Performance_Variables/PVModel.hpp"
#include "Composed/redundant_flash_model/redundant_flash_modelRJ.h"
class redundant_flash_rewardPVModel:public PVModel {
 protected:
  PerformanceVariableNode *createPVNode(int pvindex, int timeindex);
 public:
  redundant_flash_rewardPVModel(bool expandtimepoints);
};

#endif
