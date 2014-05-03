
#ifndef basic_model_studyRangeSTUDY_H_
#define basic_model_studyRangeSTUDY_H_

#include "Reward/basic_reward/basic_rewardPVNodes.h"
#include "Reward/basic_reward/basic_rewardPVModel.h"
#include "Cpp/Study/BaseStudyClass.hpp"

extern float flash_size;
extern float ram_size;

class basic_model_studyRangeStudy : public BaseStudyClass {
public:

basic_model_studyRangeStudy();
~basic_model_studyRangeStudy();

private:

float *flash_sizeValues;
float *ram_sizeValues;

void SetValues_flash_size();
void SetValues_ram_size();

void PrintGlobalValues(int);
void *GetGVValue(char *TheGVName);
void OverrideGVValue(char *TheGVName, void *TheGVValue);
void SetGVs(int expnum);
PVModel *GetPVModel(bool expandTimeArrays);
};

#endif

