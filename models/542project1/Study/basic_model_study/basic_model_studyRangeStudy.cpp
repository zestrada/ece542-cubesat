
#include "Study/basic_model_study/basic_model_studyRangeStudy.h"

//******************************************************
//Global Variables
//******************************************************
float flash_size;
float ram_size;

//********************************************************
//basic_model_studyRangeStudy Constructor
//********************************************************
basic_model_studyRangeStudy::basic_model_studyRangeStudy() {

  // define arrays of global variable names and types
  NumGVs = 2;
  NumExps = 25;

  GVNames = new char*[NumGVs];
  GVTypes = new char*[NumGVs];
  GVNames[0]=strdup("flash_size");
  GVTypes[0]=strdup("float");
  GVNames[1]=strdup("ram_size");
  GVTypes[1]=strdup("float");

  // create the arrays to store the values of each gv
  flash_sizeValues = new float[NumExps];
  ram_sizeValues = new float[NumExps];

  // call methods to assign values to each gv
  SetValues_flash_size();
  SetValues_ram_size();
  SetDefaultMobiusRoot(MOBIUSROOT);
}


//******************************************************
//basic_model_studyRangeStudy Destructor
//******************************************************
basic_model_studyRangeStudy::~basic_model_studyRangeStudy() {
  delete [] flash_sizeValues;
  delete [] ram_sizeValues;
  delete ThePVModel;
}


//******************************************************
// set values for flash_size
//******************************************************
void basic_model_studyRangeStudy::SetValues_flash_size() {
  flash_sizeValues[0] = 32.0;
  flash_sizeValues[1] = 64.0;
  flash_sizeValues[2] = 128.0;
  flash_sizeValues[3] = 256.0;
  flash_sizeValues[4] = 512.0;
  flash_sizeValues[5] = 32.0;
  flash_sizeValues[6] = 64.0;
  flash_sizeValues[7] = 128.0;
  flash_sizeValues[8] = 256.0;
  flash_sizeValues[9] = 512.0;
  flash_sizeValues[10] = 32.0;
  flash_sizeValues[11] = 64.0;
  flash_sizeValues[12] = 128.0;
  flash_sizeValues[13] = 256.0;
  flash_sizeValues[14] = 512.0;
  flash_sizeValues[15] = 32.0;
  flash_sizeValues[16] = 64.0;
  flash_sizeValues[17] = 128.0;
  flash_sizeValues[18] = 256.0;
  flash_sizeValues[19] = 512.0;
  flash_sizeValues[20] = 32.0;
  flash_sizeValues[21] = 64.0;
  flash_sizeValues[22] = 128.0;
  flash_sizeValues[23] = 256.0;
  flash_sizeValues[24] = 512.0;
}


//******************************************************
// set values for ram_size
//******************************************************
void basic_model_studyRangeStudy::SetValues_ram_size() {
  ram_sizeValues[0] = 32.0;
  ram_sizeValues[1] = 32.0;
  ram_sizeValues[2] = 32.0;
  ram_sizeValues[3] = 32.0;
  ram_sizeValues[4] = 32.0;
  ram_sizeValues[5] = 64.0;
  ram_sizeValues[6] = 64.0;
  ram_sizeValues[7] = 64.0;
  ram_sizeValues[8] = 64.0;
  ram_sizeValues[9] = 64.0;
  ram_sizeValues[10] = 128.0;
  ram_sizeValues[11] = 128.0;
  ram_sizeValues[12] = 128.0;
  ram_sizeValues[13] = 128.0;
  ram_sizeValues[14] = 128.0;
  ram_sizeValues[15] = 256.0;
  ram_sizeValues[16] = 256.0;
  ram_sizeValues[17] = 256.0;
  ram_sizeValues[18] = 256.0;
  ram_sizeValues[19] = 256.0;
  ram_sizeValues[20] = 512.0;
  ram_sizeValues[21] = 512.0;
  ram_sizeValues[22] = 512.0;
  ram_sizeValues[23] = 512.0;
  ram_sizeValues[24] = 512.0;
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
}


//******************************************************
//retrieve the value of a global variable
//******************************************************
void *basic_model_studyRangeStudy::GetGVValue(char *TheGVName) {
  if (strcmp("flash_size", TheGVName) == 0)
    return &flash_size;
  else if (strcmp("ram_size", TheGVName) == 0)
    return &ram_size;
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
  else 
    cerr<<"!! basic_model_studyRangeStudy::OverrideGVValue: Global Variable "<<TheGVName<<" does not exist."<<endl;
}


//******************************************************
//set the value of all global variables to the given exp
//******************************************************
void basic_model_studyRangeStudy::SetGVs(int expNum) {
  flash_size = flash_sizeValues[expNum];
  ram_size = ram_sizeValues[expNum];
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


