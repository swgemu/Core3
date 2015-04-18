/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#include "NpcSpawnPoint.h"
#include "server/zone/managers/mission/spawnmaps/events/DespawnMissionNpcTask.h"
#include "server/zone/managers/name/NameManager.h"

NpcSpawnPoint::NpcSpawnPoint() {
	inUseByNumberOfMissions = 0;
	spawnType = 0;
	despawnMissionNpcTask = NULL;
	npcSpawned = false;
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
	npcSpawned = false;
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
	npcSpawned = false;
}

bool NpcSpawnPoint::parseFromBinaryStream(ObjectInputStream* stream) {
	spawnType = stream->readInt();
	inUseByNumberOfMissions = stream->readInt();
	npcSpawned = stream->readBoolean();
	bool result = position.parseFromBinaryStream(stream);
	result &= direction.parseFromBinaryStream(stream);
	return result & npc.parseFromBinaryStream(stream);
}

bool NpcSpawnPoint::toBinaryStream(ObjectOutputStream* stream) {
	stream->writeInt(spawnType);
	stream->writeInt(inUseByNumberOfMissions);
	stream->writeBoolean(npcSpawned);
	bool result = position.toBinaryStream(stream);
	result &= direction.toBinaryStream(stream);
	return result & npc.toBinaryStream(stream);
}

void NpcSpawnPoint::allocateNpc(TerrainManager* terrainManager, CreatureManager* creatureManager) {
	inUseByNumberOfMissions++;

	if (inUseByNumberOfMissions > 0) {
		if (despawnMissionNpcTask != NULL && despawnMissionNpcTask->isScheduled()) {
			despawnMissionNpcTask->cancel();
		}

		if (!npcSpawned) {
			//Spawn the NPC.
			String deliverNpc = "deliver_npc";
			float z = terrainManager->getHeight(position.getX(), position.getY());
			npc = cast<AiAgent*>(creatureManager->spawnCreature(deliverNpc.hashCode(), 0, position.getX(), z, position.getY(), 0));
			if (npc != NULL) {
				npc->updateDirection(direction.getW(), direction.getX(), direction.getY(), direction.getZ());
				//Set the name of the NPC.
				NameManager* nm = npc->getZoneProcessServer()->getNameManager();
				npc->setCustomObjectName(nm->makeCreatureName(), true);
				npcSpawned = true;
			} else {
				info("Failed to spawn npc at " + position.toString(), true);
			}
		}
	}
}

void NpcSpawnPoint::freeNpc(Reference<MissionManager*> missionManager) {
	inUseByNumberOfMissions--;

	if (inUseByNumberOfMissions == 0) {
		if (despawnMissionNpcTask == NULL) {
			despawnMissionNpcTask = new DespawnMissionNpcTask(missionManager, this);
		}

		if (despawnMissionNpcTask->isScheduled()) {
			return;
		} else {
			//Despawn after 1 minute.
			despawnMissionNpcTask->schedule(60 * 1000);
		}
	}
}

void NpcSpawnPoint::despawnNpc() {
	npcSpawned = false;
	if (npc != NULL) {
		Locker locker(npc);

		npc->scheduleDespawn(1);
	}
}
