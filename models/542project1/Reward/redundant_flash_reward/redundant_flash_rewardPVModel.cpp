#include "redundant_flash_rewardPVModel.h"

redundant_flash_rewardPVModel::redundant_flash_rewardPVModel(bool expandTimeArrays) {
  TheModel=new redundant_flash_modelRJ();
  DefineName("redundant_flash_rewardPVModel");
  CreatePVList(1, expandTimeArrays);
  Initialize();
}



PerformanceVariableNode* redundant_flash_rewardPVModel::createPVNode(int pvindex, int timeindex) {
  switch(pvindex) {
  case 0:
    return new redundant_flash_rewardPV0(timeindex);
    break;
  }
  return NULL;
}
