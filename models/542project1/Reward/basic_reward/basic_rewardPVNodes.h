#ifndef _BASIC_REWARD_PVS_
#define _BASIC_REWARD_PVS_
#include <math.h>
#include "Cpp/Performance_Variables/PerformanceVariableNode.hpp"
#include "Composed/basic_model/basic_modelRJ.h"
#include "Cpp/Performance_Variables/InstantOfTime.hpp"


class basic_rewardPV0Worker:public InstantOfTime
{
 public:
  ram_systemSAN *ram_system;
  flash_systemSAN *flash_system;
  
  basic_rewardPV0Worker();
  ~basic_rewardPV0Worker();
  double Reward_Function();
};

class basic_rewardPV0:public PerformanceVariableNode
{
 public:
  basic_modelRJ *Thebasic_modelRJ;

  basic_rewardPV0Worker *basic_rewardPV0WorkerList;

  basic_rewardPV0(int timeindex=0);
  ~basic_rewardPV0();
  void CreateWorkerList(void);
};

#endif
