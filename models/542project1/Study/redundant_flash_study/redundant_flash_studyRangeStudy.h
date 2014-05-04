
#ifndef redundant_flash_studyRangeSTUDY_H_
#define redundant_flash_studyRangeSTUDY_H_

#include "Reward/redundant_flash_reward/redundant_flash_rewardPVNodes.h"
#include "Reward/redundant_flash_reward/redundant_flash_rewardPVModel.h"
#include "Cpp/Study/BaseStudyClass.hpp"

extern float flash_size;
extern short num_replicas;
extern float power_cycle_rate;
extern float ram_size;
extern float random_failure_rate;

class redundant_flash_studyRangeStudy : public BaseStudyClass {
public:

redundant_flash_studyRangeStudy();
~redundant_flash_studyRangeStudy();

private:

float *flash_sizeValues;
short *num_replicasValues;
float *power_cycle_rateValues;
float *ram_sizeValues;
float *random_failure_rateValues;

void SetValues_flash_size();
void SetValues_num_replicas();
void SetValues_power_cycle_rate();
void SetValues_ram_size();
void SetValues_random_failure_rate();

void PrintGlobalValues(int);
void *GetGVValue(char *TheGVName);
void OverrideGVValue(char *TheGVName, void *TheGVValue);
void SetGVs(int expnum);
PVModel *GetPVModel(bool expandTimeArrays);
};

#endif

