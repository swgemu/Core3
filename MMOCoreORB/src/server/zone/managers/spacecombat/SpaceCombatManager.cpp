#include "server/zone/managers/spacecombat/SpaceCombatManager.h"
#include "server/zone/managers/spacecollision/SpaceCollisionManager.h"

#include "server/zone/objects/ship/events/DestroyShipTask.h"
#include "server/zone/objects/ship/ShipComponentFlag.h"
#include "server/zone/objects/ship/ShipChassisData.h"
#include "server/zone/objects/ship/ComponentSlots.h"
#include "server/zone/objects/ship/ShipCollisionData.h"

#include "server/zone/packets/scene/PlayClientEffectLocMessage.h"
#include "server/zone/packets/jtl/CreateProjectileMessage.h"
#include "server/zone/packets/ship/OnShipHit.h"
#include "server/zone/packets/jtl/CreateMissileMessage.h"
#include "server/zone/packets/ship/DestroyShipComponentMessage.h"

void SpaceCombatManager::broadcastProjectile(ShipObject* ship, const ShipProjectile* projectile, CreatureObject* player) const {
	auto cov = ship == nullptr ? nullptr : ship->getCloseObjects();
	if (cov == nullptr) {
		return;
	}

	SortedVector<ManagedReference<TreeEntry*> > closeObjects;
	cov->safeCopyReceiversTo(closeObjects, CloseObjectsVector::PLAYERTYPE);

	for (int i = 0; i < closeObjects.size(); ++i) {
		auto playerEntry = closeObjects.get(i).castTo<CreatureObject*>();

		if (playerEntry == nullptr || playerEntry == player) {
			continue;
		}

		uint32 syncStamp = playerEntry->getSyncStamp();

		auto message = new CreateProjectileMessage(ship, projectile, syncStamp);
		playerEntry->sendMessage(message);
	}
}

void SpaceCombatManager::broadcastMissile(ShipObject* ship, const ShipMissile* missile) const {
	auto target = missile->getTarget().get();

	if (target == nullptr) {
		return;
	}

	Vector<BasePacket*> messages;
	messages.add(new CreateMissileMessage(ship, target, missile));
	messages.add(new UpdateMissileMessage(ship, missile, -1, UpdateMissileMessage::UpdateType::HIT));
	ship->broadcastMessages(&messages, true);
}

void SpaceCombatManager::broadcastMissileUpdate(ShipObject* ship, const ShipMissile* missile, int counterType, int missileResult) const {
	auto message = new UpdateMissileMessage(ship, missile, counterType, missileResult);
	ship->broadcastMessage(message, true);
}

void SpaceCombatManager::broadcastCountermeasure(ShipObject* ship, const ShipCountermeasure* counter, int missileResult) const {
	auto message = new UpdateMissileMessage(ship, counter, counter->getProjectileType(), missileResult);
	ship->broadcastMessage(message, true);
}

void SpaceCombatManager::getHitEffectMessages(ShipObject* target, const SpaceCollisionResult& result, int hitType, float newPercent, float oldPercent, Vector<BasePacket*>& messages) const {
	const Vector3& position = result.getPosition();
	String cefType	= "clienteffect/combat_ship_hit_" + shipHitTypeToString(hitType) + ".cef";

	messages.add(new PlayClientEffectLoc(cefType, "", position.getX(), position.getZ(), position.getY()));

	if (hitType == ShipHitType::HITCOMPONENT && newPercent <= 0.f) {
		messages.add(new DestroyShipComponentMessage(target, result.getSlot(), System::frandom(1.f)));
	} else {
		messages.add(new OnShipHit(target, result.getDirection(), hitType, newPercent, oldPercent));
	}
}

void SpaceCombatManager::applyDamage(ShipObject* ship, const ShipProjectile* projectile, const SpaceCollisionResult& result) const {
	if (ship == nullptr || projectile == nullptr) {
		return;
	}

	auto target = result.getObject().get();

	if (target == nullptr || !target->isShipObject()) {
		auto effect = new PlayClientEffectLoc("clienteffect/combat_ship_hit_armor.cef", "", result.getPosition().getX(), result.getPosition().getZ(), result.getPosition().getY());
		ship->broadcastMessage(effect, true);
		return;
	}

	auto targetShip = target->asShipObject();

	if (targetShip == nullptr || !targetShip->isAttackableBy(ship)) {
		auto effect = new PlayClientEffectLoc("clienteffect/combat_ship_hit_shield.cef", "", result.getPosition().getX(), result.getPosition().getZ(), result.getPosition().getY());
		ship->broadcastMessage(effect, true);
		return;
	}

	Locker tLock(target, ship);

	auto deltaVector = targetShip->getDeltaVector();

	if (deltaVector == nullptr) {
		return;
	}

	uint8 targetSlot = projectile->getComponentSlot();
	uint8 weaponSlot = projectile->getWeaponSlot();

	uint32 weaponIndex = ShipObject::WEAPON_COMPONENT_START + weaponSlot;

	float weaponEffect = ship->getComponentEfficiency(weaponIndex);

	if (weaponEffect <= 0) {
		return;
	}

	float minDamage = ship->getComponentMinDamageMap()->get(weaponIndex) * weaponEffect;
	float maxDamage = ship->getComponentMaxDamageMap()->get(weaponIndex) * weaponEffect;
	float shieldEffect = ship->getShieldEffectivenessMap()->get(weaponIndex);
	float armorEffect  = ship->getArmorEffectivenessMap()->get(weaponIndex);

	float damage = System::random(maxDamage - minDamage) + minDamage;

	if (damage <= 0.f || damage > 999999.f) {
		return;
	}

	if (damage > 1.f) {
		auto targetThreatMap = targetShip->getThreatMap();

		if (targetThreatMap != nullptr) {
			targetThreatMap->addDamage(ship, (uint32)damage);
		}

		targetShip->updateLastDamageReceived();

		if (targetShip->isShipAiAgent()) {
			auto targetAgent = targetShip->asShipAiAgent();

			if (targetAgent != nullptr && targetAgent->addEnemyShip(ship->getObjectID()) && ship->isPlayerShip()) {
				targetAgent->broadcastPvpStatusBitmask();
			}
		}
	}

	const Vector3& collisionPoint = result.getPosition();
	int collisionSlot = result.getSlot();
	bool hitFront = result.isHitFront();

	Vector<BasePacket*> messages;

	if (damage > 0.f) {
		damage = applyShieldDamage(targetShip, result, damage, shieldEffect, hitFront, deltaVector, messages);
	}

	if (damage > 0.f) {
		damage = applyArmorDamage(targetShip, result, damage, armorEffect,  hitFront, deltaVector, messages);
	}

	if (damage > 0.f && collisionSlot != Components::CHASSIS) {
		damage = applyComponentDamage(targetShip, result, damage, collisionSlot, deltaVector, messages);
	}

	if (damage > 0.f) {
		damage = applyActiveComponentDamage(targetShip, result, damage, targetSlot, deltaVector, messages);
	}

	if (damage > 0.f && targetShip->getShipComponentMap()->get(Components::BRIDGE) == 0) {
		damage = applyChassisDamage(targetShip, result, damage, deltaVector, messages);
	}

	if (deltaVector != nullptr) {
		deltaVector->sendMessages(targetShip);
	}

	if (messages.size() > 0) {
		target->broadcastMessages(&messages, true);
	}

	if (targetShip->getChassisCurrentHealth() == 0.f) {
		auto destroyTask = new DestroyShipTask(targetShip);
		destroyTask->execute();

		// If Agent ship kills player ship, remove the player from agents enemy list
		if (targetShip->isPlayerShip() && ship->isShipAiAgent()) {
			auto agentShip = ship->asShipAiAgent();

			if (agentShip != nullptr) {
				agentShip->removeEnemyShip(target->getObjectID());
			}
		}

		// Notify Destruction
		Reference<ShipObject*> refTarget = targetShip;
		Reference<ShipObject*> attackerRef = ship;

		Core::getTaskManager()->scheduleTask([refTarget, attackerRef] () {
			if (refTarget == nullptr || attackerRef == nullptr)
				return;

			Locker lock(refTarget);
			Locker clocker(attackerRef, refTarget);

			refTarget->notifyObjectDestructionObservers(attackerRef, 0, true);
		}, "notifyShipDestroyLambda", 200);
	}
}

float SpaceCombatManager::applyShieldDamage(ShipObject* target, const SpaceCollisionResult& result, float damage, float effect, bool hitFront, ShipDeltaVector* deltaVector, Vector<BasePacket*>& messages) const {
	float shieldCurrent = hitFront ? target->getFrontShield() : target->getRearShield();
	float shieldMax = hitFront ? target->getMaxFrontShield() : target->getMaxRearShield();

	if (shieldCurrent == 0.f || shieldMax == 0.f) {
		return damage;
	}

	float shieldDamage = damage * effect;

	if (shieldDamage == 0.f) {
		return 0.f;
	}

	float effectDamage = 0.f;
	float shieldOld = shieldCurrent / shieldMax;

	if (shieldDamage > shieldCurrent) {
		effectDamage = shieldCurrent;

		shieldDamage -= shieldCurrent;
		shieldCurrent = 0.f;
	} else {
		effectDamage = shieldDamage;

		shieldCurrent -= shieldDamage;
		shieldDamage = 0;
	}

	float shieldNew = shieldCurrent / shieldMax;

	if (shieldNew != shieldOld) {
		if (hitFront) {
			target->setFrontShield(shieldCurrent, false, nullptr, deltaVector);
		} else {
			target->setRearShield(shieldCurrent, false, nullptr, deltaVector);
		}

		getHitEffectMessages(target, result, ShipHitType::HITSHIELD, shieldNew, shieldOld, messages);

		if (target->isPobShip()) {
			Reference<PobShipObject*> pobTarget = target->asPobShip();

			if (pobTarget != nullptr) {
				float damageDifferential = (effectDamage / shieldMax);

				Core::getTaskManager()->scheduleTask([pobTarget, damageDifferential]() {
					if (pobTarget == nullptr) {
						return;
					}

					try {
						Locker lock(pobTarget);

						pobTarget->triggerInteriorDamage(ShipHitType::HITSHIELD, (damageDifferential * 100.f));
					} catch (const Exception& e) {
						pobTarget->error() << "Failed HITSHIELD for Pob triggerInteriorDamage";
					}
				}, "PobInteriorDamageLambda", 200);
			}
		}
	}

	return shieldDamage / effect;
}

float SpaceCombatManager::applyArmorDamage(ShipObject* target, const SpaceCollisionResult& result, float damage, float effect, bool hitFront, ShipDeltaVector* deltaVector, Vector<BasePacket*>& messages) const {
	uint32 slot = hitFront ? Components::ARMOR0 : Components::ARMOR1;

	float armorMin = target->getCurrentArmorMap()->get(slot);
	float armorMax = target->getMaxArmorMap()->get(slot);
	float healthMin = target->getCurrentHitpointsMap()->get(slot);
	float healthMax = target->getMaxHitpointsMap()->get(slot);

	if (armorMin == 0.f || armorMax == 0.f) {
		return damage;
	}

	float armorDamage = damage * effect;

	if (armorDamage <= 0.f) {
		return 0.f;
	}

	float armorOld = armorMin;
	float healthOld = healthMin;

	if (armorMin > 0.f) {
		if (armorDamage > armorMin) {
			armorDamage -= armorMin;
			armorMin = 0.f;
		} else {
			armorMin -= armorDamage;
			armorDamage = 0;
		}
	}

	if (healthMin > 0.f && armorDamage > 0.f) {
		if (armorDamage > healthMin) {
			armorDamage -= healthMin;
			healthMin = 0.f;
		} else {
			healthMin -= armorDamage;
			armorDamage = 0.f;
		}
	}

	if (armorMin != armorOld || healthMin != healthOld) {
		if (armorMin != armorOld) {
			target->setComponentArmor(slot, armorMin, nullptr, 2, deltaVector);
		}

		if (healthMin != healthOld) {
			target->setComponentHitpoints(slot, healthMin, nullptr, 2, deltaVector);
		}

		float totalMax = armorMax + healthMax;
		float totalNew = (armorMin + healthMin) / totalMax;
		float totalOld = (armorOld + healthOld) / totalMax;

		getHitEffectMessages(target, result, ShipHitType::HITARMOR, totalNew, totalOld, messages);

		if (target->isPobShip()) {
			Reference<PobShipObject*> pobTarget = target->asPobShip();

			if (pobTarget != nullptr) {
				float damageDifferential = (totalOld - totalNew);

				Core::getTaskManager()->scheduleTask([pobTarget, damageDifferential]() {
					if (pobTarget == nullptr) {
						return;
					}

					try {
						Locker lock(pobTarget);

						pobTarget->triggerInteriorDamage(ShipHitType::HITARMOR, (damageDifferential * 100.f));
					} catch (const Exception& e) {
						pobTarget->error() << "Failed HITARMOR for Pob triggerInteriorDamage";
					}
				}, "PobInteriorDamageLambda", 200);
			}
		}
	}

	if (target->getCurrentHitpointsMap()->get(slot) == 0.f) {
		target->setComponentDemolished(slot, false, deltaVector);
	}

	return armorDamage / effect;
}

float SpaceCombatManager::applyChassisDamage(ShipObject* target, const SpaceCollisionResult& result, float damage, ShipDeltaVector* deltaVector, Vector<BasePacket*>& messages) const {
	float chassisMin = target->getChassisCurrentHealth();
	float chassisMax = target->getChassisMaxHealth();

	if (chassisMin == 0.f || chassisMax == 0.f) {
		return damage;
	}

	float chassisOld = chassisMin / chassisMax;

	if (damage > chassisMin) {
		damage -= chassisMin;
		chassisMin = 0.f;
	} else {
		chassisMin -= damage;
		damage = 0;
	}

	float chassisNew = chassisMin / chassisMax;

	if (chassisNew != chassisOld) {
		target->setCurrentChassisHealth(chassisMin, false, nullptr, deltaVector);

		getHitEffectMessages(target, result, ShipHitType::HITCHASSIS, chassisNew, chassisOld, messages);

		if (target->isPobShip()) {
			Reference<PobShipObject*> pobTarget = target->asPobShip();

			if (pobTarget != nullptr) {
				float damageDifferential = (chassisOld - chassisNew);

				Core::getTaskManager()->scheduleTask([pobTarget, damageDifferential]() {
					if (pobTarget == nullptr) {
						return;
					}

					try {
						Locker lock(pobTarget);

						pobTarget->triggerInteriorDamage(ShipHitType::HITCHASSIS, (damageDifferential * 100.f));
					} catch (const Exception& e) {
						pobTarget->error() << "Failed HITCHASSIS for Pob triggerInteriorDamage";
					}
				}, "PobInteriorDamageLambda", 200);
			}
		}
	}

	return damage;
}

float SpaceCombatManager::applyComponentDamage(ShipObject* target, const SpaceCollisionResult& result, float damage, int slot, ShipDeltaVector* deltaVector, Vector<BasePacket*>& messages) const {
	float armorMin = target->getCurrentArmorMap()->get(slot);
	float armorMax = target->getMaxArmorMap()->get(slot);
	float healthMin = target->getCurrentHitpointsMap()->get(slot);
	float healthMax = target->getMaxHitpointsMap()->get(slot);

	if (armorMax == 0.f || healthMax == 0.f) {
		return damage;
	}

	if (armorMin == 0.f && healthMin == 0.f) {
		return damage;
	}

	float armorOld = armorMin;
	float healthOld = healthMin;

	if (armorMin > 0.f) {
		if (damage > armorMin) {
			damage -= armorMin;
			armorMin = 0.f;
		} else {
			armorMin -= damage;
			damage = 0;
		}
	}

	if (healthMin > 0.f && damage > 0.f) {
		if (damage > healthMin) {
			damage -= healthMin;
			healthMin = 0.f;
		} else {
			healthMin -= damage;
			damage = 0;
		}
	}

	if (armorMin != armorOld || healthMin != healthOld) {
		if (armorMin != armorOld) {
			target->setComponentArmor(slot, armorMin, nullptr, 2, deltaVector);
		}

		if (healthMin != healthOld) {
			target->setComponentHitpoints(slot, healthMin, nullptr, 2, deltaVector);
		}

		float totalMax = armorMax + healthMax;
		float totalNew = (armorMin + healthMin) / totalMax;
		float totalOld = (armorOld + healthOld) / totalMax;

		getHitEffectMessages(target, result, ShipHitType::HITCOMPONENT, totalNew, totalOld, messages);

		if (target->isPobShip()) {
			Reference<PobShipObject*> pobTarget = target->asPobShip();

			if (pobTarget != nullptr) {
				float damageDifferential = (totalOld - totalNew);

				Core::getTaskManager()->scheduleTask([pobTarget, damageDifferential]() {
					if (pobTarget == nullptr) {
						return;
					}

					try {
						Locker lock(pobTarget);

						pobTarget->triggerInteriorDamage(ShipHitType::HITCOMPONENT, (damageDifferential * 100.f));
					} catch (const Exception& e) {
						pobTarget->error() << "Failed HITCOMPONENT for Pob triggerInteriorDamage";
					}
				}, "PobInteriorDamageLambda", 200);
			}
		}
	}

	if (target->getCurrentHitpointsMap()->get(slot) <= 0.f) {
		target->setComponentDemolished(slot, false, deltaVector);

		if (slot == Components::BRIDGE) {
			applyChassisDamage(target, result, target->getChassisCurrentHealth(), deltaVector, messages);
		}
	}

	return damage;
}

float SpaceCombatManager::applyActiveComponentDamage(ShipObject* target, const SpaceCollisionResult& result, float damage, int targetSlot, ShipDeltaVector* deltaVector, Vector<BasePacket*>& messages) const {
	auto componentMap = target->getShipComponentMap();

	if (componentMap == nullptr) {
		return damage;
	}

	auto hitpointsMap = target->getCurrentHitpointsMap();

	if (hitpointsMap == nullptr) {
		return damage;
	}

	auto collisionData = ShipManager::instance()->getCollisionData(target);

	if (collisionData == nullptr) {
		return damage;
	}

	Vector<int> activeComponents;

	if (targetSlot != Components::CHASSIS) {
		int weight = collisionData->getSlotWeight(targetSlot);

		if (weight > 0 && weight <= System::random(100)) {
			activeComponents.add(targetSlot);
		}
	}

	for (int i = 0; i < componentMap->size(); ++i) {
		auto slot = componentMap->getKeyAt(i);
		auto compCRC = componentMap->getValueAt(i);

		if (compCRC == 0 || hitpointsMap->get(slot) == 0) {
			continue;
		}

		if (slot == Components::ARMOR0 || slot == Components::ARMOR1) {
			continue;
		}

		int weight = collisionData->getSlotWeight(slot);

		if (weight > 0 && weight <= System::random(100)) {
			activeComponents.add(slot);
		}
	}

	for (int i = activeComponents.size(); -1 < --i;) {
		int index = System::random(activeComponents.size() - 1);
		int slot = activeComponents.get(index);

		damage = applyComponentDamage(target, result, damage, slot, deltaVector, messages);

		if (hitpointsMap->get(slot) == 0) {
			activeComponents.remove(index);
		}

		if (damage <= 0.f) {
			break;
		}
	}

	return damage;
}

int SpaceCombatManager::updateProjectile(ShipObject* ship, ShipProjectile* projectile, SpaceCollisionResult& result, Vector<ManagedReference<SceneObject*>>& targetVectorCopy, const uint64& miliTime) {
	if (ship == nullptr || projectile == nullptr) {
		return ProjectileResult::EXPIRE;
	}

	if (projectile->isMissile()) {
		return updateMissile(ship, projectile, result, targetVectorCopy, miliTime);
	}

	long deltaTime = miliTime - projectile->getLastUpdateTime();

	if (deltaTime < CheckProjectilesTask::INTERVALMIN) {
		return ProjectileResult::MISS;
	}

	long totalTime = miliTime - projectile->getFirstUpdateTime();

	if (totalTime > projectile->getDeltaMax()) {
		deltaTime -= totalTime - projectile->getDeltaMax();

		if (deltaTime < CheckProjectilesTask::INTERVALMIN) {
			return ProjectileResult::EXPIRE;
		}
	}

	projectile->updatePosition(deltaTime, totalTime);

	if (!projectile->validatePosition()) {
		return ProjectileResult::EXPIRE;
	}

	if (projectile->isCountermeasure()) {
		return ProjectileResult::MISS;
	}

	if (SpaceCollisionManager::instance()->getProjectileCollision(ship, projectile, result, targetVectorCopy) != SpaceCollisionManager::MISS) {
		return ProjectileResult::HIT;
	}

	return ProjectileResult::MISS;
}

int SpaceCombatManager::updateMissile(ShipObject* ship, ShipProjectile* projectile, SpaceCollisionResult& result, Vector<ManagedReference<SceneObject*>>& targetVectorCopy, const uint64& miliTime) {
	if (ship == nullptr || projectile == nullptr || !projectile->isMissile()) {
		return ProjectileResult::EXPIRE;
	}

	auto missile = dynamic_cast<ShipMissile*>(projectile);

	if (missile == nullptr) {
		return ProjectileResult::EXPIRE;
	}

	auto target = missile->getTarget().get();

	if (target == nullptr) {
		return ProjectileResult::EXPIRE;
	}

	long deltaTime = miliTime - projectile->getLastUpdateTime();

	if (deltaTime < CheckProjectilesTask::INTERVALMIN) {
		return ProjectileResult::MISS;
	}

	long totalTime = miliTime - projectile->getFirstUpdateTime();

	if (totalTime > missile->getDeltaMax()) {
		broadcastMissileUpdate(ship, missile, -1, UpdateMissileMessage::UpdateType::MISS);
		return ProjectileResult::EXPIRE;
	}

	missile->updatePosition(deltaTime, totalTime);

	if (!missile->validatePosition()) {
		broadcastMissileUpdate(ship, missile, -1, UpdateMissileMessage::UpdateType::MISS);
		return ProjectileResult::EXPIRE;
	}

	Locker cLock(target, ship);
	auto entry = projectileMap.getEntry(target);

	if (entry != nullptr) {
		for (int i = 0; i < entry->size(); ++i) {
			auto targetProjectile = entry->getProjectile(i);
			if (targetProjectile == nullptr || !targetProjectile->isCountermeasure()) {
				continue;
			}

			auto counter = dynamic_cast<ShipCountermeasure*>(targetProjectile);
			if (counter == nullptr) {
				continue;
			}

			float sqrDistance = missile->getThisPosition().squaredDistanceTo(counter->getThisPosition());
			float radius = missile->getRadius() + counter->getRadius();

			if (sqrDistance <= (radius * radius)) {
				int missileDifficulty = missile->getDifficulty();
				int counterDifficulty = counter->getDifficulty();

				if (counterDifficulty >= missileDifficulty) {
					broadcastMissileUpdate(ship, missile, -1, UpdateMissileMessage::UpdateType::COUNTERED);
					return ProjectileResult::EXPIRE;
				}
			}
		}
	}

	if (totalTime < missile->getTimeToHit()) {
		return ProjectileResult::MISS;
	}

	if (SpaceCollisionManager::instance()->getProjectileCollision(ship, projectile, result, targetVectorCopy) != SpaceCollisionManager::MISS) {
		broadcastMissileUpdate(ship, missile, -1, UpdateMissileMessage::UpdateType::HIT);
		return ProjectileResult::HIT;
	}

	return ProjectileResult::MISS;
}

int SpaceCombatManager::updateProjectiles() {
	uint64 miliTime = System::getMiliTime();

	try {
		for (int i = projectileMap.mapSize(); -1 < --i;) {
			if (projectileMap.entrySize(i) == 0) {
				projectileMap.removeShip(i);
				continue;
			}

			auto ship = projectileMap.getShip(i);

			if (ship == nullptr || ship->getZone() == nullptr) {
				projectileMap.removeShip(i);
				continue;
			}

			Locker sLock(ship);

			auto targetVector = ship->getTargetVector();

			if (targetVector == nullptr || targetVector->size() == 0) {
				projectileMap.removeShip(i);
				continue;
			}

			Vector<ManagedReference<SceneObject*>> targetVectorCopy;
			targetVector->safeCopyTo(targetVectorCopy);

			for (int ii = projectileMap.entrySize(i); -1 < --ii;) {
				auto projectile = projectileMap.getProjectile(i, ii);

				if (projectile == nullptr) {
					projectileMap.removeProjectile(i, ii);
					continue;
				}

				SpaceCollisionResult result;
				int hitResult = updateProjectile(ship, projectile, result, targetVectorCopy, miliTime);

				if (hitResult == ProjectileResult::HIT) {
					applyDamage(ship, projectile, result);
#ifdef SPACECOLLISION_DEBUG
					result.debugCollision(ship, projectile);
#endif // SPACECOLLISION_DEBUG
					projectileMap.removeProjectile(i, ii);
					continue;
				}

#ifdef SHIPPROJECTILE_DEBUG
				projectile->debugProjectile(ship, hitResult);
#endif // SHIPPROJECTILE_DEBUG

				if (hitResult == ProjectileResult::EXPIRE) {
					projectileMap.removeProjectile(i, ii);
					continue;
				}

				if (hitResult == ProjectileResult::MISS) {
					projectile->setLastUpdateTime(miliTime);
					continue;
				}
			}
		}

	} catch (Exception& e ) {
		error() << e.getMessage();
		e.printStackTrace();
	}

	return System::getMiliTime() - miliTime;
}

void SpaceCombatManager::addProjectile(ShipObject* ship, ShipProjectile* projectile, CreatureObject* player) {
	if (ship == nullptr || projectile == nullptr) {
		return;
	}

	Locker sLock(ship);

	projectileMap.addProjectile(ship, projectile);
	broadcastProjectile(ship, projectile, player);
}

void SpaceCombatManager::addMissile(ShipObject* ship, ShipMissile* missile) {
	if (ship == nullptr || missile == nullptr) {
		return;
	}

	Locker sLock(ship);

	projectileMap.addProjectile(ship, missile);
	broadcastMissile(ship, missile);
}

void SpaceCombatManager::addCountermeasure(ShipObject* ship, ShipCountermeasure* counter) {
	if (ship == nullptr || counter == nullptr) {
		return;
	}

	Locker sLock(ship);

	projectileMap.addProjectile(ship, counter);
	broadcastCountermeasure(ship, counter, UpdateMissileMessage::UpdateType::COUNTERFAILED);
}
