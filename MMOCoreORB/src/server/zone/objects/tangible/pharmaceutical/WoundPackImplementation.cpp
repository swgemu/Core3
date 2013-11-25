
#include "server/zone/objects/tangible/pharmaceutical/WoundPack.h"

bool WoundPackImplementation::isDroidReconstructionKit() {
	return getObjectNameStringIdName().contains("droid_wound_kit");
}
