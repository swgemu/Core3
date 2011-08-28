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
#include "server/zone/templates/datatables/DataTableIff.h"
#include "server/zone/templates/datatables/DataTableRow.h"
#include "server/zone/managers/templates/TemplateManager.h"

class CreatureState : public Singleton<CreatureState>, public Logger {
public:
	HashTable<String, uint64> states;

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
	static const uint64 IMMOBILIZED = 0x10000;
	static const uint64 FROZEN = 0x20000;
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
	static const uint64 PILOTINGSHIP = 0x20000000;
	static const uint64 SHIPOPERATIONS = 0x40000000;
	static const uint64 SHIPGUNNER = 0x80000000;
	static const uint64 SHIPINTERIOR = (uint64) 1 << 32;
	static const uint64 PILOTINGPOBSHIP = (uint64) 1 << 33;

	void loadStateData() {
		IffStream* iffStream = TemplateManager::instance()->openIffFile("datatables/include/state.iff");

		if (iffStream == NULL) {
			error("Could not load states.");
			return;
		}

		DataTableIff dtiff;
		dtiff.readObject(iffStream);

		delete iffStream;

		states.removeAll();

		for (int i = 0; i < dtiff.getTotalRows(); i++) {
			DataTableRow* row = dtiff.getRow(i);
			String name;
			int value;

			row->getValue(0, name);
			row->getValue(1, value);

			if (value >= 0)
				states.put(name.toLowerCase(), 1 << value);
			else
				states.put(name.toLowerCase(), 0x00);
		}
	}

	uint64 getState(String state) {
		state = state.toLowerCase();
		return states.get(state);
	}

	String getSpecialName(const uint64 state, bool initialCap = false) {
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

	String getName(const uint64 state, bool initialCap = false) {
		String name = "invalid";

		HashTableIterator<String, uint64> iter(&states);
		iter.resetIterator();

		while (iter.hasNext()) {
			uint64 testState;

			iter.getNextKeyAndValue(name, testState);

			if (testState == state)
				break;
		}

		if (initialCap)
			name[0] = toupper(name[0]);

		return name;
	}
};

#endif /* CREATURESTATE_H_ */
