#include "basic_rewardPVNodes.h"

basic_rewardPV0Worker::basic_rewardPV0Worker()
{
  NumModels = 2;
  TheModelPtr = new BaseModelClass**[NumModels];
  TheModelPtr[0] = (BaseModelClass**)(&ram_system);
  TheModelPtr[1] = (BaseModelClass**)(&flash_system);
}

basic_rewardPV0Worker::~basic_rewardPV0Worker() {
  delete [] TheModelPtr;
}

double basic_rewardPV0Worker::Reward_Function(void) {

return ram_system->system_failed->Mark();
//return ((ram_system->flash_corrupted->Mark() > 0) 
//&& (ram_system->ram_corrupted->Mark() > 0));

return (0);



}

basic_rewardPV0::basic_rewardPV0(int timeindex) {
  TheModelPtr = (BaseModelClass**)(&Thebasic_modelRJ);
  double startpts[3]={30.0, 180.0, 365.0};
  double stoppts[3]={30.0, 180.0, 365.0};
  Initialize("reliability",(RewardType)0,3, startpts, stoppts, timeindex, 0,2, 1);
  AddVariableDependency("system_failed","ram_system");
  AddModelDependency("flash_system");
}

basic_rewardPV0::~basic_rewardPV0() {
  for(int i = 0; i < NumberOfWorkers; i++) {
    delete[] WorkerList[i]->Name;
    delete WorkerList[i];
  }
}

void basic_rewardPV0::CreateWorkerList(void) {
  for(int i = 0; i < NumberOfWorkers; i++)
    WorkerList[i] = new basic_rewardPV0Worker;
}
