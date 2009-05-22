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

#ifndef LAIROBJECTIMPLEMENTATION_H_
#define LAIROBJECTIMPLEMENTATION_H_

#include "engine/engine.h"

#include "LairObject.h"

#include "../../../packets.h"

#include "../../creature/Creature.h"
#include "../../../managers/creature/CreatureManager.h"
#include "../../../Zone.h"

class LairObjectImplementation : public LairObjectServant {

	SortedVector<Creature*> creatures;

	bool spawn1;
	bool spawn2;

	String stfName;
	uint32 creatureCRC;
	String creatureName;
	String creatureStfName;
	int spawnSize;
	int babiesPerMillion;
	int level;

	String templateDetailName;
	String templateDetail;

public:
	LairObjectImplementation(uint32 objCRC, uint64 oid);

	void addDefender(SceneObject* defender);
	void doDamage(int damage, SceneObject* attacker);
	void spawnCreatures(bool lockCreatureManager = true);
	void doDestroyed(SceneObject* attacker);

	void sendTo(Player* player, bool doClose = true);

	inline void setMaxCondition(int cond) {
		maxCondition = cond;
	}

	inline void setSStfName(String& stfname) {
		stfName = stfname;
	}

	inline void setCreatureCRC(uint32 crc) {
		creatureCRC = crc;
	}

	inline void setSpawnSize(int size) {
		spawnSize = size;
	}

	inline void setBabiesPerMillion(int babies) {
		babiesPerMillion = babies;
	}

	inline void setLevel(int lev) {
		level = lev;
	}

	void addCreature(Creature* creature) {
		creatures.add(creature);
	}

	void removeCreature(Creature* creature) {
		creatures.drop(creature);
	}

	inline String& getTemplateDetailName() {
		return templateDetailName;
	}

	inline String& getTemplateDetail() {
		return templateDetail;
	}

	Creature* getCreature() {
		if (creatures.size() > 0)
			return creatures.get(0);
		else
			return NULL;
	}

	int getNumberOfCreatures() {
		return creatures.size();
	}

	inline int getLevel() {
		return level;
	}

};

#endif /*LAIROBJECTIMPLEMENTATION_H_*/
