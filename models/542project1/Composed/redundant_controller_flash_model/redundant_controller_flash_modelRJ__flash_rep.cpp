#include "Composed/redundant_controller_flash_model/redundant_controller_flash_modelRJ__flash_rep.h"
char * redundant_controller_flash_modelRJ__flash_rep__SharedNames[] = {"devices_available", "flash_corrupted"};

redundant_controller_flash_modelRJ__flash_rep::redundant_controller_flash_modelRJ__flash_rep():Rep("flash_rep", num_devices, 2, redundant_controller_flash_modelRJ__flash_rep__SharedNames)
{
  InstanceArray = new redundant_controller_flash_systemSAN * [NumModels];
  delete[] ModelArray;
  ModelArray = (BaseModelClass **) InstanceArray;
  for (counter = 0; counter < NumModels; counter++)
    InstanceArray[counter] = new redundant_controller_flash_systemSAN();

  SetupActions();
  if (NumModels == 0) return;

  if (AllChildrenEmpty())
    NumSharedStateVariables = 0;
  else {
    //**************** Initialize local variables ****************
    devices_available = new Place("devices_available");
    addSharedPtr(devices_available, "devices_available");
    devices_available->ShareWith(InstanceArray[0]->devices_available);

    flash_corrupted = new Place("flash_corrupted");
    addSharedPtr(flash_corrupted, "flash_corrupted");
    flash_corrupted->ShareWith(InstanceArray[0]->flash_corrupted);


    //Share state in submodels
    for (counter = 0; counter < NumModels; counter++) {
      addSharingInfo(InstanceArray[counter]->devices_available, devices_available);
    }
    for (counter = 0; counter < NumModels; counter++) {
      addSharingInfo(InstanceArray[counter]->flash_corrupted, flash_corrupted);
    }
    for (counter = 1; counter < NumModels; counter++) {
      InstanceArray[0]->devices_available->ShareWith(InstanceArray[counter]->devices_available);
      InstanceArray[0]->flash_corrupted->ShareWith(InstanceArray[counter]->flash_corrupted);
    }
  }
  Setup("redundant_controller_flash_system");
}

redundant_controller_flash_modelRJ__flash_rep::~redundant_controller_flash_modelRJ__flash_rep() {
  if (NumModels == 0) return;
  delete devices_available;
  delete flash_corrupted;
  for (int i = 0; i < NumModels; i++)
    delete InstanceArray[i];
}

