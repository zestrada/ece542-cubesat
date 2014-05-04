#ifndef redundant_flash_systemSAN_H_
#define redundant_flash_systemSAN_H_

#include "Cpp/BaseClasses/EmptyGroup.h"
#include "Cpp/BaseClasses/PreselectGroup.h"
#include "Cpp/BaseClasses/PostselectGroup.h"
#include "Cpp/BaseClasses/state/StructStateVariable.h"
#include "Cpp/BaseClasses/state/ArrayStateVariable.h"
#include "Cpp/BaseClasses/SAN/SANModel.h" 
#include "Cpp/BaseClasses/SAN/Place.h"
#include "Cpp/BaseClasses/SAN/ExtendedPlace.h"
extern float flash_size;
extern float power_cycle_rate;
extern short num_replicas;
extern UserDistributions* TheDistribution;

void MemoryError();


/*********************************************************************
               redundant_flash_systemSAN Submodel Definition                   
*********************************************************************/

class redundant_flash_systemSAN:public SANModel{
public:

class seuActivity_case1:public Activity {
public:

  Place* replicas_available;
  short* replicas_available_Mobius_Mark;

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

  Place* replicas_available;
  short* replicas_available_Mobius_Mark;
  Place* flash_corrupted;
  short* flash_corrupted_Mobius_Mark;

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

class sefiActivity:public Activity {
public:

  Place* replicas_available;
  short* replicas_available_Mobius_Mark;
  Place* flash_corrupted;
  short* flash_corrupted_Mobius_Mark;

  double* TheDistributionParameters;
  sefiActivity();
  ~sefiActivity();
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
}; // sefiActivityActivity

class power_cycleActivity:public Activity {
public:

  Place* replicas_available;
  short* replicas_available_Mobius_Mark;
  Place* flash_corrupted;
  short* flash_corrupted_Mobius_Mark;

  double* TheDistributionParameters;
  power_cycleActivity();
  ~power_cycleActivity();
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
}; // power_cycleActivityActivity

  //List of user-specified place names
  Place* flash_corrupted;
  Place* replicas_available;

  // Create instances of all actvities
  seuActivity_case1 seu_case1;
  seuActivity_case2 seu_case2;
  sefiActivity sefi;
  power_cycleActivity power_cycle;
  //Create instances of all groups 
  EmptyGroup ImmediateGroup;
  PostselectGroup seuGroup;
  redundant_flash_systemSAN();
  ~redundant_flash_systemSAN();
  void CustomInitialization();

  void assignPlacesToActivitiesInst();
  void assignPlacesToActivitiesTimed();
}; // end redundant_flash_systemSAN

#endif // redundant_flash_systemSAN_H_
