
#include "server/zone/objects/tangible/pharmaceutical/StimPack.h"
#include "server/zone/templates/tangible/StimPackTemplate.h"

bool StimPackImplementation::isPetStimPack() {
	return getObjectNameStringIdName().contains("pet_stimpack");
}

bool StimPackImplementation::isDroidRepairKit() {
	return getObjectNameStringIdName().contains("droid_damage_kit");
}
bool StimPackImplementation::isClassA() {
	return getMedicineClass() == StimPackTemplate::STIM_A;
}
bool StimPackImplementation::isClassB() {
	return getMedicineClass() == StimPackTemplate::STIM_B;
}
bool StimPackImplementation::isClassC() {
	return getMedicineClass() == StimPackTemplate::STIM_C;
}
bool StimPackImplementation::isClassD() {
	return getMedicineClass() == StimPackTemplate::STIM_D;
}
bool StimPackImplementation::isClassE() {
	return getMedicineClass() == StimPackTemplate::STIM_E;
}
