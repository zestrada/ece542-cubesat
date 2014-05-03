
#include "Study/basic_model_study/basic_model_studyRangeStudy.h"

//******************************************************
//Global Variables
//******************************************************
float flash_size;
float power_cycle_rate;
float ram_size;
float random_failure_rate;

//********************************************************
//basic_model_studyRangeStudy Constructor
//********************************************************
basic_model_studyRangeStudy::basic_model_studyRangeStudy() {

  // define arrays of global variable names and types
  NumGVs = 4;
  NumExps = 9;

  GVNames = new char*[NumGVs];
  GVTypes = new char*[NumGVs];
  GVNames[0]=strdup("flash_size");
  GVTypes[0]=strdup("float");
  GVNames[1]=strdup("power_cycle_rate");
  GVTypes[1]=strdup("float");
  GVNames[2]=strdup("ram_size");
  GVTypes[2]=strdup("float");
  GVNames[3]=strdup("random_failure_rate");
  GVTypes[3]=strdup("float");

  // create the arrays to store the values of each gv
  flash_sizeValues = new float[NumExps];
  power_cycle_rateValues = new float[NumExps];
  ram_sizeValues = new float[NumExps];
  random_failure_rateValues = new float[NumExps];

  // call methods to assign values to each gv
  SetValues_flash_size();
  SetValues_power_cycle_rate();
  SetValues_ram_size();
  SetValues_random_failure_rate();
  SetDefaultMobiusRoot(MOBIUSROOT);
}


//******************************************************
//basic_model_studyRangeStudy Destructor
//******************************************************
basic_model_studyRangeStudy::~basic_model_studyRangeStudy() {
  delete [] flash_sizeValues;
  delete [] power_cycle_rateValues;
  delete [] ram_sizeValues;
  delete [] random_failure_rateValues;
  delete ThePVModel;
}


//******************************************************
// set values for flash_size
//******************************************************
void basic_model_studyRangeStudy::SetValues_flash_size() {
  flash_sizeValues[0] = 64.0;
  flash_sizeValues[1] = 64.0;
  flash_sizeValues[2] = 64.0;
  flash_sizeValues[3] = 64.0;
  flash_sizeValues[4] = 64.0;
  flash_sizeValues[5] = 64.0;
  flash_sizeValues[6] = 64.0;
  flash_sizeValues[7] = 64.0;
  flash_sizeValues[8] = 64.0;
}


//******************************************************
// set values for power_cycle_rate
//******************************************************
void basic_model_studyRangeStudy::SetValues_power_cycle_rate() {
  power_cycle_rateValues[0] = 0.03125;
  power_cycle_rateValues[1] = 0.0625;
  power_cycle_rateValues[2] = 0.125;
  power_cycle_rateValues[3] = 0.25;
  power_cycle_rateValues[4] = 0.5;
  power_cycle_rateValues[5] = 1.0;
  power_cycle_rateValues[6] = 2.0;
  power_cycle_rateValues[7] = 4.0;
  power_cycle_rateValues[8] = 8.0;
}


//******************************************************
// set values for ram_size
//******************************************************
void basic_model_studyRangeStudy::SetValues_ram_size() {
  ram_sizeValues[0] = 128.0;
  ram_sizeValues[1] = 128.0;
  ram_sizeValues[2] = 128.0;
  ram_sizeValues[3] = 128.0;
  ram_sizeValues[4] = 128.0;
  ram_sizeValues[5] = 128.0;
  ram_sizeValues[6] = 128.0;
  ram_sizeValues[7] = 128.0;
  ram_sizeValues[8] = 128.0;
}


//******************************************************
// set values for random_failure_rate
//******************************************************
void basic_model_studyRangeStudy::SetValues_random_failure_rate() {
  random_failure_rateValues[0] = 0.005;
  random_failure_rateValues[1] = 0.005;
  random_failure_rateValues[2] = 0.005;
  random_failure_rateValues[3] = 0.005;
  random_failure_rateValues[4] = 0.005;
  random_failure_rateValues[5] = 0.005;
  random_failure_rateValues[6] = 0.005;
  random_failure_rateValues[7] = 0.005;
  random_failure_rateValues[8] = 0.005;
}



//******************************************************
//print values of gv (for debugging)
//******************************************************
void basic_model_studyRangeStudy::PrintGlobalValues(int expNum) {
  if (NumGVs == 0) {
    cout<<"There are no global variables."<<endl;
    return;
  }

  SetGVs(expNum);

  cout<<"The Global Variable values for experiment "<<
    GetExpName(expNum)<<" are:"<<endl;
  cout << "flash_size\tfloat\t" << flash_size << endl;
  cout << "power_cycle_rate\tfloat\t" << power_cycle_rate << endl;
  cout << "ram_size\tfloat\t" << ram_size << endl;
  cout << "random_failure_rate\tfloat\t" << random_failure_rate << endl;
}


//******************************************************
//retrieve the value of a global variable
//******************************************************
void *basic_model_studyRangeStudy::GetGVValue(char *TheGVName) {
  if (strcmp("flash_size", TheGVName) == 0)
    return &flash_size;
  else if (strcmp("power_cycle_rate", TheGVName) == 0)
    return &power_cycle_rate;
  else if (strcmp("ram_size", TheGVName) == 0)
    return &ram_size;
  else if (strcmp("random_failure_rate", TheGVName) == 0)
    return &random_failure_rate;
  else 
    cerr<<"!! basic_model_studyRangeStudy::GetGVValue: Global Variable "<<TheGVName<<" does not exist."<<endl;
  return NULL;
}


//******************************************************
//override the value of a global variable
//******************************************************
void basic_model_studyRangeStudy::OverrideGVValue(char *TheGVName,void *TheGVValue) {
  if (strcmp("flash_size", TheGVName) == 0)
    flash_size = *(float *)TheGVValue;
  else if (strcmp("power_cycle_rate", TheGVName) == 0)
    power_cycle_rate = *(float *)TheGVValue;
  else if (strcmp("ram_size", TheGVName) == 0)
    ram_size = *(float *)TheGVValue;
  else if (strcmp("random_failure_rate", TheGVName) == 0)
    random_failure_rate = *(float *)TheGVValue;
  else 
    cerr<<"!! basic_model_studyRangeStudy::OverrideGVValue: Global Variable "<<TheGVName<<" does not exist."<<endl;
}


//******************************************************
//set the value of all global variables to the given exp
//******************************************************
void basic_model_studyRangeStudy::SetGVs(int expNum) {
  flash_size = flash_sizeValues[expNum];
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
    GlobalStudyPtr = new basic_model_studyRangeStudy();
  return GlobalStudyPtr;
}

void DestructStudy() {
  delete GlobalStudyPtr;
  GlobalStudyPtr = NULL;
}
//******************************************************
//get and create the PVModel
//******************************************************
PVModel* basic_model_studyRangeStudy::GetPVModel(bool expandTimeArrays) {
  if (ThePVModel!=NULL)
    delete ThePVModel;
  // create the PV model
  ThePVModel=new basic_rewardPVModel(expandTimeArrays);
  return ThePVModel;
}


