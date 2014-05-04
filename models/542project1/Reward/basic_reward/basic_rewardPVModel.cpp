#include "basic_rewardPVModel.h"

basic_rewardPVModel::basic_rewardPVModel(bool expandTimeArrays) {
  TheModel=new basic_modelRJ();
  DefineName("basic_rewardPVModel");
  CreatePVList(1, expandTimeArrays);
  Initialize();
}



PerformanceVariableNode* basic_rewardPVModel::createPVNode(int pvindex, int timeindex) {
  switch(pvindex) {
  case 0:
    return new basic_rewardPV0(timeindex);
    break;
  }
  return NULL;
}
