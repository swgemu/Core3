/*
 * DroidLabratory.cpp
 *
 *  Created on: Aug 20, 2014
 *      Author: swgemu
 */

#include "DroidLabratory.h"

namespace server {
namespace zone {
namespace objects {
namespace manufactureschematic {
class ManufactureSchematic;
}  // namespace manufactureschematic
}  // namespace objects
}  // namespace zone
}  // namespace server

DroidLabratory::DroidLabratory() {
	setLoggingName("DroidLabratory");
}

DroidLabratory::~DroidLabratory() {
}

int DroidLabratory::getCreationCount(ManufactureSchematic* manufactureSchematic) {
	// TODO check for the droid_count property and return the value
	return 1;
}
