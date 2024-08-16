/*
 * MinefieldAttackTask.h
 *
 *  Created on: 20/12/2012
 *      Author: victor
 */

#ifndef MINEFIELDATTACKTASK_H_
#define MINEFIELDATTACKTASK_H_

#include "engine/engine.h"
#include "server/zone/managers/objectcontroller/ObjectController.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/packets/scene/PlayClientEffectLocMessage.h"
#include "server/zone/objects/creature/commands/CombatQueueCommand.h"
#include "server/zone/objects/installation/components/MinefieldDataComponent.h"
#include "server/zone/objects/installation/components/TurretDataComponent.h"

class MinefieldAttackTask : public Task {
	ManagedWeakReference<TangibleObject*> weakMinefield;
	ManagedWeakReference<CreatureObject*> weakTarget;

public:
	MinefieldAttackTask(TangibleObject* minefield, CreatureObject* creatureTarget) {
		weakMinefield = minefield;
		weakTarget = creatureTarget;
	}

	void run() {
		ManagedReference<TangibleObject*> minefield = weakMinefield.get();

		if (minefield == nullptr) {
			return;
		}

		auto zone = minefield->getZone();

		if (zone == nullptr) {
			return;
		}

		ManagedReference<CreatureObject*> creatureTarget = weakTarget.get();

		if (creatureTarget == nullptr) {
			return;
		}

		auto zoneServer = minefield->getZoneServer();

		if (zoneServer == nullptr) {
			return;
		}

		Locker locker(minefield);

		if (minefield->getContainerObjectsSize() <= 0) {
			return;
		}

		DataObjectComponentReference* dataComponent = minefield->getDataObjectComponent();

		if (dataComponent == nullptr) {
			return;
		}

		if (!CollisionManager::checkLineOfSight(creatureTarget, minefield)) {
			return;
		}

		ManagedReference<WeaponObject*> weapon = minefield->getContainerObject(0).castTo<WeaponObject*>();

		if (weapon == nullptr) {
			return;
		}

		if (minefield->isTurret()) {
			TurretDataComponent* turretData = cast<TurretDataComponent*>(dataComponent->get());

			if (turretData == nullptr || !turretData->canExplodeMine()) {
				return;
			}

			// Update cooldown
			turretData->updateMineCooldown((uint64)(weapon->getAttackSpeed() * 1000));
		} else {
			MinefieldDataComponent* mineData = cast<MinefieldDataComponent*>(dataComponent->get());

			if (mineData == nullptr || !mineData->canExplode()) {
				return;
			}

			// Update cooldown
			mineData->updateCooldown((uint64)(weapon->getAttackSpeed() * 1000));
		}

		float damageRadius = weapon->getDamageRadius();

		auto targetCov = creatureTarget->getCloseObjects();

		if (targetCov == nullptr) {
			return;
		}

		SortedVector<TreeEntry*> closeObjects;

		closeObjects.removeAll(targetCov->size(), 10);
		targetCov->safeCopyReceiversTo(closeObjects, CloseObjectsVector::CREOTYPE);

		for (int i = 0; i < closeObjects.size(); i++) {
			SceneObject* object = static_cast<SceneObject*>(closeObjects.get(i));

			if (object == nullptr) {
				continue;
			}

			Reference<CreatureObject*> targetCreo = object->asCreatureObject();

			if (targetCreo == nullptr) {
				continue;
			}

			// Check target is within range
			if (!targetCreo->isInRange(creatureTarget, damageRadius)) {
				continue;
			}

			// Check target is valid attackable target
			if (!targetCreo->isAttackableBy(minefield)) {
				continue;
			}

			// Check that the mine has LoS of the creature to damage
			if (!CollisionManager::checkLineOfSight(targetCreo, creatureTarget)) {
				continue;
			}

			// Damage the creature target
			Locker targetClock(targetCreo, minefield);

			// Player mine explosion animation
			auto explodeLoc = new PlayClientEffectLoc("clienteffect/lair_damage_heavy.cef", zone->getZoneName(), targetCreo->getPositionX(), targetCreo->getPositionZ(), targetCreo->getPositionY());

			if (explodeLoc != nullptr) {
				targetCreo->broadcastMessage(explodeLoc, true, false);
			}

			float minDamage = weapon->getMinDamage();
			float maxDamage = weapon->getMaxDamage();

			CombatManager::instance()->doObjectDetonation(minefield, targetCreo, (System::frandom(maxDamage - minDamage) + minDamage), weapon);
		}

		Locker lockerw(weapon, minefield);

		int weaponUses = weapon->getUseCount();

		// Mine has greater than 1 use count
		if (weaponUses > 1) {
			weapon->setUseCount(weaponUses - 1, true);
		// Mine is down to one use count, destroy
		} else {
			weapon->destroyObjectFromWorld(true);
			weapon->destroyObjectFromDatabase(true);
		}
	}
};

#endif /* MINEFIELDATTACKTASK_H_ */
