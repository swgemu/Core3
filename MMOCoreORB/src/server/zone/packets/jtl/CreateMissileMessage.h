/*
 * CreateMissileMessage.h
 *
 *  Created on: Nov 20, 2008
 *      Author: swgemu
 */

#ifndef CREATEMISSILEMESSAGE_H_
#define CREATEMISSILEMESSAGE_H_

#include "engine/service/proto/BaseMessage.h"
#include "server/zone/objects/ship/ShipObject.h"

class CreateMissileMessage : public BaseMessage {
	enum PlayerMissileType : int {
		concussion_mk1 = 0,
		concussion_mk2 = 1,
		concussion_mk3 = 2,
		imagerec_mk1 = 3,
		imagerec_mk2 = 4,
		proton_mk1 = 5,
		proton_mk2 = 6,
		proton_mk3 = 7,
		proton_mk4 = 8,
		seismic_mk1 = 9,
		seismic_mk2 = 10,
		seismic_mk3 = 11,
		spacebomb_mk1 = 12,
		spacebomb_mk2 = 13
	};

	enum AiMissileType : int {
		ai_proton_tier1 = 16,
		ai_proton_tier2 = 17,
		ai_proton_tier3 = 18,
		ai_proton_tier4 = 19,
		ai_proton_tier5 = 20,
	};

public:
	CreateMissileMessage(SceneObject* source, SceneObject* target, int impactTime, int missileId, int missileType, int weaponSlot, int targetSlot) : BaseMessage() {
		insertShort(0x14);
		insertInt(0x721CF08B);  // CRC

		insertInt(missileId);
		insertLong(source->getObjectID());
		insertLong(target->getObjectID());

		insertFloat(source->getPositionX());
		insertFloat(source->getPositionZ());
		insertFloat(source->getPositionY());

		insertFloat(target->getPositionX());
		insertFloat(target->getPositionZ());
		insertFloat(target->getPositionY());

		insertInt(impactTime);
		insertInt(missileType);
		insertInt(weaponSlot);
		insertInt(targetSlot);
	}

	CreateMissileMessage(SceneObject* source, SceneObject* target, const Vector3& targetPosition, int impactTime, int missileId, int missileType, int weaponSlot, int targetSlot) : BaseMessage() {
		insertShort(0x14);
		insertInt(0x721CF08B);  // CRC

		insertInt(missileId);
		insertLong(source->getObjectID());
		insertLong(target->getObjectID());

		insertFloat(source->getPositionX());
		insertFloat(source->getPositionZ());
		insertFloat(source->getPositionY());

		insertFloat(targetPosition.getX());
		insertFloat(targetPosition.getZ());
		insertFloat(targetPosition.getY());

		insertInt(impactTime);
		insertInt(missileType);
		insertInt(weaponSlot);
		insertInt(targetSlot);
	}

	CreateMissileMessage(SceneObject* source, SceneObject* target, const ShipMissile* missile) : BaseMessage() {
		insertShort(0x14);
		insertInt(0x721CF08B);  // CRC

		insertInt(missile->getUniqueID());
		insertLong(source->getObjectID());
		insertLong(target->getObjectID());

		const Vector3& missilePosition = missile->getThisPosition();

		insertFloat(missilePosition.getX());
		insertFloat(missilePosition.getZ());
		insertFloat(missilePosition.getY());

		const Vector3& targetPosition = target->getPosition();

		insertFloat(targetPosition.getX());
		insertFloat(targetPosition.getZ());
		insertFloat(targetPosition.getY());

		insertInt((int)(missile->getTimeToHit() * 0.001f));
		insertInt(missile->getProjectileType());
		insertInt(missile->getWeaponSlot());
		insertInt(missile->getComponentSlot());
	}
};

#endif // CREATEMISSILEMESSAGE_H_
