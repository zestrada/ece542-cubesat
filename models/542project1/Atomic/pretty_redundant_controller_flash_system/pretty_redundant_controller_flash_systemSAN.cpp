

// This C++ file was created by SanEditor

#include "Atomic/pretty_redundant_controller_flash_system/pretty_redundant_controller_flash_systemSAN.h"

#include <stdlib.h>
#include <iostream>

#include <math.h>


/*****************************************************************
                         pretty_redundant_controller_flash_systemSAN Constructor             
******************************************************************/


pretty_redundant_controller_flash_systemSAN::pretty_redundant_controller_flash_systemSAN(){


  seuGroup.initialize(2, "seuGroup");
  seuGroup.appendGroup((BaseGroupClass*) &seu_case1);
  seuGroup.appendGroup((BaseGroupClass*) &seu_case2);

  Activity* InitialActionList[4]={
    &seu_case1, //0
    &seu_case2, //1
    &sefi, //2
    &power_cycle  // 3
  };

  BaseGroupClass* InitialGroupList[3]={
    (BaseGroupClass*) &(seuGroup), 
    (BaseGroupClass*) &(sefi), 
    (BaseGroupClass*) &(power_cycle)
  };

  devices_available = new Place("devices_available" ,num_devices);
  replicas_available = new Place("replicas_available" ,num_replicas);
  flash_corrupted = new Place("flash_corrupted" ,0);
  replicas_corrupted = new Place("replicas_corrupted" ,0);
  local_device_corrupted = new Place("local_device_corrupted" ,0);
  BaseStateVariableClass* InitialPlaces[5]={
    devices_available,  // 0
    replicas_available,  // 1
    flash_corrupted,  // 2
    replicas_corrupted,  // 3
    local_device_corrupted   // 4
  };
  BaseStateVariableClass* InitialROPlaces[0]={
  };
  initializeSANModelNow("pretty_redundant_controller_flash_system", 5, InitialPlaces, 
                        0, InitialROPlaces, 
                        4, InitialActionList, 3, InitialGroupList);


  assignPlacesToActivitiesInst();
  assignPlacesToActivitiesTimed();

  int AffectArcs[15][2]={ 
    {1,0}, {1,1}, {3,1}, {0,1}, {4,1}, {2,1}, {1,2}, {0,2}, {4,2}, 
    {2,2}, {1,3}, {3,3}, {4,3}, {0,3}, {2,3}
  };
  for(int n=0;n<15;n++) {
    AddAffectArc(InitialPlaces[AffectArcs[n][0]],
                 InitialActionList[AffectArcs[n][1]]);
  }
  int EnableArcs[4][2]={ 
    {1,0}, {1,1}, {1,2}, {1,3}
  };
  for(int n=0;n<4;n++) {
    AddEnableArc(InitialPlaces[EnableArcs[n][0]],
                 InitialActionList[EnableArcs[n][1]]);
  }

  for(int n=0;n<4;n++) {
    InitialActionList[n]->LinkVariables();
  }
  CustomInitialization();

}

void pretty_redundant_controller_flash_systemSAN::CustomInitialization() {

}
pretty_redundant_controller_flash_systemSAN::~pretty_redundant_controller_flash_systemSAN(){
  for (int i = 0; i < NumStateVariables-NumReadOnlyPlaces; i++)
    delete LocalStateVariables[i];
};

void pretty_redundant_controller_flash_systemSAN::assignPlacesToActivitiesInst(){
}
void pretty_redundant_controller_flash_systemSAN::assignPlacesToActivitiesTimed(){
  seu_case1.replicas_available = (Place*) LocalStateVariables[1];
  seu_case2.replicas_available = (Place*) LocalStateVariables[1];
  seu_case2.replicas_corrupted = (Place*) LocalStateVariables[3];
  seu_case2.devices_available = (Place*) LocalStateVariables[0];
  seu_case2.local_device_corrupted = (Place*) LocalStateVariables[4];
  seu_case2.flash_corrupted = (Place*) LocalStateVariables[2];
  sefi.replicas_available = (Place*) LocalStateVariables[1];
  sefi.devices_available = (Place*) LocalStateVariables[0];
  sefi.local_device_corrupted = (Place*) LocalStateVariables[4];
  sefi.flash_corrupted = (Place*) LocalStateVariables[2];
  power_cycle.replicas_available = (Place*) LocalStateVariables[1];
  power_cycle.replicas_corrupted = (Place*) LocalStateVariables[3];
  power_cycle.local_device_corrupted = (Place*) LocalStateVariables[4];
  power_cycle.devices_available = (Place*) LocalStateVariables[0];
  power_cycle.flash_corrupted = (Place*) LocalStateVariables[2];
}
/*****************************************************************/
/*                  Activity Method Definitions                  */
/*****************************************************************/

/*======================seuActivity_case1========================*/

pretty_redundant_controller_flash_systemSAN::seuActivity_case1::seuActivity_case1(){
  TheDistributionParameters = new double[1];
  ActivityInitialize("seu_case1",0,Exponential, RaceEnabled, 1,1, false);
}

pretty_redundant_controller_flash_systemSAN::seuActivity_case1::~seuActivity_case1(){
  delete[] TheDistributionParameters;
}

void pretty_redundant_controller_flash_systemSAN::seuActivity_case1::LinkVariables(){
  replicas_available->Register(&replicas_available_Mobius_Mark);
}

bool pretty_redundant_controller_flash_systemSAN::seuActivity_case1::Enabled(){
  OldEnabled=NewEnabled;
  NewEnabled=(((*(replicas_available_Mobius_Mark)) >=1));
  return NewEnabled;
}

double pretty_redundant_controller_flash_systemSAN::seuActivity_case1::Rate(){
  return 6.44e-7;
  return 1.0;  // default rate if none is specified
}

double pretty_redundant_controller_flash_systemSAN::seuActivity_case1::Weight(){ 
  return 1-(flash_size*replicas_available->Mark()/512);
}

bool pretty_redundant_controller_flash_systemSAN::seuActivity_case1::ReactivationPredicate(){ 
  return false;
}

bool pretty_redundant_controller_flash_systemSAN::seuActivity_case1::ReactivationFunction(){ 
  return false;
}

double pretty_redundant_controller_flash_systemSAN::seuActivity_case1::SampleDistribution(){
  return TheDistribution->Exponential(6.44e-7);
}

double* pretty_redundant_controller_flash_systemSAN::seuActivity_case1::ReturnDistributionParameters(){
  TheDistributionParameters[0] = Rate();
  return TheDistributionParameters;
}

int pretty_redundant_controller_flash_systemSAN::seuActivity_case1::Rank(){
  return 1;
}

BaseActionClass* pretty_redundant_controller_flash_systemSAN::seuActivity_case1::Fire(){
  (*(replicas_available_Mobius_Mark))--;
  replicas_available->Mark() += 1;
  return this;
}

/*======================seuActivity_case2========================*/

pretty_redundant_controller_flash_systemSAN::seuActivity_case2::seuActivity_case2(){
  TheDistributionParameters = new double[1];
  ActivityInitialize("seu_case2",0,Exponential, RaceEnabled, 5,1, false);
}

pretty_redundant_controller_flash_systemSAN::seuActivity_case2::~seuActivity_case2(){
  delete[] TheDistributionParameters;
}

void pretty_redundant_controller_flash_systemSAN::seuActivity_case2::LinkVariables(){
  replicas_available->Register(&replicas_available_Mobius_Mark);
  replicas_corrupted->Register(&replicas_corrupted_Mobius_Mark);
  devices_available->Register(&devices_available_Mobius_Mark);
  local_device_corrupted->Register(&local_device_corrupted_Mobius_Mark);
  flash_corrupted->Register(&flash_corrupted_Mobius_Mark);
}

bool pretty_redundant_controller_flash_systemSAN::seuActivity_case2::Enabled(){
  OldEnabled=NewEnabled;
  NewEnabled=(((*(replicas_available_Mobius_Mark)) >=1));
  return NewEnabled;
}

double pretty_redundant_controller_flash_systemSAN::seuActivity_case2::Rate(){
  return 6.44e-7;
  return 1.0;  // default rate if none is specified
}

double pretty_redundant_controller_flash_systemSAN::seuActivity_case2::Weight(){ 
  return flash_size*replicas_available->Mark()/512;
}

bool pretty_redundant_controller_flash_systemSAN::seuActivity_case2::ReactivationPredicate(){ 
  return false;
}

bool pretty_redundant_controller_flash_systemSAN::seuActivity_case2::ReactivationFunction(){ 
  return false;
}

double pretty_redundant_controller_flash_systemSAN::seuActivity_case2::SampleDistribution(){
  return TheDistribution->Exponential(6.44e-7);
}

double* pretty_redundant_controller_flash_systemSAN::seuActivity_case2::ReturnDistributionParameters(){
  TheDistributionParameters[0] = Rate();
  return TheDistributionParameters;
}

int pretty_redundant_controller_flash_systemSAN::seuActivity_case2::Rank(){
  return 1;
}

BaseActionClass* pretty_redundant_controller_flash_systemSAN::seuActivity_case2::Fire(){
  (*(replicas_available_Mobius_Mark))--;
  replicas_corrupted->Mark()++;
if(replicas_available->Mark() == 0) {
	devices_available->Mark() -= 1;
	local_device_corrupted->Mark() = 1;
	if(devices_available->Mark() == 0) {
		flash_corrupted->Mark() = 1;
	}
}
  return this;
}

/*======================sefiActivity========================*/

pretty_redundant_controller_flash_systemSAN::sefiActivity::sefiActivity(){
  TheDistributionParameters = new double[1];
  ActivityInitialize("sefi",1,Exponential, RaceEnabled, 4,1, false);
}

pretty_redundant_controller_flash_systemSAN::sefiActivity::~sefiActivity(){
  delete[] TheDistributionParameters;
}

void pretty_redundant_controller_flash_systemSAN::sefiActivity::LinkVariables(){
  replicas_available->Register(&replicas_available_Mobius_Mark);
  devices_available->Register(&devices_available_Mobius_Mark);
  local_device_corrupted->Register(&local_device_corrupted_Mobius_Mark);
  flash_corrupted->Register(&flash_corrupted_Mobius_Mark);
}

bool pretty_redundant_controller_flash_systemSAN::sefiActivity::Enabled(){
  OldEnabled=NewEnabled;
  NewEnabled=((replicas_available->Mark() > 0));
  return NewEnabled;
}

double pretty_redundant_controller_flash_systemSAN::sefiActivity::Rate(){
  return 2.74e-3;
  return 1.0;  // default rate if none is specified
}

double pretty_redundant_controller_flash_systemSAN::sefiActivity::Weight(){ 
  return 1;
}

bool pretty_redundant_controller_flash_systemSAN::sefiActivity::ReactivationPredicate(){ 
  return false;
}

bool pretty_redundant_controller_flash_systemSAN::sefiActivity::ReactivationFunction(){ 
  return false;
}

double pretty_redundant_controller_flash_systemSAN::sefiActivity::SampleDistribution(){
  return TheDistribution->Exponential(2.74e-3);
}

double* pretty_redundant_controller_flash_systemSAN::sefiActivity::ReturnDistributionParameters(){
  TheDistributionParameters[0] = Rate();
  return TheDistributionParameters;
}

int pretty_redundant_controller_flash_systemSAN::sefiActivity::Rank(){
  return 1;
}

BaseActionClass* pretty_redundant_controller_flash_systemSAN::sefiActivity::Fire(){
  ;
  replicas_available->Mark() = 0;
devices_available->Mark() -= 1;
local_device_corrupted->Mark() = 1;
if(devices_available->Mark() == 0) {
	flash_corrupted->Mark() = 1;
}
  return this;
}

/*======================power_cycleActivity========================*/

pretty_redundant_controller_flash_systemSAN::power_cycleActivity::power_cycleActivity(){
  TheDistributionParameters = new double[1];
  ActivityInitialize("power_cycle",2,Deterministic, RaceEnabled, 5,1, false);
}

pretty_redundant_controller_flash_systemSAN::power_cycleActivity::~power_cycleActivity(){
  delete[] TheDistributionParameters;
}

void pretty_redundant_controller_flash_systemSAN::power_cycleActivity::LinkVariables(){
  replicas_available->Register(&replicas_available_Mobius_Mark);
  replicas_corrupted->Register(&replicas_corrupted_Mobius_Mark);
  local_device_corrupted->Register(&local_device_corrupted_Mobius_Mark);
  devices_available->Register(&devices_available_Mobius_Mark);
  flash_corrupted->Register(&flash_corrupted_Mobius_Mark);
}

bool pretty_redundant_controller_flash_systemSAN::power_cycleActivity::Enabled(){
  OldEnabled=NewEnabled;
  NewEnabled=((replicas_available->Mark() < num_replicas));
  return NewEnabled;
}

double pretty_redundant_controller_flash_systemSAN::power_cycleActivity::DeterministicParamValue(){
  return power_cycle_rate;
  return 1.0;  // default rate if none is specified
}

double pretty_redundant_controller_flash_systemSAN::power_cycleActivity::Weight(){ 
  return 1;
}

bool pretty_redundant_controller_flash_systemSAN::power_cycleActivity::ReactivationPredicate(){ 
  return false;
}

bool pretty_redundant_controller_flash_systemSAN::power_cycleActivity::ReactivationFunction(){ 
  return false;
}

double pretty_redundant_controller_flash_systemSAN::power_cycleActivity::SampleDistribution(){
  return power_cycle_rate;
}

double* pretty_redundant_controller_flash_systemSAN::power_cycleActivity::ReturnDistributionParameters(){
  TheDistributionParameters[0] = DeterministicParamValue();
  return TheDistributionParameters;
}

int pretty_redundant_controller_flash_systemSAN::power_cycleActivity::Rank(){
  return 1;
}

BaseActionClass* pretty_redundant_controller_flash_systemSAN::power_cycleActivity::Fire(){
  ;
  replicas_available->Mark() = num_replicas - replicas_corrupted->Mark();
if(local_device_corrupted->Mark() == 1) {
	devices_available->Mark() += 1;
	local_device_corrupted->Mark() = 0;
	flash_corrupted->Mark() = 0;
}
  return this;
}

