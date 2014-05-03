
#include "Study/basic_model_study/basic_model_studyRangeStudy.h"

//******************************************************
//Global Variables
//******************************************************
float flash_size;
float ram_size;
float random_failure_rate;

//********************************************************
//basic_model_studyRangeStudy Constructor
//********************************************************
basic_model_studyRangeStudy::basic_model_studyRangeStudy() {

  // define arrays of global variable names and types
  NumGVs = 3;
  NumExps = 16;

  GVNames = new char*[NumGVs];
  GVTypes = new char*[NumGVs];
  GVNames[0]=strdup("flash_size");
  GVTypes[0]=strdup("float");
  GVNames[1]=strdup("ram_size");
  GVTypes[1]=strdup("float");
  GVNames[2]=strdup("random_failure_rate");
  GVTypes[2]=strdup("float");

  // create the arrays to store the values of each gv
  flash_sizeValues = new float[NumExps];
  ram_sizeValues = new float[NumExps];
  random_failure_rateValues = new float[NumExps];

  // call methods to assign values to each gv
  SetValues_flash_size();
  SetValues_ram_size();
  SetValues_random_failure_rate();
  SetDefaultMobiusRoot(MOBIUSROOT);
}


//******************************************************
//basic_model_studyRangeStudy Destructor
//******************************************************
basic_model_studyRangeStudy::~basic_model_studyRangeStudy() {
  delete [] flash_sizeValues;
  delete [] ram_sizeValues;
  delete [] random_failure_rateValues;
  delete ThePVModel;
}


//******************************************************
// set values for flash_size
//******************************************************
void basic_model_studyRangeStudy::SetValues_flash_size() {
  flash_sizeValues[0] = 64.0;
  flash_sizeValues[1] = 128.0;
  flash_sizeValues[2] = 256.0;
  flash_sizeValues[3] = 512.0;
  flash_sizeValues[4] = 64.0;
  flash_sizeValues[5] = 128.0;
  flash_sizeValues[6] = 256.0;
  flash_sizeValues[7] = 512.0;
  flash_sizeValues[8] = 64.0;
  flash_sizeValues[9] = 128.0;
  flash_sizeValues[10] = 256.0;
  flash_sizeValues[11] = 512.0;
  flash_sizeValues[12] = 64.0;
  flash_sizeValues[13] = 128.0;
  flash_sizeValues[14] = 256.0;
  flash_sizeValues[15] = 512.0;
}


//******************************************************
// set values for ram_size
//******************************************************
void basic_model_studyRangeStudy::SetValues_ram_size() {
  ram_sizeValues[0] = 64.0;
  ram_sizeValues[1] = 64.0;
  ram_sizeValues[2] = 64.0;
  ram_sizeValues[3] = 64.0;
  ram_sizeValues[4] = 128.0;
  ram_sizeValues[5] = 128.0;
  ram_sizeValues[6] = 128.0;
  ram_sizeValues[7] = 128.0;
  ram_sizeValues[8] = 256.0;
  ram_sizeValues[9] = 256.0;
  ram_sizeValues[10] = 256.0;
  ram_sizeValues[11] = 256.0;
  ram_sizeValues[12] = 512.0;
  ram_sizeValues[13] = 512.0;
  ram_sizeValues[14] = 512.0;
  ram_sizeValues[15] = 512.0;
}


//******************************************************
// set values for random_failure_rate
//******************************************************
void basic_model_studyRangeStudy::SetValues_random_failure_rate() {
  for (int n=0; n<NumExps; n++)
    random_failure_rateValues[n] = 0.005;
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
  cout << "ram_size\tfloat\t" << ram_size << endl;
  cout << "random_failure_rate\tfloat\t" << random_failure_rate << endl;
}


//******************************************************
//retrieve the value of a global variable
//******************************************************
void *basic_model_studyRangeStudy::GetGVValue(char *TheGVName) {
  if (strcmp("flash_size", TheGVName) == 0)
    return &flash_size;
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


