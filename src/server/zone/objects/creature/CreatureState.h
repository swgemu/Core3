/*
Copyright (C) 2007 <SWGEmu>

This File is part of Core3.

This program is free software; you can redistribute
it and/or modify it under the terms of the GNU Lesser
General Public License as published by the Free Software
Foundation; either version 2 of the License,
or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
See the GNU Lesser General Public License for
more details.

You should have received a copy of the GNU Lesser General
Public License along with this program; if not, write to
the Free Software Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA

Linking Engine3 statically or dynamically with other modules
is making a combined work based on Engine3.
Thus, the terms and conditions of the GNU Lesser General Public License
cover the whole combination.

In addition, as a special exception, the copyright holders of Engine3
give you permission to combine Engine3 program with free software
programs or libraries that are released under the GNU LGPL and with
code included in the standard release of Core3 under the GNU LGPL
license (or modified versions of such code, with unchanged license).
You may copy and distribute such a system following the terms of the
GNU LGPL for Engine3 and the licenses of the other code concerned,
provided that you include the source code of that other code when
and as the GNU LGPL requires distribution of source code.

Note that people who make modified versions of Engine3 are not obligated
to grant this special exception for their modified versions;
it is their choice whether to do so. The GNU Lesser General Public License
gives permission to release a modified version without this exception;
this exception also makes it possible to release a modified version
which carries forward this exception.
*/

#ifndef CREATURESTATE_H_
#define CREATURESTATE_H_

#include "engine/engine.h"

class CreatureState {
public:
	static const uint64 INVALID = 0x00;
	static const uint64 COVER = 0x01;
	static const uint64 COMBAT = 0x02;
	static const uint64 PEACE = 0x04;
	static const uint64 AIMING = 0x08;
	static const uint64 ALERT = 0x10;
	static const uint64 BERSERK = 0x20;
	static const uint64 FEIGNDEATH = 0x40;
	static const uint64 COMBATATTITUDEEVASIVE = 0x80;
	static const uint64 COMBATATTITUDENORMAL = 0x100;
	static const uint64 COMBATATTITUDEAGGRESSIVE = 0x200;
	static const uint64 TUMBLING = 0x400;
	static const uint64 RALLIED = 0x800;
	static const uint64 STUNNED = 0x1000;
	static const uint64 BLINDED = 0x2000;
	static const uint64 DIZZY = 0x4000;
	static const uint64 INTIMIDATED = 0x8000;
	static const uint64 SNARED = 0x10000;
	static const uint64 ROOTED = 0x20000;
	static const uint64 SWIMMING = 0x40000;
	static const uint64 SITTINGONCHAIR = 0x80000;
	static const uint64 CRAFTING = 0x100000;
	static const uint64 GLOWINGJEDI = 0x200000;
	static const uint64 MASKSCENT = 0x400000;
	static const uint64 POISONED = 0x800000;
	static const uint64 BLEEDING = 0x1000000;
	static const uint64 DISEASED = 0x2000000;
	static const uint64 ONFIRE = 0x4000000;
	static const uint64 RIDINGMOUNT = 0x8000000;
	static const uint64 MOUNTEDCREATURE = 0x10000000;
	static const uint64 PILOTSHIP = 0x20000000;
	static const uint64 SHIPOPERATIONS = 0x40000000;
	static const uint64 SHIPGUNNER = 0x80000000;
	//static const uint64 SHIPINTERIOR = 0x100000000;
	//static const uint64 PILOTINGPOBSHIP = 0x200000000;

	static uint64 getState(String state) {
		state = state.toLowerCase();

		if (state == "cover")
			return COVER;
		else if (state == "combat")
			return COMBAT;
		else if (state == "peace")
			return PEACE;
		else if (state == "aiming")
			return AIMING;
		else if (state == "alert")
			return ALERT;
		else if (state == "berserk")
			return BERSERK;
		else if (state == "feigndeath")
			return FEIGNDEATH;
		else if (state == "combatattitudeevasive")
			return COMBATATTITUDEEVASIVE;
		else if (state == "combatattitudenormal")
			return COMBATATTITUDENORMAL;
		else if (state == "combatattitudeaggressive")
			return COMBATATTITUDEAGGRESSIVE;
		else if (state == "tumbling")
			return TUMBLING;
		else if (state == "rallied")
			return RALLIED;
		else if (state == "stunned" || state == "stun")
			return STUNNED;
		else if (state == "blinded" || state == "blind")
			return BLINDED;
		else if (state == "dizzy")
			return DIZZY;
		else if (state == "intimidated" || state == "intimidation")
			return INTIMIDATED;
		else if (state == "snared" || state == "snare")
			return SNARED;
		else if (state == "rooted" || state == "root")
			return ROOTED;
		else if (state == "swimming")
			return SWIMMING;
		else if (state == "sittingonchair")
			return SITTINGONCHAIR;
		else if (state == "crafting")
			return CRAFTING;
		else if (state == "glowingjedi")
			return GLOWINGJEDI;
		else if (state == "maskscent")
			return MASKSCENT;
		else if (state == "poisoned" || state == "poison")
			return POISONED;
		else if (state == "bleeding" || state == "bleed")
			return BLEEDING;
		else if (state == "diseased" || state == "disease")
			return DISEASED;
		else if (state == "onfire")
			return ONFIRE;
		else if (state == "ridingmount")
			return RIDINGMOUNT;
		else if (state == "mountedcreature")
			return MOUNTEDCREATURE;
		else if (state == "pilotship")
			return PILOTSHIP;
		else if (state == "shipoperations")
			return SHIPOPERATIONS;
		else if (state == "shipgunner")
			return SHIPGUNNER;
		else
			return INVALID;
	}

	static String getSpecialName(const uint64 state, bool initialCap = false) {
		//This method is used for String building to match up with the tre's
		String name = "";

		switch (state) {
		case POISONED:
			name = "poison";
			break;
		case DISEASED:
			name = "disease";
			break;
		case ONFIRE:
			name = "fire";
			break;
		}

		if (initialCap)
			name[0] = toupper(name[0]);

		return name;
	}

	static String getName(const uint64 state, bool initialCap = false) {
		String name = "";

		switch (state) {
		case COVER:
			name = "cover";
			break;
		case COMBAT:
			name = "combat";
			break;
		case PEACE:
			name = "peace";
			break;
		case AIMING:
			name = "aiming";
			break;
		case ALERT:
			name = "alert";
			break;
		case BERSERK:
			name = "berserk";
			break;
		case FEIGNDEATH:
			name = "feigndeath";
			break;
		case COMBATATTITUDEEVASIVE:
			name = "combatattitudeevasive";
			break;
		case COMBATATTITUDENORMAL:
			name = "combatattitudenormal";
			break;
		case COMBATATTITUDEAGGRESSIVE:
			name = "combatattitudeaggressive";
			break;
		case TUMBLING:
			name = "tumbling";
			break;
		case RALLIED:
			name = "rallied";
			break;
		case STUNNED:
			name = "stunned";
			break;
		case BLINDED:
			name = "blinded";
			break;
		case DIZZY:
			name = "dizzy";
			break;
		case INTIMIDATED:
			name = "intimidated";
			break;
		case SNARED:
			name = "snared";
			break;
		case ROOTED:
			name = "rooted";
			break;
		case SWIMMING:
			name = "swimming";
			break;
		case SITTINGONCHAIR:
			name = "sittingonchair";
			break;
		case CRAFTING:
			name = "crafting";
			break;
		case GLOWINGJEDI:
			name = "glowingjedi";
			break;
		case MASKSCENT:
			name = "maskscent";
			break;
		case POISONED:
			name = "poisoned";
			break;
		case BLEEDING:
			name = "bleeding";
			break;
		case DISEASED:
			name = "diseased";
			break;
		case ONFIRE:
			name = "onfire";
			break;
		case RIDINGMOUNT:
			name = "ridingmount";
			break;
		case MOUNTEDCREATURE:
			name = "mountedcreature";
			break;
		case PILOTSHIP:
			name = "pilotship";
			break;
		case SHIPOPERATIONS:
			name = "shipoperations";
			break;
		case SHIPGUNNER:
			name = "shipgunner";
			break;
		case INVALID:
		default:
			name = "invalid";
			break;
		}

		if (initialCap)
			name[0] = toupper(name[0]);

		return name;
	}
};

#endif /* CREATURESTATE_H_ */
