

// This C++ file was created by SanEditor

#include "Atomic/ram_system/ram_systemSAN.h"

#include <stdlib.h>
#include <iostream>

#include <math.h>


/*****************************************************************
                         ram_systemSAN Constructor             
******************************************************************/


ram_systemSAN::ram_systemSAN(){


  bit_errorGroup.initialize(2, "bit_errorGroup");
  bit_errorGroup.appendGroup((BaseGroupClass*) &bit_error_case1);
  bit_errorGroup.appendGroup((BaseGroupClass*) &bit_error_case2);

  page_errorGroup.initialize(2, "page_errorGroup");
  page_errorGroup.appendGroup((BaseGroupClass*) &page_error_case1);
  page_errorGroup.appendGroup((BaseGroupClass*) &page_error_case2);

  Activity* InitialActionList[6]={
    &watchdog_reboot, //0
    &random_failure, //1
    &bit_error_case1, //2
    &bit_error_case2, //3
    &page_error_case1, //4
    &page_error_case2  // 5
  };

  BaseGroupClass* InitialGroupList[4]={
    (BaseGroupClass*) &(watchdog_reboot), 
    (BaseGroupClass*) &(random_failure), 
    (BaseGroupClass*) &(bit_errorGroup), 
    (BaseGroupClass*) &(page_errorGroup)
  };

  flash_corrupted = new Place("flash_corrupted" ,0);
  ram_working = new Place("ram_working" ,1);
  ram_corrupted = new Place("ram_corrupted" ,0);
  BaseStateVariableClass* InitialPlaces[3]={
    flash_corrupted,  // 0
    ram_working,  // 1
    ram_corrupted   // 2
  };
  BaseStateVariableClass* InitialROPlaces[0]={
  };
  initializeSANModelNow("ram_system", 3, InitialPlaces, 
                        0, InitialROPlaces, 
                        6, InitialActionList, 4, InitialGroupList);


  assignPlacesToActivitiesInst();
  assignPlacesToActivitiesTimed();

  int AffectArcs[9][2]={ 
    {2,0}, {1,0}, {2,1}, {1,2}, {1,3}, {2,3}, {1,4}, {1,5}, {2,5}
  };
  for(int n=0;n<9;n++) {
    AddAffectArc(InitialPlaces[AffectArcs[n][0]],
                 InitialActionList[AffectArcs[n][1]]);
  }
  int EnableArcs[6][2]={ 
    {2,0}, {2,1}, {1,2}, {1,3}, {1,4}, {1,5}
  };
  for(int n=0;n<6;n++) {
    AddEnableArc(InitialPlaces[EnableArcs[n][0]],
                 InitialActionList[EnableArcs[n][1]]);
  }

  for(int n=0;n<6;n++) {
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
}
void ram_systemSAN::assignPlacesToActivitiesTimed(){
  watchdog_reboot.ram_corrupted = (Place*) LocalStateVariables[2];
  watchdog_reboot.ram_working = (Place*) LocalStateVariables[1];
  random_failure.ram_corrupted = (Place*) LocalStateVariables[2];
  bit_error_case1.ram_working = (Place*) LocalStateVariables[1];
  bit_error_case2.ram_working = (Place*) LocalStateVariables[1];
  bit_error_case2.ram_corrupted = (Place*) LocalStateVariables[2];
  page_error_case1.ram_working = (Place*) LocalStateVariables[1];
  page_error_case2.ram_working = (Place*) LocalStateVariables[1];
  page_error_case2.ram_corrupted = (Place*) LocalStateVariables[2];
}
/*****************************************************************/
/*                  Activity Method Definitions                  */
/*****************************************************************/

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
  ram_corrupted->Mark() = 0;
  ram_working->Mark() = 1;
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
  return 5.48e-3;
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
  return TheDistribution->Exponential(5.48e-3);
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

/*======================bit_errorActivity_case1========================*/

ram_systemSAN::bit_errorActivity_case1::bit_errorActivity_case1(){
  TheDistributionParameters = new double[1];
  ActivityInitialize("bit_error_case1",2,Exponential, RaceEnabled, 1,1, false);
}

ram_systemSAN::bit_errorActivity_case1::~bit_errorActivity_case1(){
  delete[] TheDistributionParameters;
}

void ram_systemSAN::bit_errorActivity_case1::LinkVariables(){
  ram_working->Register(&ram_working_Mobius_Mark);
}

bool ram_systemSAN::bit_errorActivity_case1::Enabled(){
  OldEnabled=NewEnabled;
  NewEnabled=(((*(ram_working_Mobius_Mark)) >=1));
  return NewEnabled;
}

double ram_systemSAN::bit_errorActivity_case1::Rate(){
  return 6.012;
  return 1.0;  // default rate if none is specified
}

double ram_systemSAN::bit_errorActivity_case1::Weight(){ 
  return 1-(ram_size/512);
}

bool ram_systemSAN::bit_errorActivity_case1::ReactivationPredicate(){ 
  return false;
}

bool ram_systemSAN::bit_errorActivity_case1::ReactivationFunction(){ 
  return false;
}

double ram_systemSAN::bit_errorActivity_case1::SampleDistribution(){
  return TheDistribution->Exponential(6.012);
}

double* ram_systemSAN::bit_errorActivity_case1::ReturnDistributionParameters(){
  TheDistributionParameters[0] = Rate();
  return TheDistributionParameters;
}

int ram_systemSAN::bit_errorActivity_case1::Rank(){
  return 1;
}

BaseActionClass* ram_systemSAN::bit_errorActivity_case1::Fire(){
  (*(ram_working_Mobius_Mark))--;
  (*(ram_working_Mobius_Mark))++;
  return this;
}

/*======================bit_errorActivity_case2========================*/

ram_systemSAN::bit_errorActivity_case2::bit_errorActivity_case2(){
  TheDistributionParameters = new double[1];
  ActivityInitialize("bit_error_case2",2,Exponential, RaceEnabled, 2,1, false);
}

ram_systemSAN::bit_errorActivity_case2::~bit_errorActivity_case2(){
  delete[] TheDistributionParameters;
}

void ram_systemSAN::bit_errorActivity_case2::LinkVariables(){
  ram_working->Register(&ram_working_Mobius_Mark);
  ram_corrupted->Register(&ram_corrupted_Mobius_Mark);
}

bool ram_systemSAN::bit_errorActivity_case2::Enabled(){
  OldEnabled=NewEnabled;
  NewEnabled=(((*(ram_working_Mobius_Mark)) >=1));
  return NewEnabled;
}

double ram_systemSAN::bit_errorActivity_case2::Rate(){
  return 6.012;
  return 1.0;  // default rate if none is specified
}

double ram_systemSAN::bit_errorActivity_case2::Weight(){ 
  return ram_size/512;
}

bool ram_systemSAN::bit_errorActivity_case2::ReactivationPredicate(){ 
  return false;
}

bool ram_systemSAN::bit_errorActivity_case2::ReactivationFunction(){ 
  return false;
}

double ram_systemSAN::bit_errorActivity_case2::SampleDistribution(){
  return TheDistribution->Exponential(6.012);
}

double* ram_systemSAN::bit_errorActivity_case2::ReturnDistributionParameters(){
  TheDistributionParameters[0] = Rate();
  return TheDistributionParameters;
}

int ram_systemSAN::bit_errorActivity_case2::Rank(){
  return 1;
}

BaseActionClass* ram_systemSAN::bit_errorActivity_case2::Fire(){
  (*(ram_working_Mobius_Mark))--;
  (*(ram_corrupted_Mobius_Mark))++;
  return this;
}

/*======================page_errorActivity_case1========================*/

ram_systemSAN::page_errorActivity_case1::page_errorActivity_case1(){
  TheDistributionParameters = new double[1];
  ActivityInitialize("page_error_case1",3,Exponential, RaceEnabled, 1,1, false);
}

ram_systemSAN::page_errorActivity_case1::~page_errorActivity_case1(){
  delete[] TheDistributionParameters;
}

void ram_systemSAN::page_errorActivity_case1::LinkVariables(){
  ram_working->Register(&ram_working_Mobius_Mark);
}

bool ram_systemSAN::page_errorActivity_case1::Enabled(){
  OldEnabled=NewEnabled;
  NewEnabled=(((*(ram_working_Mobius_Mark)) >=1));
  return NewEnabled;
}

double ram_systemSAN::page_errorActivity_case1::Rate(){
  return 2.36e-5/8;
  return 1.0;  // default rate if none is specified
}

double ram_systemSAN::page_errorActivity_case1::Weight(){ 
  return 0.75;
}

bool ram_systemSAN::page_errorActivity_case1::ReactivationPredicate(){ 
  return false;
}

bool ram_systemSAN::page_errorActivity_case1::ReactivationFunction(){ 
  return false;
}

double ram_systemSAN::page_errorActivity_case1::SampleDistribution(){
  return TheDistribution->Exponential(2.36e-5/8);
}

double* ram_systemSAN::page_errorActivity_case1::ReturnDistributionParameters(){
  TheDistributionParameters[0] = Rate();
  return TheDistributionParameters;
}

int ram_systemSAN::page_errorActivity_case1::Rank(){
  return 1;
}

BaseActionClass* ram_systemSAN::page_errorActivity_case1::Fire(){
  (*(ram_working_Mobius_Mark))--;
  (*(ram_working_Mobius_Mark))++;
  return this;
}

/*======================page_errorActivity_case2========================*/

ram_systemSAN::page_errorActivity_case2::page_errorActivity_case2(){
  TheDistributionParameters = new double[1];
  ActivityInitialize("page_error_case2",3,Exponential, RaceEnabled, 2,1, false);
}

ram_systemSAN::page_errorActivity_case2::~page_errorActivity_case2(){
  delete[] TheDistributionParameters;
}

void ram_systemSAN::page_errorActivity_case2::LinkVariables(){
  ram_working->Register(&ram_working_Mobius_Mark);
  ram_corrupted->Register(&ram_corrupted_Mobius_Mark);
}

bool ram_systemSAN::page_errorActivity_case2::Enabled(){
  OldEnabled=NewEnabled;
  NewEnabled=(((*(ram_working_Mobius_Mark)) >=1));
  return NewEnabled;
}

double ram_systemSAN::page_errorActivity_case2::Rate(){
  return 2.36e-5/8;
  return 1.0;  // default rate if none is specified
}

double ram_systemSAN::page_errorActivity_case2::Weight(){ 
  return 0.25;
}

bool ram_systemSAN::page_errorActivity_case2::ReactivationPredicate(){ 
  return false;
}

bool ram_systemSAN::page_errorActivity_case2::ReactivationFunction(){ 
  return false;
}

double ram_systemSAN::page_errorActivity_case2::SampleDistribution(){
  return TheDistribution->Exponential(2.36e-5/8);
}

double* ram_systemSAN::page_errorActivity_case2::ReturnDistributionParameters(){
  TheDistributionParameters[0] = Rate();
  return TheDistributionParameters;
}

int ram_systemSAN::page_errorActivity_case2::Rank(){
  return 1;
}

BaseActionClass* ram_systemSAN::page_errorActivity_case2::Fire(){
  (*(ram_working_Mobius_Mark))--;
  (*(ram_corrupted_Mobius_Mark))++;
  return this;
}

