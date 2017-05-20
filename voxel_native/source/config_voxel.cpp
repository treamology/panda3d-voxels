
#include "config_voxel.h"

/*

Include all your dynamically typed classes here, e.g.
#include "my_dynamic_class.h"

*/

#include "dconfig.h"

Configure(config_voxel);
NotifyCategoryDef(voxel , "");

ConfigureFn(config_voxel) {
  init_libvoxel();
}

void
init_libvoxel() {
  static bool initialized = false;
  if (initialized) {
    return;
  }
  initialized = true;

  // Init your dynamic types here, e.g.:
  // MyDynamicClass::init_type();

  return;
}

