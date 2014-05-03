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

return ((ram_system->flash_corrupted->Mark() > 0) 
&& (ram_system->ram_corrupted->Mark() > 0));

return (0);



}

basic_rewardPV0::basic_rewardPV0(int timeindex) {
  TheModelPtr = (BaseModelClass**)(&Thebasic_modelRJ);
  double startpts[1]={365.0};
  double stoppts[1]={365.0};
  Initialize("reliability",(RewardType)0,1, startpts, stoppts, timeindex, 0,3, 2);
  AddVariableDependency("flash_corrupted","ram_system");
  AddVariableDependency("ram_corrupted","ram_system");
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
