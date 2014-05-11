#ifndef pretty_redundant_controller_flash_systemSAN_H_
#define pretty_redundant_controller_flash_systemSAN_H_

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
extern short num_devices;
extern UserDistributions* TheDistribution;

void MemoryError();


/*********************************************************************
               pretty_redundant_controller_flash_systemSAN Submodel Definition                   
*********************************************************************/

class pretty_redundant_controller_flash_systemSAN:public SANModel{
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
  Place* replicas_corrupted;
  short* replicas_corrupted_Mobius_Mark;
  Place* devices_available;
  short* devices_available_Mobius_Mark;
  Place* local_device_corrupted;
  short* local_device_corrupted_Mobius_Mark;
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
  Place* devices_available;
  short* devices_available_Mobius_Mark;
  Place* local_device_corrupted;
  short* local_device_corrupted_Mobius_Mark;
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
  Place* replicas_corrupted;
  short* replicas_corrupted_Mobius_Mark;
  Place* local_device_corrupted;
  short* local_device_corrupted_Mobius_Mark;
  Place* devices_available;
  short* devices_available_Mobius_Mark;
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
  Place* devices_available;
  Place* replicas_available;
  Place* flash_corrupted;
  Place* replicas_corrupted;
  Place* local_device_corrupted;

  // Create instances of all actvities
  seuActivity_case1 seu_case1;
  seuActivity_case2 seu_case2;
  sefiActivity sefi;
  power_cycleActivity power_cycle;
  //Create instances of all groups 
  EmptyGroup ImmediateGroup;
  PostselectGroup seuGroup;
  pretty_redundant_controller_flash_systemSAN();
  ~pretty_redundant_controller_flash_systemSAN();
  void CustomInitialization();

  void assignPlacesToActivitiesInst();
  void assignPlacesToActivitiesTimed();
}; // end pretty_redundant_controller_flash_systemSAN

#endif // pretty_redundant_controller_flash_systemSAN_H_
