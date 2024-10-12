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
		CONCUSSION_MK1 = 0,
		CONCUSSION_MK2 = 1,
		CONCUSSION_MK3 = 2,
		IMAGEREC_MK1 = 3,
		IMAGEREC_MK2 = 4,
		PROTON_MK1 = 5,
		PROTON_MK2 = 6,
		PROTON_MK3 = 7,
		PROTON_MK4 = 8,
		SEISMIC_MK1 = 9,
		SEISMIC_MK2 = 10,
		SEISMIC_MK3 = 11,
		SPACEBOMB_MK1 = 12,
		SPACEBOMB_MK2 = 13
	};

	enum AiMissileType : int {
		AI_PROTON_TIER1 = 16,
		AI_PROTON_TIER2 = 17,
		AI_PROTON_TIER3 = 18,
		AI_PROTON_TIER4 = 19,
		AI_PROTON_TIER5 = 20
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

	CreateMissileMessage(ShipObject* source, ShipObject* target, const ShipMissile* missile) : BaseMessage() {
		insertShort(0x14);
		insertInt(0x721CF08B);  // CRC

		insertInt(missile->getUniqueID());
		insertLong(source->getObjectID());
		insertLong(target->getObjectID());

		const Vector3& missilePosition = missile->getThisPosition();

		insertFloat(missilePosition.getX());
		insertFloat(missilePosition.getZ());
		insertFloat(missilePosition.getY());

		int timeToHit = (int)(missile->getTimeToHit() * 0.001f);
		Vector3 targetPosition = missile->getTargetPosition(target, timeToHit);

		insertFloat(targetPosition.getX());
		insertFloat(targetPosition.getZ());
		insertFloat(targetPosition.getY());

		insertInt(timeToHit);
		insertInt(missile->getProjectileType());
		insertInt(missile->getWeaponSlot());
		insertInt(missile->getComponentSlot());
	}
};

#endif // CREATEMISSILEMESSAGE_H_
