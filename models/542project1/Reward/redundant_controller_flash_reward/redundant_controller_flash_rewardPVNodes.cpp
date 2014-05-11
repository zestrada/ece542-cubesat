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

return (ram_system->system_failed->Mark() == 0);
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
redundant_controller_flash_rewardPV1Worker::redundant_controller_flash_rewardPV1Worker()
{
  NumModels = 1;
  TheModelPtr = new BaseModelClass**[NumModels];
  TheModelPtr[0] = (BaseModelClass**)(&redundant_controller_flash_system);
}

redundant_controller_flash_rewardPV1Worker::~redundant_controller_flash_rewardPV1Worker() {
  delete [] TheModelPtr;
}

double redundant_controller_flash_rewardPV1Worker::Reward_Function(void) {

return redundant_controller_flash_system->seu_events->Mark();

return (0);



}

redundant_controller_flash_rewardPV1::redundant_controller_flash_rewardPV1(int timeindex) {
  TheModelPtr = (BaseModelClass**)(&Theredundant_controller_flash_modelRJ);
  double startpts[1]={365.0};
  double stoppts[1]={365.0};
  Initialize("seu_events",(RewardType)0,1, startpts, stoppts, timeindex, 0,1, 1);
  AddVariableDependency("seu_events","redundant_controller_flash_system");
}

redundant_controller_flash_rewardPV1::~redundant_controller_flash_rewardPV1() {
  for(int i = 0; i < NumberOfWorkers; i++) {
    delete[] WorkerList[i]->Name;
    delete WorkerList[i];
  }
}

void redundant_controller_flash_rewardPV1::CreateWorkerList(void) {
  for(int i = 0; i < NumberOfWorkers; i++)
    WorkerList[i] = new redundant_controller_flash_rewardPV1Worker;
}
redundant_controller_flash_rewardPV2Worker::redundant_controller_flash_rewardPV2Worker()
{
  NumModels = 1;
  TheModelPtr = new BaseModelClass**[NumModels];
  TheModelPtr[0] = (BaseModelClass**)(&redundant_controller_flash_system);
}

redundant_controller_flash_rewardPV2Worker::~redundant_controller_flash_rewardPV2Worker() {
  delete [] TheModelPtr;
}

double redundant_controller_flash_rewardPV2Worker::Reward_Function(void) {

return redundant_controller_flash_system->sefi_events->Mark();

return (0);



}

redundant_controller_flash_rewardPV2::redundant_controller_flash_rewardPV2(int timeindex) {
  TheModelPtr = (BaseModelClass**)(&Theredundant_controller_flash_modelRJ);
  double startpts[1]={365.0};
  double stoppts[1]={365.0};
  Initialize("sefi_events",(RewardType)0,1, startpts, stoppts, timeindex, 0,1, 1);
  AddVariableDependency("sefi_events","redundant_controller_flash_system");
}

redundant_controller_flash_rewardPV2::~redundant_controller_flash_rewardPV2() {
  for(int i = 0; i < NumberOfWorkers; i++) {
    delete[] WorkerList[i]->Name;
    delete WorkerList[i];
  }
}

void redundant_controller_flash_rewardPV2::CreateWorkerList(void) {
  for(int i = 0; i < NumberOfWorkers; i++)
    WorkerList[i] = new redundant_controller_flash_rewardPV2Worker;
}
