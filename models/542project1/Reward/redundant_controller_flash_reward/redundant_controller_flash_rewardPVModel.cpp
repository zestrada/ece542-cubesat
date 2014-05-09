#include "redundant_controller_flash_rewardPVModel.h"

redundant_controller_flash_rewardPVModel::redundant_controller_flash_rewardPVModel(bool expandTimeArrays) {
  TheModel=new redundant_controller_flash_modelRJ();
  DefineName("redundant_controller_flash_rewardPVModel");
  CreatePVList(3, expandTimeArrays);
  Initialize();
}



PerformanceVariableNode* redundant_controller_flash_rewardPVModel::createPVNode(int pvindex, int timeindex) {
  switch(pvindex) {
  case 0:
    return new redundant_controller_flash_rewardPV0(timeindex);
    break;
  case 1:
    return new redundant_controller_flash_rewardPV1(timeindex);
    break;
  case 2:
    return new redundant_controller_flash_rewardPV2(timeindex);
    break;
  }
  return NULL;
}
