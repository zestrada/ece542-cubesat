#ifndef _REDUNDANT_FLASH_REWARD_PVS_
#define _REDUNDANT_FLASH_REWARD_PVS_
#include <math.h>
#include "Cpp/Performance_Variables/PerformanceVariableNode.hpp"
#include "Composed/redundant_flash_model/redundant_flash_modelRJ.h"
#include "Cpp/Performance_Variables/InstantOfTime.hpp"


class redundant_flash_rewardPV0Worker:public InstantOfTime
{
 public:
  ram_systemSAN *ram_system;
  
  redundant_flash_rewardPV0Worker();
  ~redundant_flash_rewardPV0Worker();
  double Reward_Function();
};

class redundant_flash_rewardPV0:public PerformanceVariableNode
{
 public:
  redundant_flash_modelRJ *Theredundant_flash_modelRJ;

  redundant_flash_rewardPV0Worker *redundant_flash_rewardPV0WorkerList;

  redundant_flash_rewardPV0(int timeindex=0);
  ~redundant_flash_rewardPV0();
  void CreateWorkerList(void);
};

#endif
