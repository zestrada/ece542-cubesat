

// This C++ file was created by SanEditor

#include "Atomic/ram_system/ram_systemSAN.h"

#include <stdlib.h>
#include <iostream>

#include <math.h>


/*****************************************************************
                         ram_systemSAN Constructor             
******************************************************************/


ram_systemSAN::ram_systemSAN(){


  seuGroup.initialize(2, "seuGroup");
  seuGroup.appendGroup((BaseGroupClass*) &seu_case1);
  seuGroup.appendGroup((BaseGroupClass*) &seu_case2);

  word_sefiGroup.initialize(2, "word_sefiGroup");
  word_sefiGroup.appendGroup((BaseGroupClass*) &word_sefi_case1);
  word_sefiGroup.appendGroup((BaseGroupClass*) &word_sefi_case2);

  Activity* InitialActionList[8]={
    &failure, //0
    &watchdog_reboot, //1
    &random_failure, //2
    &seu_case1, //3
    &seu_case2, //4
    &word_sefi_case1, //5
    &word_sefi_case2, //6
    &device_sefi  // 7
  };

  BaseGroupClass* InitialGroupList[6]={
    (BaseGroupClass*) &(watchdog_reboot), 
    (BaseGroupClass*) &(random_failure), 
    (BaseGroupClass*) &(seuGroup), 
    (BaseGroupClass*) &(word_sefiGroup), 
    (BaseGroupClass*) &(device_sefi), 
    (BaseGroupClass*) &(failure)
  };

  flash_corrupted = new Place("flash_corrupted" ,0);
  ram_working = new Place("ram_working" ,1);
  ram_corrupted = new Place("ram_corrupted" ,0);
  system_failed = new Place("system_failed" ,0);
  BaseStateVariableClass* InitialPlaces[4]={
    flash_corrupted,  // 0
    ram_working,  // 1
    ram_corrupted,  // 2
    system_failed   // 3
  };
  BaseStateVariableClass* InitialROPlaces[0]={
  };
  initializeSANModelNow("ram_system", 4, InitialPlaces, 
                        0, InitialROPlaces, 
                        8, InitialActionList, 6, InitialGroupList);


  assignPlacesToActivitiesInst();
  assignPlacesToActivitiesTimed();

  int AffectArcs[12][2]={ 
    {3,0}, {1,1}, {2,1}, {2,2}, {1,3}, {1,4}, {2,4}, {1,5}, {1,6}, 
    {2,6}, {1,7}, {2,7}
  };
  for(int n=0;n<12;n++) {
    AddAffectArc(InitialPlaces[AffectArcs[n][0]],
                 InitialActionList[AffectArcs[n][1]]);
  }
  int EnableArcs[10][2]={ 
    {0,0}, {2,0}, {3,0}, {2,1}, {2,2}, {1,3}, {1,4}, {1,5}, {1,6}, 
    {1,7}
  };
  for(int n=0;n<10;n++) {
    AddEnableArc(InitialPlaces[EnableArcs[n][0]],
                 InitialActionList[EnableArcs[n][1]]);
  }

  for(int n=0;n<8;n++) {
    InitialActionList[n]->LinkVariables();
  }
  CustomInitialization();

}

void ram_systemSAN::CustomInitialization() {

}
ram_systemSAN::~ram_systemSAN(){
  for (int i = 0; i < NumStateVariables-NumReadOnlyPlaces; i++)
    delete LocalStateVariables[i];
};

void ram_systemSAN::assignPlacesToActivitiesInst(){
  failure.flash_corrupted = (Place*) LocalStateVariables[0];
  failure.ram_corrupted = (Place*) LocalStateVariables[2];
  failure.system_failed = (Place*) LocalStateVariables[3];
}
void ram_systemSAN::assignPlacesToActivitiesTimed(){
  watchdog_reboot.ram_corrupted = (Place*) LocalStateVariables[2];
  watchdog_reboot.ram_working = (Place*) LocalStateVariables[1];
  random_failure.ram_corrupted = (Place*) LocalStateVariables[2];
  seu_case1.ram_working = (Place*) LocalStateVariables[1];
  seu_case2.ram_working = (Place*) LocalStateVariables[1];
  seu_case2.ram_corrupted = (Place*) LocalStateVariables[2];
  word_sefi_case1.ram_working = (Place*) LocalStateVariables[1];
  word_sefi_case2.ram_working = (Place*) LocalStateVariables[1];
  word_sefi_case2.ram_corrupted = (Place*) LocalStateVariables[2];
  device_sefi.ram_working = (Place*) LocalStateVariables[1];
  device_sefi.ram_corrupted = (Place*) LocalStateVariables[2];
}
/*****************************************************************/
/*                  Activity Method Definitions                  */
/*****************************************************************/

/*======================failureActivity========================*/


ram_systemSAN::failureActivity::failureActivity(){
  ActivityInitialize("failure",5,Instantaneous , RaceEnabled, 1,3, false);
}

void ram_systemSAN::failureActivity::LinkVariables(){
  flash_corrupted->Register(&flash_corrupted_Mobius_Mark);
  ram_corrupted->Register(&ram_corrupted_Mobius_Mark);
  system_failed->Register(&system_failed_Mobius_Mark);
}

bool ram_systemSAN::failureActivity::Enabled(){
  OldEnabled=NewEnabled;
  NewEnabled=((flash_corrupted->Mark() > 0 && ram_corrupted->Mark() > 0 && system_failed->Mark() == 0));
  return NewEnabled;
}

double ram_systemSAN::failureActivity::Weight(){ 
  return 1;
}

bool ram_systemSAN::failureActivity::ReactivationPredicate(){ 
  return false;
}

bool ram_systemSAN::failureActivity::ReactivationFunction(){ 
  return false;
}

double ram_systemSAN::failureActivity::SampleDistribution(){
  return 0;
}

double* ram_systemSAN::failureActivity::ReturnDistributionParameters(){
    return NULL;
}

int ram_systemSAN::failureActivity::Rank(){
  return 1;
}

BaseActionClass* ram_systemSAN::failureActivity::Fire(){
  ;
  (*(system_failed_Mobius_Mark))++;
  return this;
}

/*======================watchdog_rebootActivity========================*/

ram_systemSAN::watchdog_rebootActivity::watchdog_rebootActivity(){
  TheDistributionParameters = new double[1];
  ActivityInitialize("watchdog_reboot",0,Deterministic, RaceEnabled, 2,1, false);
}

ram_systemSAN::watchdog_rebootActivity::~watchdog_rebootActivity(){
  delete[] TheDistributionParameters;
}

void ram_systemSAN::watchdog_rebootActivity::LinkVariables(){
  ram_corrupted->Register(&ram_corrupted_Mobius_Mark);
  ram_working->Register(&ram_working_Mobius_Mark);
}

bool ram_systemSAN::watchdog_rebootActivity::Enabled(){
  OldEnabled=NewEnabled;
  NewEnabled=((ram_corrupted->Mark() > 0));
  return NewEnabled;
}

double ram_systemSAN::watchdog_rebootActivity::DeterministicParamValue(){
  return 3.47e-3;
  return 1.0;  // default rate if none is specified
}

double ram_systemSAN::watchdog_rebootActivity::Weight(){ 
  return 1;
}

bool ram_systemSAN::watchdog_rebootActivity::ReactivationPredicate(){ 
  return false;
}

bool ram_systemSAN::watchdog_rebootActivity::ReactivationFunction(){ 
  return false;
}

double ram_systemSAN::watchdog_rebootActivity::SampleDistribution(){
  return 3.47e-3;
}

double* ram_systemSAN::watchdog_rebootActivity::ReturnDistributionParameters(){
  TheDistributionParameters[0] = DeterministicParamValue();
  return TheDistributionParameters;
}

int ram_systemSAN::watchdog_rebootActivity::Rank(){
  return 1;
}

BaseActionClass* ram_systemSAN::watchdog_rebootActivity::Fire(){
  ;
  ram_working->Mark() = 1;
ram_corrupted->Mark() = 0;
  return this;
}

/*======================random_failureActivity========================*/

ram_systemSAN::random_failureActivity::random_failureActivity(){
  TheDistributionParameters = new double[1];
  ActivityInitialize("random_failure",1,Exponential, RaceEnabled, 1,1, false);
}

ram_systemSAN::random_failureActivity::~random_failureActivity(){
  delete[] TheDistributionParameters;
}

void ram_systemSAN::random_failureActivity::LinkVariables(){
  ram_corrupted->Register(&ram_corrupted_Mobius_Mark);
}

bool ram_systemSAN::random_failureActivity::Enabled(){
  OldEnabled=NewEnabled;
  NewEnabled=((ram_corrupted->Mark() == 0));
  return NewEnabled;
}

double ram_systemSAN::random_failureActivity::Rate(){
  return random_failure_rate;
  return 1.0;  // default rate if none is specified
}

double ram_systemSAN::random_failureActivity::Weight(){ 
  return 1;
}

bool ram_systemSAN::random_failureActivity::ReactivationPredicate(){ 
  return false;
}

bool ram_systemSAN::random_failureActivity::ReactivationFunction(){ 
  return false;
}

double ram_systemSAN::random_failureActivity::SampleDistribution(){
  return TheDistribution->Exponential(random_failure_rate);
}

double* ram_systemSAN::random_failureActivity::ReturnDistributionParameters(){
  TheDistributionParameters[0] = Rate();
  return TheDistributionParameters;
}

int ram_systemSAN::random_failureActivity::Rank(){
  return 1;
}

BaseActionClass* ram_systemSAN::random_failureActivity::Fire(){
  ;
  (*(ram_corrupted_Mobius_Mark))++;
  return this;
}

/*======================seuActivity_case1========================*/

ram_systemSAN::seuActivity_case1::seuActivity_case1(){
  TheDistributionParameters = new double[1];
  ActivityInitialize("seu_case1",2,Exponential, RaceEnabled, 1,1, false);
}

ram_systemSAN::seuActivity_case1::~seuActivity_case1(){
  delete[] TheDistributionParameters;
}

void ram_systemSAN::seuActivity_case1::LinkVariables(){
  ram_working->Register(&ram_working_Mobius_Mark);
}

bool ram_systemSAN::seuActivity_case1::Enabled(){
  OldEnabled=NewEnabled;
  NewEnabled=(((*(ram_working_Mobius_Mark)) >=1));
  return NewEnabled;
}

double ram_systemSAN::seuActivity_case1::Rate(){
  return 6.012;
  return 1.0;  // default rate if none is specified
}

double ram_systemSAN::seuActivity_case1::Weight(){ 
  return 1-(ram_size/512);
}

bool ram_systemSAN::seuActivity_case1::ReactivationPredicate(){ 
  return false;
}

bool ram_systemSAN::seuActivity_case1::ReactivationFunction(){ 
  return false;
}

double ram_systemSAN::seuActivity_case1::SampleDistribution(){
  return TheDistribution->Exponential(6.012);
}

double* ram_systemSAN::seuActivity_case1::ReturnDistributionParameters(){
  TheDistributionParameters[0] = Rate();
  return TheDistributionParameters;
}

int ram_systemSAN::seuActivity_case1::Rank(){
  return 1;
}

BaseActionClass* ram_systemSAN::seuActivity_case1::Fire(){
  (*(ram_working_Mobius_Mark))--;
  (*(ram_working_Mobius_Mark))++;
  return this;
}

/*======================seuActivity_case2========================*/

ram_systemSAN::seuActivity_case2::seuActivity_case2(){
  TheDistributionParameters = new double[1];
  ActivityInitialize("seu_case2",2,Exponential, RaceEnabled, 2,1, false);
}

ram_systemSAN::seuActivity_case2::~seuActivity_case2(){
  delete[] TheDistributionParameters;
}

void ram_systemSAN::seuActivity_case2::LinkVariables(){
  ram_working->Register(&ram_working_Mobius_Mark);
  ram_corrupted->Register(&ram_corrupted_Mobius_Mark);
}

bool ram_systemSAN::seuActivity_case2::Enabled(){
  OldEnabled=NewEnabled;
  NewEnabled=(((*(ram_working_Mobius_Mark)) >=1));
  return NewEnabled;
}

double ram_systemSAN::seuActivity_case2::Rate(){
  return 6.012;
  return 1.0;  // default rate if none is specified
}

double ram_systemSAN::seuActivity_case2::Weight(){ 
  return ram_size/512;
}

bool ram_systemSAN::seuActivity_case2::ReactivationPredicate(){ 
  return false;
}

bool ram_systemSAN::seuActivity_case2::ReactivationFunction(){ 
  return false;
}

double ram_systemSAN::seuActivity_case2::SampleDistribution(){
  return TheDistribution->Exponential(6.012);
}

double* ram_systemSAN::seuActivity_case2::ReturnDistributionParameters(){
  TheDistributionParameters[0] = Rate();
  return TheDistributionParameters;
}

int ram_systemSAN::seuActivity_case2::Rank(){
  return 1;
}

BaseActionClass* ram_systemSAN::seuActivity_case2::Fire(){
  (*(ram_working_Mobius_Mark))--;
  (*(ram_corrupted_Mobius_Mark))++;
  return this;
}

/*======================word_sefiActivity_case1========================*/

ram_systemSAN::word_sefiActivity_case1::word_sefiActivity_case1(){
  TheDistributionParameters = new double[1];
  ActivityInitialize("word_sefi_case1",3,Exponential, RaceEnabled, 1,1, false);
}

ram_systemSAN::word_sefiActivity_case1::~word_sefiActivity_case1(){
  delete[] TheDistributionParameters;
}

void ram_systemSAN::word_sefiActivity_case1::LinkVariables(){
  ram_working->Register(&ram_working_Mobius_Mark);
}

bool ram_systemSAN::word_sefiActivity_case1::Enabled(){
  OldEnabled=NewEnabled;
  NewEnabled=(((*(ram_working_Mobius_Mark)) >=1));
  return NewEnabled;
}

double ram_systemSAN::word_sefiActivity_case1::Rate(){
  return //2.36e-5/8
0;
  return 1.0;  // default rate if none is specified
}

double ram_systemSAN::word_sefiActivity_case1::Weight(){ 
  return 1-(ram_size/512);
}

bool ram_systemSAN::word_sefiActivity_case1::ReactivationPredicate(){ 
  return false;
}

bool ram_systemSAN::word_sefiActivity_case1::ReactivationFunction(){ 
  return false;
}

double ram_systemSAN::word_sefiActivity_case1::SampleDistribution(){
  return TheDistribution->Exponential(Rate());
}

double* ram_systemSAN::word_sefiActivity_case1::ReturnDistributionParameters(){
  TheDistributionParameters[0] = Rate();
  return TheDistributionParameters;
}

int ram_systemSAN::word_sefiActivity_case1::Rank(){
  return 1;
}

BaseActionClass* ram_systemSAN::word_sefiActivity_case1::Fire(){
  (*(ram_working_Mobius_Mark))--;
  (*(ram_working_Mobius_Mark))++;
  return this;
}

/*======================word_sefiActivity_case2========================*/

ram_systemSAN::word_sefiActivity_case2::word_sefiActivity_case2(){
  TheDistributionParameters = new double[1];
  ActivityInitialize("word_sefi_case2",3,Exponential, RaceEnabled, 2,1, false);
}

ram_systemSAN::word_sefiActivity_case2::~word_sefiActivity_case2(){
  delete[] TheDistributionParameters;
}

void ram_systemSAN::word_sefiActivity_case2::LinkVariables(){
  ram_working->Register(&ram_working_Mobius_Mark);
  ram_corrupted->Register(&ram_corrupted_Mobius_Mark);
}

bool ram_systemSAN::word_sefiActivity_case2::Enabled(){
  OldEnabled=NewEnabled;
  NewEnabled=(((*(ram_working_Mobius_Mark)) >=1));
  return NewEnabled;
}

double ram_systemSAN::word_sefiActivity_case2::Rate(){
  return //2.36e-5/8
0;
  return 1.0;  // default rate if none is specified
}

double ram_systemSAN::word_sefiActivity_case2::Weight(){ 
  return ram_size/512;
}

bool ram_systemSAN::word_sefiActivity_case2::ReactivationPredicate(){ 
  return false;
}

bool ram_systemSAN::word_sefiActivity_case2::ReactivationFunction(){ 
  return false;
}

double ram_systemSAN::word_sefiActivity_case2::SampleDistribution(){
  return TheDistribution->Exponential(Rate());
}

double* ram_systemSAN::word_sefiActivity_case2::ReturnDistributionParameters(){
  TheDistributionParameters[0] = Rate();
  return TheDistributionParameters;
}

int ram_systemSAN::word_sefiActivity_case2::Rank(){
  return 1;
}

BaseActionClass* ram_systemSAN::word_sefiActivity_case2::Fire(){
  (*(ram_working_Mobius_Mark))--;
  (*(ram_corrupted_Mobius_Mark))++;
  return this;
}

/*======================device_sefiActivity========================*/

ram_systemSAN::device_sefiActivity::device_sefiActivity(){
  TheDistributionParameters = new double[1];
  ActivityInitialize("device_sefi",4,Exponential, RaceEnabled, 2,1, false);
}

ram_systemSAN::device_sefiActivity::~device_sefiActivity(){
  delete[] TheDistributionParameters;
}

void ram_systemSAN::device_sefiActivity::LinkVariables(){
  ram_working->Register(&ram_working_Mobius_Mark);
  ram_corrupted->Register(&ram_corrupted_Mobius_Mark);
}

bool ram_systemSAN::device_sefiActivity::Enabled(){
  OldEnabled=NewEnabled;
  NewEnabled=(((*(ram_working_Mobius_Mark)) >=1));
  return NewEnabled;
}

double ram_systemSAN::device_sefiActivity::Rate(){
  return 3.8e-2;
  return 1.0;  // default rate if none is specified
}

double ram_systemSAN::device_sefiActivity::Weight(){ 
  return 1;
}

bool ram_systemSAN::device_sefiActivity::ReactivationPredicate(){ 
  return false;
}

bool ram_systemSAN::device_sefiActivity::ReactivationFunction(){ 
  return false;
}

double ram_systemSAN::device_sefiActivity::SampleDistribution(){
  return TheDistribution->Exponential(3.8e-2);
}

double* ram_systemSAN::device_sefiActivity::ReturnDistributionParameters(){
  TheDistributionParameters[0] = Rate();
  return TheDistributionParameters;
}

int ram_systemSAN::device_sefiActivity::Rank(){
  return 1;
}

BaseActionClass* ram_systemSAN::device_sefiActivity::Fire(){
  (*(ram_working_Mobius_Mark))--;
  (*(ram_corrupted_Mobius_Mark))++;
  return this;
}

