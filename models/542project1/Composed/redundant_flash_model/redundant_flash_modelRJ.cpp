#include "Composed/redundant_flash_model/redundant_flash_modelRJ.h"
char * redundant_flash_modelRJ__SharedNames[] = {"flash_corrupted"};

redundant_flash_modelRJ::redundant_flash_modelRJ():Join("Join", 2, 1,redundant_flash_modelRJ__SharedNames) {
  ram_system = new ram_systemSAN();
  ModelArray[0] = (BaseModelClass*) ram_system;
  ModelArray[0]->DefineName("ram_system");
  redundant_flash_system = new redundant_flash_systemSAN();
  ModelArray[1] = (BaseModelClass*) redundant_flash_system;
  ModelArray[1]->DefineName("redundant_flash_system");

  SetupActions();
  if (AllChildrenEmpty())
    NumSharedStateVariables = 0;
  else {
    //**************  State sharing info  **************
    //Shared variable 0
    flash_corrupted = new Place("flash_corrupted");
    addSharedPtr(flash_corrupted, "flash_corrupted" );
    if (ram_system->NumStateVariables > 0) {
      flash_corrupted->ShareWith(ram_system->flash_corrupted);
      addSharingInfo(ram_system->flash_corrupted, flash_corrupted, ram_system);
    }
    if (redundant_flash_system->NumStateVariables > 0) {
      flash_corrupted->ShareWith(redundant_flash_system->flash_corrupted);
      addSharingInfo(redundant_flash_system->flash_corrupted, flash_corrupted, redundant_flash_system);
    }

  }

  Setup();
}

redundant_flash_modelRJ::~redundant_flash_modelRJ() {
  if (!AllChildrenEmpty()) {
    delete flash_corrupted;
  }
  delete ram_system;
  delete redundant_flash_system;
}
