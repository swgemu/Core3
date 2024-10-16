//
// Created by g on 12/31/17.
//

#ifndef CORE3_COMPONENTSLOTS_H
#define CORE3_COMPONENTSLOTS_H

#include "engine/engine.h"

class Components {
public:
	const static int CHASSIS = -1;

	enum ShipComponents : uint32 {
		REACTOR,
		ENGINE,
		SHIELD0,
		SHIELD1,
		ARMOR0,
		ARMOR1,
		CAPACITOR,
		BOOSTER,
		DROID_INTERFACE,
		BRIDGE,
		HANGAR,
		TARGETING_STATION,
		WEAPON_START
	};

	enum ShipComponentsMax {
		FIGHTERSLOTMAX = 19,
		CAPITALSLOTMAX = 111
	};

	static String shipComponentSlotToString(int slot) {
		switch (slot) {
			case Components::CHASSIS: return "chassis";
			case Components::REACTOR: return "reactor";
			case Components::ENGINE: return "engine";
			case Components::SHIELD0: return "shield_0";
			case Components::SHIELD1: return "shield_1";
			case Components::ARMOR0: return "armor_0";
			case Components::ARMOR1: return "armor_1";
			case Components::CAPACITOR: return "capacitor";
			case Components::BOOSTER: return "booster";
			case Components::DROID_INTERFACE: return "droid_interface";
			case Components::BRIDGE: return "bridge";
			case Components::HANGAR: return "hangar";
			case Components::TARGETING_STATION: return "targeting_station";
			default: {
				if (slot >= WEAPON_START && slot <= CAPITALSLOTMAX) {
					return "weapon_" + String::valueOf(slot - Components::WEAPON_START);
				} else {
					return "";
				}
			}
		}
	}
};

#endif //CORE3_COMPONENTSLOTS_H
