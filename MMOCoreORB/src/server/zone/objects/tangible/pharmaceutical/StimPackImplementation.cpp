
#include "server/zone/objects/tangible/pharmaceutical/StimPack.h"

bool StimPackImplementation::isPetStimPack() {
	return getObjectNameStringIdName().contains("pet_stimpack");
}

bool StimPackImplementation::isDroidRepairKit() {
	return getObjectNameStringIdName().contains("droid_damage_kit");
}
bool StimPackImplementation::isClassA() {
	return getObjectNameStringIdName().contains("stimpack_sm_s1_a") ||
			getObjectNameStringIdName().contains("medpack_grenade_damage_a") ||
			getObjectNameStringIdName().contains("medpack_grenade_area_a") ||
			getObjectNameStringIdName().contains("medpack_damage_a");
}
