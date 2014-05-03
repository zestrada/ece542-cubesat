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
extern UserDistributions* TheDistribution;

void MemoryError();


/*********************************************************************
               ram_systemSAN Submodel Definition                   
*********************************************************************/

class ram_systemSAN:public SANModel{
public:

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

class bit_errorActivity_case1:public Activity {
public:

  Place* ram_working;
  short* ram_working_Mobius_Mark;

  double* TheDistributionParameters;
  bit_errorActivity_case1();
  ~bit_errorActivity_case1();
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
}; // bit_errorActivity_case1Activity

class bit_errorActivity_case2:public Activity {
public:

  Place* ram_working;
  short* ram_working_Mobius_Mark;
  Place* ram_corrupted;
  short* ram_corrupted_Mobius_Mark;

  double* TheDistributionParameters;
  bit_errorActivity_case2();
  ~bit_errorActivity_case2();
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
}; // bit_errorActivity_case2Activity

class page_errorActivity_case1:public Activity {
public:

  Place* ram_working;
  short* ram_working_Mobius_Mark;

  double* TheDistributionParameters;
  page_errorActivity_case1();
  ~page_errorActivity_case1();
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
}; // page_errorActivity_case1Activity

class page_errorActivity_case2:public Activity {
public:

  Place* ram_working;
  short* ram_working_Mobius_Mark;
  Place* ram_corrupted;
  short* ram_corrupted_Mobius_Mark;

  double* TheDistributionParameters;
  page_errorActivity_case2();
  ~page_errorActivity_case2();
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
}; // page_errorActivity_case2Activity

  //List of user-specified place names
  Place* flash_corrupted;
  Place* ram_working;
  Place* ram_corrupted;

  // Create instances of all actvities
  watchdog_rebootActivity watchdog_reboot;
  random_failureActivity random_failure;
  bit_errorActivity_case1 bit_error_case1;
  bit_errorActivity_case2 bit_error_case2;
  page_errorActivity_case1 page_error_case1;
  page_errorActivity_case2 page_error_case2;
  //Create instances of all groups 
  EmptyGroup ImmediateGroup;
  PostselectGroup bit_errorGroup;  PostselectGroup page_errorGroup;
  ram_systemSAN();
  ~ram_systemSAN();
  void CustomInitialization();

  void assignPlacesToActivitiesInst();
  void assignPlacesToActivitiesTimed();
}; // end ram_systemSAN

#endif // ram_systemSAN_H_
