#ifndef ram_systemSAN_H_
#define ram_systemSAN_H_

#include "Cpp/BaseClasses/EmptyGroup.h"
#include "Cpp/BaseClasses/PreselectGroup.h"
#include "Cpp/BaseClasses/PostselectGroup.h"
#include "Cpp/BaseClasses/state/StructStateVariable.h"
#include "Cpp/BaseClasses/state/ArrayStateVariable.h"
#include "Cpp/BaseClasses/SAN/SANModel.h" 
#include "Cpp/BaseClasses/SAN/Place.h"
#include "Cpp/BaseClasses/SAN/ExtendedPlace.h"
extern float ram_size;
extern float random_failure_rate;
extern UserDistributions* TheDistribution;

void MemoryError();


/*********************************************************************
               ram_systemSAN Submodel Definition                   
*********************************************************************/

class ram_systemSAN:public SANModel{
public:

class failureActivity:public Activity {
public:

  Place* flash_corrupted;
  short* flash_corrupted_Mobius_Mark;
  Place* ram_corrupted;
  short* ram_corrupted_Mobius_Mark;
  Place* system_failed;
  short* system_failed_Mobius_Mark;

  double* TheDistributionParameters;
  failureActivity();
  double Rate(){return 0;}
  bool Enabled();
  void LinkVariables();
  double Weight();
  bool ReactivationPredicate();
  bool ReactivationFunction();
  double SampleDistribution();
  double* ReturnDistributionParameters();
  int Rank();
  BaseActionClass* Fire();
}; // failureActivityActivity

class watchdog_rebootActivity:public Activity {
public:

  Place* ram_corrupted;
  short* ram_corrupted_Mobius_Mark;
  Place* ram_working;
  short* ram_working_Mobius_Mark;

  double* TheDistributionParameters;
  watchdog_rebootActivity();
  ~watchdog_rebootActivity();
  double Rate(){return 0;}
  bool Enabled();
  void LinkVariables();
  double Weight();
  bool ReactivationPredicate();
  bool ReactivationFunction();
  double SampleDistribution();
  double* ReturnDistributionParameters();
  int Rank();
  BaseActionClass* Fire();
  double DeterministicParamValue();
}; // watchdog_rebootActivityActivity

class random_failureActivity:public Activity {
public:

  Place* ram_corrupted;
  short* ram_corrupted_Mobius_Mark;

  double* TheDistributionParameters;
  random_failureActivity();
  ~random_failureActivity();
  bool Enabled();
  void LinkVariables();
  double Weight();
  bool ReactivationPredicate();
  bool ReactivationFunction();
  double SampleDistribution();
  double* ReturnDistributionParameters();
  int Rank();
  BaseActionClass* Fire();
  double Rate();
}; // random_failureActivityActivity

class seuActivity_case1:public Activity {
public:

  Place* ram_working;
  short* ram_working_Mobius_Mark;

  double* TheDistributionParameters;
  seuActivity_case1();
  ~seuActivity_case1();
  bool Enabled();
  void LinkVariables();
  double Weight();
  bool ReactivationPredicate();
  bool ReactivationFunction();
  double SampleDistribution();
  double* ReturnDistributionParameters();
  int Rank();
  BaseActionClass* Fire();
  double Rate();
}; // seuActivity_case1Activity

class seuActivity_case2:public Activity {
public:

  Place* ram_working;
  short* ram_working_Mobius_Mark;
  Place* ram_corrupted;
  short* ram_corrupted_Mobius_Mark;

  double* TheDistributionParameters;
  seuActivity_case2();
  ~seuActivity_case2();
  bool Enabled();
  void LinkVariables();
  double Weight();
  bool ReactivationPredicate();
  bool ReactivationFunction();
  double SampleDistribution();
  double* ReturnDistributionParameters();
  int Rank();
  BaseActionClass* Fire();
  double Rate();
}; // seuActivity_case2Activity

class word_sefiActivity_case1:public Activity {
public:

  Place* ram_working;
  short* ram_working_Mobius_Mark;

  double* TheDistributionParameters;
  word_sefiActivity_case1();
  ~word_sefiActivity_case1();
  bool Enabled();
  void LinkVariables();
  double Weight();
  bool ReactivationPredicate();
  bool ReactivationFunction();
  double SampleDistribution();
  double* ReturnDistributionParameters();
  int Rank();
  BaseActionClass* Fire();
  double Rate();
}; // word_sefiActivity_case1Activity

class word_sefiActivity_case2:public Activity {
public:

  Place* ram_working;
  short* ram_working_Mobius_Mark;
  Place* ram_corrupted;
  short* ram_corrupted_Mobius_Mark;

  double* TheDistributionParameters;
  word_sefiActivity_case2();
  ~word_sefiActivity_case2();
  bool Enabled();
  void LinkVariables();
  double Weight();
  bool ReactivationPredicate();
  bool ReactivationFunction();
  double SampleDistribution();
  double* ReturnDistributionParameters();
  int Rank();
  BaseActionClass* Fire();
  double Rate();
}; // word_sefiActivity_case2Activity

class device_sefiActivity:public Activity {
public:

  Place* ram_working;
  short* ram_working_Mobius_Mark;
  Place* ram_corrupted;
  short* ram_corrupted_Mobius_Mark;

  double* TheDistributionParameters;
  device_sefiActivity();
  ~device_sefiActivity();
  bool Enabled();
  void LinkVariables();
  double Weight();
  bool ReactivationPredicate();
  bool ReactivationFunction();
  double SampleDistribution();
  double* ReturnDistributionParameters();
  int Rank();
  BaseActionClass* Fire();
  double Rate();
}; // device_sefiActivityActivity

  //List of user-specified place names
  Place* flash_corrupted;
  Place* ram_working;
  Place* ram_corrupted;
  Place* system_failed;

  // Create instances of all actvities
  failureActivity failure;
  watchdog_rebootActivity watchdog_reboot;
  random_failureActivity random_failure;
  seuActivity_case1 seu_case1;
  seuActivity_case2 seu_case2;
  word_sefiActivity_case1 word_sefi_case1;
  word_sefiActivity_case2 word_sefi_case2;
  device_sefiActivity device_sefi;
  //Create instances of all groups 
  PreselectGroup ImmediateGroup;
  PostselectGroup failureGroup;
  PostselectGroup seuGroup;  PostselectGroup word_sefiGroup;
  ram_systemSAN();
  ~ram_systemSAN();
  void CustomInitialization();

  void assignPlacesToActivitiesInst();
  void assignPlacesToActivitiesTimed();
}; // end ram_systemSAN

#endif // ram_systemSAN_H_
