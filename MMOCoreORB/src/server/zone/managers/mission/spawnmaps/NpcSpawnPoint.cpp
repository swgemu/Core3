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

#include "NpcSpawnPoint.h"
#include "server/zone/managers/mission/spawnmaps/events/DespawnMissionNpcTask.h"
#include "server/zone/managers/name/NameManager.h"

NpcSpawnPoint::NpcSpawnPoint() {
	spawnType = 0;
	despawnMissionNpcTask = NULL;
}

NpcSpawnPoint::NpcSpawnPoint(CreatureObject* player, const String& spawnTypes) {
	//Parse spawn types.
	String st = spawnTypes.toLowerCase();
	spawnType = 0;
	if (st.contains("neutral")) {
		spawnType |= NEUTRALSPAWN;
	}
	if (st.contains("imperial")) {
		spawnType |= IMPERIALSPAWN;
	}
	if (st.contains("rebel")) {
		spawnType |= REBELSPAWN;
	}
	if (st.contains("bhtarget")) {
		spawnType |= BHTARGETSPAWN;
	}
	if (st.contains("nospawn")) {
		//No spawn overrides all other spawn types.
		spawnType = NOSPAWN;
	}
	position.setX(player->getPosition().getX());
	position.setY(player->getPosition().getY());
	direction.setHeadingDirection(player->getDirection()->getRadians());
	inUseByNumberOfMissions = 0;
	despawnMissionNpcTask = NULL;
}

void NpcSpawnPoint::readObject(LuaObject* luaObject) {
	float x = luaObject->getFloatAt(1);
	float y = luaObject->getFloatAt(2);
	float radians = luaObject->getFloatAt(3);
	spawnType = luaObject->getIntAt(4);
	position.setX(x);
	position.setY(y);
	position.setZ(0);
	direction.setHeadingDirection(radians);
	inUseByNumberOfMissions = 0;
	despawnMissionNpcTask = NULL;
}

bool NpcSpawnPoint::parseFromBinaryStream(ObjectInputStream* stream) {
	spawnType = stream->readInt();
	inUseByNumberOfMissions = stream->readInt();
	bool result = position.parseFromBinaryStream(stream);
	result &= direction.parseFromBinaryStream(stream);
	return result & npc.parseFromBinaryStream(stream);
}

bool NpcSpawnPoint::toBinaryStream(ObjectOutputStream* stream) {
	stream->writeInt(spawnType);
	stream->writeInt(inUseByNumberOfMissions);
	bool result = position.toBinaryStream(stream);
	result &= direction.toBinaryStream(stream);
	return result & npc.toBinaryStream(stream);
}

void NpcSpawnPoint::spawnNpc(TerrainManager* terrainManager, CreatureManager* creatureManager) {
	inUseByNumberOfMissions++;

	if (inUseByNumberOfMissions == 1) {
		if (despawnMissionNpcTask != NULL && despawnMissionNpcTask->isScheduled()) {
			despawnMissionNpcTask->cancel();
		} else {
			//Spawn the NPC.
			String deliverNpc = "deliver_npc";
			float z = terrainManager->getHeight(position.getX(), position.getY());
			npc = cast<AiAgent*>(creatureManager->spawnCreature(deliverNpc.hashCode(), 0, position.getX(), z, position.getY(), 0));
			npc->updateDirection(direction.getW(), direction.getX(), direction.getY(), direction.getZ());
			//Set the name of the NPC.
			NameManager* nm = npc->getZoneProcessServer()->getNameManager();
			npc->setCustomObjectName(nm->makeCreatureName(), true);
		}
	}
}

void NpcSpawnPoint::despawnNpc() {
	inUseByNumberOfMissions--;

	if (inUseByNumberOfMissions == 0) {
		if (despawnMissionNpcTask == NULL) {
			despawnMissionNpcTask = new DespawnMissionNpcTask(npc, this);
		}

		if (despawnMissionNpcTask->isScheduled()) {
			return;
		} else {
			//Despawn after 1 minute.
			despawnMissionNpcTask->schedule(60 * 1000);
		}
	}
}
