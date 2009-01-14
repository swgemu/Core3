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

#ifndef CLONINGFACILITYIMPLEMENTATION_H_
#define CLONINGFACILITYIMPLEMENTATION_H_

#include "engine/engine.h"

#include "../BuildingObject.h"

#include "CloneSpawnPoint.h"

#include "../../tangible/terminal/cloning/CloningTerminal.h"

class CloningFacilityImplementation : public CloningFacilityServant {
	Vector<CloningTerminal*> cloningTerminals;
	Vector<CloneSpawnPoint*> cloningSpawnPoints;

	bool registered;
	bool degenerating;

	uint32 faction;

public:
	CloningFacilityImplementation(uint64 oid, bool staticBuild) :
		CloningFacilityServant(oid, staticBuild, CLONING_FACILITY) {

		setRegistered(false);
		setDegenerating(true);
	}

	~CloningFacilityImplementation() {
	}

	void addSpawnPoint(CloneSpawnPoint* spawnPoint) {
		cloningSpawnPoints.add(spawnPoint);
	}

	void addCloningTerminal(CloningTerminal* cloningTerminal) {
		cloningTerminals.add(cloningTerminal);
	}

	/**
	 * Clones a player at this facility.
	 * \param player Player to be cloned at this facility.
	 * \param deathblown Was the death the result of a deathblow by a player?
	 * \return Was the cloning a success.
	 */
	bool clone(Player* player, bool deathblown = false) {
		if (isDegenerating()) {
			if (!hasCloningData(player)) {
				player->changeHAMWounds(100,100,100);
				player->changeShockWounds(100);
			}

			if (!deathblown)
				player->decayInventory();
		}

		player->clearStates();
		player->clearBuffs(true);
		player->resetArmorEncumbrance();


		//TODO: Make cloning facilities able to be neutral, imp, or rebel
		if (player->isOvert())
			player->setCovert();

		player->setPosture(CreaturePosture::UPRIGHT);

		CloneSpawnPoint* spawnPoint = getRandomSpawnPoint();

		if (spawnPoint != NULL) {
			if (spawnPoint->spawnAt(player))
				player->onCloneSuccessful();
			else
				player->onCloneFailure();
		}

		return true;
	}

	//Setters
	inline void setRegistered(bool reg) {
		registered = reg;
	}

	/**
	 * Sets where cloning wounds and battle fatigue should be incurred.
	 * \param deg Boolean value indicating whether or not to incur battle fatigue and cloning wounds.
	 */
	inline void setDegenerating(bool deg) {
		degenerating = deg;
	}

	inline void setFaction(uint32 fctn) {
		faction = fctn;
	}

	//Getters
	inline bool isRegistered() {
		return registered;
	}

	inline bool isDegenerating() {
		return degenerating;
	}

	inline uint32 getFaction() {
		return faction;
	}

	inline bool hasCloningData(Player* player) {
		return (player->getCloningFacility() == _this);
	}

	inline CloneSpawnPoint* getRandomSpawnPoint() {
		if (cloningSpawnPoints.size() > 0)
			return cloningSpawnPoints.get(System::random(cloningSpawnPoints.size() - 1));
		else
			return NULL;
	}

};

#endif /*CLONINGFACILITYIMPLEMENTATION_H_*/
