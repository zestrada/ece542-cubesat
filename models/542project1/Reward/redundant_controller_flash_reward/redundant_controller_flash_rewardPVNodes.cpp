#include "redundant_controller_flash_rewardPVNodes.h"

redundant_controller_flash_rewardPV0Worker::redundant_controller_flash_rewardPV0Worker()
{
  NumModels = 1;
  TheModelPtr = new BaseModelClass**[NumModels];
  TheModelPtr[0] = (BaseModelClass**)(&ram_system);
}

redundant_controller_flash_rewardPV0Worker::~redundant_controller_flash_rewardPV0Worker() {
  delete [] TheModelPtr;
}

double redundant_controller_flash_rewardPV0Worker::Reward_Function(void) {

return ram_system->system_failed->Mark();
//return ((ram_system->flash_corrupted->Mark() > 0) 
//&& (ram_system->ram_corrupted->Mark() > 0));

return (0);



}

redundant_controller_flash_rewardPV0::redundant_controller_flash_rewardPV0(int timeindex) {
  TheModelPtr = (BaseModelClass**)(&Theredundant_controller_flash_modelRJ);
  double startpts[3]={30.0, 180.0, 365.0};
  double stoppts[3]={30.0, 180.0, 365.0};
  Initialize("reliability",(RewardType)0,3, startpts, stoppts, timeindex, 0,1, 1);
  AddVariableDependency("system_failed","ram_system");
}

redundant_controller_flash_rewardPV0::~redundant_controller_flash_rewardPV0() {
  for(int i = 0; i < NumberOfWorkers; i++) {
    delete[] WorkerList[i]->Name;
    delete WorkerList[i];
  }
}

void redundant_controller_flash_rewardPV0::CreateWorkerList(void) {
  for(int i = 0; i < NumberOfWorkers; i++)
    WorkerList[i] = new redundant_controller_flash_rewardPV0Worker;
}
