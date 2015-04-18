/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef CREATURESTATE_H_
#define CREATURESTATE_H_

#include "engine/engine.h"
#include "server/zone/templates/datatables/DataTableIff.h"
#include "server/zone/templates/datatables/DataTableRow.h"
#include "server/zone/managers/templates/TemplateManager.h"

class CreatureState : public Singleton<CreatureState>, public Logger, public Object {
public:
	HashTable<String, uint64> states;

	enum {
		INVALID                  = 0x00,
		COVER                    = 0x01,
		COMBAT                   = 0x02,
		PEACE                    = 0x04,
		AIMING                   = 0x08,
		ALERT                    = 0x10,
		BERSERK                  = 0x20,
		FEIGNDEATH               = 0x40,
		COMBATATTITUDEEVASIVE    = 0x80,
		COMBATATTITUDENORMAL     = 0x100,
		COMBATATTITUDEAGGRESSIVE = 0x200,
		TUMBLING                 = 0x400,
		RALLIED                  = 0x800,
		STUNNED                  = 0x1000,
		BLINDED                  = 0x2000,
		DIZZY                    = 0x4000,
		INTIMIDATED              = 0x8000,
		IMMOBILIZED              = 0x10000,
		FROZEN                   = 0x20000,
		SWIMMING                 = 0x40000,
		SITTINGONCHAIR           = 0x80000,
		CRAFTING                 = 0x100000,
		GLOWINGJEDI              = 0x200000,
		MASKSCENT                = 0x400000,
		POISONED                 = 0x800000,
		BLEEDING                 = 0x1000000,
		DISEASED                 = 0x2000000,
		ONFIRE                   = 0x4000000,
		RIDINGMOUNT              = 0x8000000, // Is riding a vehicle or creature mount
		MOUNTEDCREATURE          = 0x10000000, // Is a vehicle or creature mount that has a rider
		PILOTINGSHIP             = 0x20000000,
		SHIPOPERATIONS           = 0x40000000,
		SHIPGUNNER               = 0x80000000,
		SHIPINTERIOR             = (uint64) 1 << 32,
		PILOTINGPOBSHIP          = (uint64) 1 << 33
	};


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

	uint64 getState(const String& state) {
		return states.get(state.toLowerCase());
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
