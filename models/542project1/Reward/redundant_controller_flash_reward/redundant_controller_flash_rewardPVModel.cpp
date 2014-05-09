#include "redundant_controller_flash_rewardPVModel.h"

redundant_controller_flash_rewardPVModel::redundant_controller_flash_rewardPVModel(bool expandTimeArrays) {
  TheModel=new redundant_controller_flash_modelRJ();
  DefineName("redundant_controller_flash_rewardPVModel");
  CreatePVList(1, expandTimeArrays);
  Initialize();
}



PerformanceVariableNode* redundant_controller_flash_rewardPVModel::createPVNode(int pvindex, int timeindex) {
  switch(pvindex) {
  case 0:
    return new redundant_controller_flash_rewardPV0(timeindex);
    break;
  }
  return NULL;
}
