#ifndef flash_systemSAN_H_
#define flash_systemSAN_H_

#include "Cpp/BaseClasses/EmptyGroup.h"
#include "Cpp/BaseClasses/PreselectGroup.h"
#include "Cpp/BaseClasses/PostselectGroup.h"
#include "Cpp/BaseClasses/state/StructStateVariable.h"
#include "Cpp/BaseClasses/state/ArrayStateVariable.h"
#include "Cpp/BaseClasses/SAN/SANModel.h" 
#include "Cpp/BaseClasses/SAN/Place.h"
#include "Cpp/BaseClasses/SAN/ExtendedPlace.h"
extern float flash_size;
extern UserDistributions* TheDistribution;

void MemoryError();


/*********************************************************************
               flash_systemSAN Submodel Definition                   
*********************************************************************/

class flash_systemSAN:public SANModel{
public:

class seuActivity_case1:public Activity {
public:

  Place* flash_working;
  short* flash_working_Mobius_Mark;

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

  Place* flash_working;
  short* flash_working_Mobius_Mark;
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

  Place* flash_working;
  short* flash_working_Mobius_Mark;
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

  Place* flash_corrupted;
  short* flash_corrupted_Mobius_Mark;
  Place* flash_working;
  short* flash_working_Mobius_Mark;

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
  Place* flash_working;

  // Create instances of all actvities
  seuActivity_case1 seu_case1;
  seuActivity_case2 seu_case2;
  sefiActivity sefi;
  power_cycleActivity power_cycle;
  //Create instances of all groups 
  EmptyGroup ImmediateGroup;
  PostselectGroup seuGroup;
  flash_systemSAN();
  ~flash_systemSAN();
  void CustomInitialization();

  void assignPlacesToActivitiesInst();
  void assignPlacesToActivitiesTimed();
}; // end flash_systemSAN

#endif // flash_systemSAN_H_
