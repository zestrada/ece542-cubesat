

// This C++ file was created by SanEditor

#include "Atomic/flash_system/flash_systemSAN.h"

#include <stdlib.h>
#include <iostream>

#include <math.h>


/*****************************************************************
                         flash_systemSAN Constructor             
******************************************************************/


flash_systemSAN::flash_systemSAN(){


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

  flash_corrupted = new Place("flash_corrupted" ,0);
  flash_working = new Place("flash_working" ,1);
  BaseStateVariableClass* InitialPlaces[2]={
    flash_corrupted,  // 0
    flash_working   // 1
  };
  BaseStateVariableClass* InitialROPlaces[0]={
  };
  initializeSANModelNow("flash_system", 2, InitialPlaces, 
                        0, InitialROPlaces, 
                        4, InitialActionList, 3, InitialGroupList);


  assignPlacesToActivitiesInst();
  assignPlacesToActivitiesTimed();

  int AffectArcs[7][2]={ 
    {1,0}, {1,1}, {0,1}, {1,2}, {0,2}, {0,3}, {1,3}
  };
  for(int n=0;n<7;n++) {
    AddAffectArc(InitialPlaces[AffectArcs[n][0]],
                 InitialActionList[AffectArcs[n][1]]);
  }
  int EnableArcs[4][2]={ 
    {1,0}, {1,1}, {1,2}, {0,3}
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

void flash_systemSAN::CustomInitialization() {

}
flash_systemSAN::~flash_systemSAN(){
  for (int i = 0; i < NumStateVariables-NumReadOnlyPlaces; i++)
    delete LocalStateVariables[i];
};

void flash_systemSAN::assignPlacesToActivitiesInst(){
}
void flash_systemSAN::assignPlacesToActivitiesTimed(){
  seu_case1.flash_working = (Place*) LocalStateVariables[1];
  seu_case2.flash_working = (Place*) LocalStateVariables[1];
  seu_case2.flash_corrupted = (Place*) LocalStateVariables[0];
  sefi.flash_working = (Place*) LocalStateVariables[1];
  sefi.flash_corrupted = (Place*) LocalStateVariables[0];
  power_cycle.flash_corrupted = (Place*) LocalStateVariables[0];
  power_cycle.flash_working = (Place*) LocalStateVariables[1];
}
/*****************************************************************/
/*                  Activity Method Definitions                  */
/*****************************************************************/

/*======================seuActivity_case1========================*/

flash_systemSAN::seuActivity_case1::seuActivity_case1(){
  TheDistributionParameters = new double[1];
  ActivityInitialize("seu_case1",0,Exponential, RaceEnabled, 1,1, false);
}

flash_systemSAN::seuActivity_case1::~seuActivity_case1(){
  delete[] TheDistributionParameters;
}

void flash_systemSAN::seuActivity_case1::LinkVariables(){
  flash_working->Register(&flash_working_Mobius_Mark);
}

bool flash_systemSAN::seuActivity_case1::Enabled(){
  OldEnabled=NewEnabled;
  NewEnabled=((flash_working->Mark() > 0));
  return NewEnabled;
}

double flash_systemSAN::seuActivity_case1::Rate(){
  return 1.5e-16;
  return 1.0;  // default rate if none is specified
}

double flash_systemSAN::seuActivity_case1::Weight(){ 
  return 1-(flash_size/512);
}

bool flash_systemSAN::seuActivity_case1::ReactivationPredicate(){ 
  return false;
}

bool flash_systemSAN::seuActivity_case1::ReactivationFunction(){ 
  return false;
}

double flash_systemSAN::seuActivity_case1::SampleDistribution(){
  return TheDistribution->Exponential(1.5e-16);
}

double* flash_systemSAN::seuActivity_case1::ReturnDistributionParameters(){
  TheDistributionParameters[0] = Rate();
  return TheDistributionParameters;
}

int flash_systemSAN::seuActivity_case1::Rank(){
  return 1;
}

BaseActionClass* flash_systemSAN::seuActivity_case1::Fire(){
  flash_working->Mark() = 0;
  flash_working->Mark() = 1;
  return this;
}

/*======================seuActivity_case2========================*/

flash_systemSAN::seuActivity_case2::seuActivity_case2(){
  TheDistributionParameters = new double[1];
  ActivityInitialize("seu_case2",0,Exponential, RaceEnabled, 2,1, false);
}

flash_systemSAN::seuActivity_case2::~seuActivity_case2(){
  delete[] TheDistributionParameters;
}

void flash_systemSAN::seuActivity_case2::LinkVariables(){
  flash_working->Register(&flash_working_Mobius_Mark);
  flash_corrupted->Register(&flash_corrupted_Mobius_Mark);
}

bool flash_systemSAN::seuActivity_case2::Enabled(){
  OldEnabled=NewEnabled;
  NewEnabled=((flash_working->Mark() > 0));
  return NewEnabled;
}

double flash_systemSAN::seuActivity_case2::Rate(){
  return 1.5e-16;
  return 1.0;  // default rate if none is specified
}

double flash_systemSAN::seuActivity_case2::Weight(){ 
  return flash_size/512;
}

bool flash_systemSAN::seuActivity_case2::ReactivationPredicate(){ 
  return false;
}

bool flash_systemSAN::seuActivity_case2::ReactivationFunction(){ 
  return false;
}

double flash_systemSAN::seuActivity_case2::SampleDistribution(){
  return TheDistribution->Exponential(1.5e-16);
}

double* flash_systemSAN::seuActivity_case2::ReturnDistributionParameters(){
  TheDistributionParameters[0] = Rate();
  return TheDistributionParameters;
}

int flash_systemSAN::seuActivity_case2::Rank(){
  return 1;
}

BaseActionClass* flash_systemSAN::seuActivity_case2::Fire(){
  flash_working->Mark() = 0;
  flash_working->Mark() = 0;
flash_corrupted->Mark() = 1;
  return this;
}

/*======================sefiActivity========================*/

flash_systemSAN::sefiActivity::sefiActivity(){
  TheDistributionParameters = new double[1];
  ActivityInitialize("sefi",1,Exponential, RaceEnabled, 2,1, false);
}

flash_systemSAN::sefiActivity::~sefiActivity(){
  delete[] TheDistributionParameters;
}

void flash_systemSAN::sefiActivity::LinkVariables(){
  flash_working->Register(&flash_working_Mobius_Mark);
  flash_corrupted->Register(&flash_corrupted_Mobius_Mark);
}

bool flash_systemSAN::sefiActivity::Enabled(){
  OldEnabled=NewEnabled;
  NewEnabled=((flash_working->Mark() > 0));
  return NewEnabled;
}

double flash_systemSAN::sefiActivity::Rate(){
  return 2.74e-3;
  return 1.0;  // default rate if none is specified
}

double flash_systemSAN::sefiActivity::Weight(){ 
  return 1;
}

bool flash_systemSAN::sefiActivity::ReactivationPredicate(){ 
  return false;
}

bool flash_systemSAN::sefiActivity::ReactivationFunction(){ 
  return false;
}

double flash_systemSAN::sefiActivity::SampleDistribution(){
  return TheDistribution->Exponential(2.74e-3);
}

double* flash_systemSAN::sefiActivity::ReturnDistributionParameters(){
  TheDistributionParameters[0] = Rate();
  return TheDistributionParameters;
}

int flash_systemSAN::sefiActivity::Rank(){
  return 1;
}

BaseActionClass* flash_systemSAN::sefiActivity::Fire(){
  flash_working->Mark() = 0;
  flash_working->Mark() = 0;
flash_corrupted->Mark() = 1;
  return this;
}

/*======================power_cycleActivity========================*/

flash_systemSAN::power_cycleActivity::power_cycleActivity(){
  TheDistributionParameters = new double[1];
  ActivityInitialize("power_cycle",2,Deterministic, RaceEnabled, 2,1, false);
}

flash_systemSAN::power_cycleActivity::~power_cycleActivity(){
  delete[] TheDistributionParameters;
}

void flash_systemSAN::power_cycleActivity::LinkVariables(){
  flash_corrupted->Register(&flash_corrupted_Mobius_Mark);
  flash_working->Register(&flash_working_Mobius_Mark);
}

bool flash_systemSAN::power_cycleActivity::Enabled(){
  OldEnabled=NewEnabled;
  NewEnabled=((flash_corrupted->Mark() == 1));
  return NewEnabled;
}

double flash_systemSAN::power_cycleActivity::DeterministicParamValue(){
  return 10000000000000000000;
  return 1.0;  // default rate if none is specified
}

double flash_systemSAN::power_cycleActivity::Weight(){ 
  return 1;
}

bool flash_systemSAN::power_cycleActivity::ReactivationPredicate(){ 
  return false;
}

bool flash_systemSAN::power_cycleActivity::ReactivationFunction(){ 
  return false;
}

double flash_systemSAN::power_cycleActivity::SampleDistribution(){
  return 10000000000000000000;
}

double* flash_systemSAN::power_cycleActivity::ReturnDistributionParameters(){
  TheDistributionParameters[0] = DeterministicParamValue();
  return TheDistributionParameters;
}

int flash_systemSAN::power_cycleActivity::Rank(){
  return 1;
}

BaseActionClass* flash_systemSAN::power_cycleActivity::Fire(){
  flash_corrupted->Mark() = 0;
  flash_working->Mark() = 1;
  return this;
}

