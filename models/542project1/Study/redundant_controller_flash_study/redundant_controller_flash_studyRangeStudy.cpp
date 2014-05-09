
#include "Study/redundant_controller_flash_study/redundant_controller_flash_studyRangeStudy.h"

//******************************************************
//Global Variables
//******************************************************
float flash_size;
short num_devices;
short num_replicas;
float power_cycle_rate;
float ram_size;
float random_failure_rate;

//********************************************************
//redundant_controller_flash_studyRangeStudy Constructor
//********************************************************
redundant_controller_flash_studyRangeStudy::redundant_controller_flash_studyRangeStudy() {

  // define arrays of global variable names and types
  NumGVs = 6;
  NumExps = 27;

  GVNames = new char*[NumGVs];
  GVTypes = new char*[NumGVs];
  GVNames[0]=strdup("flash_size");
  GVTypes[0]=strdup("float");
  GVNames[1]=strdup("num_devices");
  GVTypes[1]=strdup("short");
  GVNames[2]=strdup("num_replicas");
  GVTypes[2]=strdup("short");
  GVNames[3]=strdup("power_cycle_rate");
  GVTypes[3]=strdup("float");
  GVNames[4]=strdup("ram_size");
  GVTypes[4]=strdup("float");
  GVNames[5]=strdup("random_failure_rate");
  GVTypes[5]=strdup("float");

  // create the arrays to store the values of each gv
  flash_sizeValues = new float[NumExps];
  num_devicesValues = new short[NumExps];
  num_replicasValues = new short[NumExps];
  power_cycle_rateValues = new float[NumExps];
  ram_sizeValues = new float[NumExps];
  random_failure_rateValues = new float[NumExps];

  // call methods to assign values to each gv
  SetValues_flash_size();
  SetValues_num_devices();
  SetValues_num_replicas();
  SetValues_power_cycle_rate();
  SetValues_ram_size();
  SetValues_random_failure_rate();
  SetDefaultMobiusRoot(MOBIUSROOT);
}


//******************************************************
//redundant_controller_flash_studyRangeStudy Destructor
//******************************************************
redundant_controller_flash_studyRangeStudy::~redundant_controller_flash_studyRangeStudy() {
  delete [] flash_sizeValues;
  delete [] num_devicesValues;
  delete [] num_replicasValues;
  delete [] power_cycle_rateValues;
  delete [] ram_sizeValues;
  delete [] random_failure_rateValues;
  delete ThePVModel;
}


//******************************************************
// set values for flash_size
//******************************************************
void redundant_controller_flash_studyRangeStudy::SetValues_flash_size() {
  for (int n=0; n<NumExps; n++)
    flash_sizeValues[n] = 17.0;
}


//******************************************************
// set values for num_devices
//******************************************************
void redundant_controller_flash_studyRangeStudy::SetValues_num_devices() {
  num_devicesValues[0] = 1;
  num_devicesValues[1] = 2;
  num_devicesValues[2] = 3;
  num_devicesValues[3] = 1;
  num_devicesValues[4] = 2;
  num_devicesValues[5] = 3;
  num_devicesValues[6] = 1;
  num_devicesValues[7] = 2;
  num_devicesValues[8] = 3;
  num_devicesValues[9] = 1;
  num_devicesValues[10] = 2;
  num_devicesValues[11] = 3;
  num_devicesValues[12] = 1;
  num_devicesValues[13] = 2;
  num_devicesValues[14] = 3;
  num_devicesValues[15] = 1;
  num_devicesValues[16] = 2;
  num_devicesValues[17] = 3;
  num_devicesValues[18] = 1;
  num_devicesValues[19] = 2;
  num_devicesValues[20] = 3;
  num_devicesValues[21] = 1;
  num_devicesValues[22] = 2;
  num_devicesValues[23] = 3;
  num_devicesValues[24] = 1;
  num_devicesValues[25] = 2;
  num_devicesValues[26] = 3;
}


//******************************************************
// set values for num_replicas
//******************************************************
void redundant_controller_flash_studyRangeStudy::SetValues_num_replicas() {
  num_replicasValues[0] = 1;
  num_replicasValues[1] = 1;
  num_replicasValues[2] = 1;
  num_replicasValues[3] = 2;
  num_replicasValues[4] = 2;
  num_replicasValues[5] = 2;
  num_replicasValues[6] = 3;
  num_replicasValues[7] = 3;
  num_replicasValues[8] = 3;
  num_replicasValues[9] = 1;
  num_replicasValues[10] = 1;
  num_replicasValues[11] = 1;
  num_replicasValues[12] = 2;
  num_replicasValues[13] = 2;
  num_replicasValues[14] = 2;
  num_replicasValues[15] = 3;
  num_replicasValues[16] = 3;
  num_replicasValues[17] = 3;
  num_replicasValues[18] = 1;
  num_replicasValues[19] = 1;
  num_replicasValues[20] = 1;
  num_replicasValues[21] = 2;
  num_replicasValues[22] = 2;
  num_replicasValues[23] = 2;
  num_replicasValues[24] = 3;
  num_replicasValues[25] = 3;
  num_replicasValues[26] = 3;
}


//******************************************************
// set values for power_cycle_rate
//******************************************************
void redundant_controller_flash_studyRangeStudy::SetValues_power_cycle_rate() {
  power_cycle_rateValues[0] = 0.25;
  power_cycle_rateValues[1] = 0.25;
  power_cycle_rateValues[2] = 0.25;
  power_cycle_rateValues[3] = 0.25;
  power_cycle_rateValues[4] = 0.25;
  power_cycle_rateValues[5] = 0.25;
  power_cycle_rateValues[6] = 0.25;
  power_cycle_rateValues[7] = 0.25;
  power_cycle_rateValues[8] = 0.25;
  power_cycle_rateValues[9] = 0.5;
  power_cycle_rateValues[10] = 0.5;
  power_cycle_rateValues[11] = 0.5;
  power_cycle_rateValues[12] = 0.5;
  power_cycle_rateValues[13] = 0.5;
  power_cycle_rateValues[14] = 0.5;
  power_cycle_rateValues[15] = 0.5;
  power_cycle_rateValues[16] = 0.5;
  power_cycle_rateValues[17] = 0.5;
  power_cycle_rateValues[18] = 1.0;
  power_cycle_rateValues[19] = 1.0;
  power_cycle_rateValues[20] = 1.0;
  power_cycle_rateValues[21] = 1.0;
  power_cycle_rateValues[22] = 1.0;
  power_cycle_rateValues[23] = 1.0;
  power_cycle_rateValues[24] = 1.0;
  power_cycle_rateValues[25] = 1.0;
  power_cycle_rateValues[26] = 1.0;
}


//******************************************************
// set values for ram_size
//******************************************************
void redundant_controller_flash_studyRangeStudy::SetValues_ram_size() {
  for (int n=0; n<NumExps; n++)
    ram_sizeValues[n] = 128.0;
}


//******************************************************
// set values for random_failure_rate
//******************************************************
void redundant_controller_flash_studyRangeStudy::SetValues_random_failure_rate() {
  for (int n=0; n<NumExps; n++)
    random_failure_rateValues[n] = 0.005;
}



//******************************************************
//print values of gv (for debugging)
//******************************************************
void redundant_controller_flash_studyRangeStudy::PrintGlobalValues(int expNum) {
  if (NumGVs == 0) {
    cout<<"There are no global variables."<<endl;
    return;
  }

  SetGVs(expNum);

  cout<<"The Global Variable values for experiment "<<
    GetExpName(expNum)<<" are:"<<endl;
  cout << "flash_size\tfloat\t" << flash_size << endl;
  cout << "num_devices\tshort\t" << num_devices << endl;
  cout << "num_replicas\tshort\t" << num_replicas << endl;
  cout << "power_cycle_rate\tfloat\t" << power_cycle_rate << endl;
  cout << "ram_size\tfloat\t" << ram_size << endl;
  cout << "random_failure_rate\tfloat\t" << random_failure_rate << endl;
}


//******************************************************
//retrieve the value of a global variable
//******************************************************
void *redundant_controller_flash_studyRangeStudy::GetGVValue(char *TheGVName) {
  if (strcmp("flash_size", TheGVName) == 0)
    return &flash_size;
  else if (strcmp("num_devices", TheGVName) == 0)
    return &num_devices;
  else if (strcmp("num_replicas", TheGVName) == 0)
    return &num_replicas;
  else if (strcmp("power_cycle_rate", TheGVName) == 0)
    return &power_cycle_rate;
  else if (strcmp("ram_size", TheGVName) == 0)
    return &ram_size;
  else if (strcmp("random_failure_rate", TheGVName) == 0)
    return &random_failure_rate;
  else 
    cerr<<"!! redundant_controller_flash_studyRangeStudy::GetGVValue: Global Variable "<<TheGVName<<" does not exist."<<endl;
  return NULL;
}


//******************************************************
//override the value of a global variable
//******************************************************
void redundant_controller_flash_studyRangeStudy::OverrideGVValue(char *TheGVName,void *TheGVValue) {
  if (strcmp("flash_size", TheGVName) == 0)
    flash_size = *(float *)TheGVValue;
  else if (strcmp("num_devices", TheGVName) == 0)
    num_devices = *(short *)TheGVValue;
  else if (strcmp("num_replicas", TheGVName) == 0)
    num_replicas = *(short *)TheGVValue;
  else if (strcmp("power_cycle_rate", TheGVName) == 0)
    power_cycle_rate = *(float *)TheGVValue;
  else if (strcmp("ram_size", TheGVName) == 0)
    ram_size = *(float *)TheGVValue;
  else if (strcmp("random_failure_rate", TheGVName) == 0)
    random_failure_rate = *(float *)TheGVValue;
  else 
    cerr<<"!! redundant_controller_flash_studyRangeStudy::OverrideGVValue: Global Variable "<<TheGVName<<" does not exist."<<endl;
}


//******************************************************
//set the value of all global variables to the given exp
//******************************************************
void redundant_controller_flash_studyRangeStudy::SetGVs(int expNum) {
  flash_size = flash_sizeValues[expNum];
  num_devices = num_devicesValues[expNum];
  num_replicas = num_replicasValues[expNum];
  power_cycle_rate = power_cycle_rateValues[expNum];
  ram_size = ram_sizeValues[expNum];
  random_failure_rate = random_failure_rateValues[expNum];
}


//******************************************************
//static class method called by solvers to create study 
//(and thus create all of the model)
//******************************************************
BaseStudyClass* GlobalStudyPtr = NULL;
BaseStudyClass * GenerateStudy() {
  if (GlobalStudyPtr == NULL)
    GlobalStudyPtr = new redundant_controller_flash_studyRangeStudy();
  return GlobalStudyPtr;
}

void DestructStudy() {
  delete GlobalStudyPtr;
  GlobalStudyPtr = NULL;
}
//******************************************************
//get and create the PVModel
//******************************************************
PVModel* redundant_controller_flash_studyRangeStudy::GetPVModel(bool expandTimeArrays) {
  if (ThePVModel!=NULL)
    delete ThePVModel;
  // create the PV model
  ThePVModel=new redundant_controller_flash_rewardPVModel(expandTimeArrays);
  return ThePVModel;
}


