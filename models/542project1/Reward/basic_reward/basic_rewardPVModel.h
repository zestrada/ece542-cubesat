#ifndef _BASIC_REWARD_PVMODEL_
#define _BASIC_REWARD_PVMODEL_
#include "basic_rewardPVNodes.h"
#include "Cpp/Performance_Variables/PVModel.hpp"
#include "Composed/basic_model/basic_modelRJ.h"
class basic_rewardPVModel:public PVModel {
 protected:
  PerformanceVariableNode *createPVNode(int pvindex, int timeindex);
 public:
  basic_rewardPVModel(bool expandtimepoints);
};

#endif
