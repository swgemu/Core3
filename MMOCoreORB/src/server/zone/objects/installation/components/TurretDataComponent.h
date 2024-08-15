/*
 * TurretDataComponent.h
 *
 *  Created on: Nov 24, 2012
 *      Author: root
 */

#ifndef TURRETDATACOMPONENT_H_
#define TURRETDATACOMPONENT_H_

#include "engine/engine.h"
#include "server/zone/objects/scene/components/DataObjectComponent.h"
#include "server/zone/packets/scene/AttributeListMessage.h"
#include "templates/installation/SharedInstallationObjectTemplate.h"
#include "server/zone/objects/tangible/weapon/WeaponObject.h"
#include "server/zone/objects/creature/CreatureObject.h"

class TurretDataComponent : public DataObjectComponent {
protected:
	float maxRange;
	float attackSpeed;

	Time nextAutoFireTime;

	SharedInstallationObjectTemplate* templateData;

	ManagedWeakReference<CreatureObject*> controller;
	ManagedWeakReference<CreatureObject*> manualTarget;
	ManagedWeakReference<CreatureObject*> lastAutoTarget;

	Reference<Task*> turretTask;
	AtomicInteger numberOfPlayersInRange;

	float maxMineRange;
	Time explodeDelay;

	Vector<ManagedReference<WeaponObject*>> mines;
	SynchronizedSortedVector<uint64> notifiedPlayers;

public:
	TurretDataComponent() {
		maxRange = 80.f;
		attackSpeed = 1.f;

		nextAutoFireTime.updateToCurrentTime();

		templateData = nullptr;
		controller = nullptr;
		manualTarget = nullptr;
		turretTask = nullptr;

		maxMineRange = 32.f;
		explodeDelay.updateToCurrentTime();
	}

	~TurretDataComponent() {
	}

	void writeJSON(nlohmann::json& j) const {
		DataObjectComponent::writeJSON(j);

		SERIALIZE_JSON_MEMBER(maxRange);
		SERIALIZE_JSON_MEMBER(attackSpeed);
		SERIALIZE_JSON_MEMBER(nextAutoFireTime);

		if (templateData) {
			j["templateData"] = templateData->getTemplateFileName();
		} else {
			j["templateData"] = "";
		}

		SERIALIZE_JSON_MEMBER(controller);
		SERIALIZE_JSON_MEMBER(manualTarget);
		SERIALIZE_JSON_MEMBER(lastAutoTarget);
		SERIALIZE_JSON_MEMBER(numberOfPlayersInRange);
	}

	void initializeTransientMembers();
	void fillAttributeList(AttributeListMessage* alm);

	Vector<CreatureObject*> getAvailableTargets(bool aggroOnly);
	CreatureObject* selectTarget();
	bool checkTarget(CreatureObject* creature, TangibleObject* turret, bool aggroOnly);

	void updateAutoCooldown(float secondsToAdd);

	void scheduleFireTask(CreatureObject* target, TangibleObject* terminal, int delay = 0);
	void rescheduleFireTask(bool wasManual, bool isManual);
	int getAutoFireTimeout();

	/*
	 * Setters
	 */

	void setController(CreatureObject* creature) {
		controller = creature;
	}

	void setManualTarget(CreatureObject* creature) {
		manualTarget = creature;
	}

	uint32 incrementNumberOfPlayersInRange() {
		return numberOfPlayersInRange.increment();
	}

	uint32 decrementNumberOfPlayersInRange() {
		return numberOfPlayersInRange.decrement();
	}

	void addNotifiedPlayer(const uint64 oid) {
		notifiedPlayers.put(oid);
	}

	void removeNotifiedPlayer(const uint64 oid) {
		notifiedPlayers.drop(oid);
	}

	void updateMineCooldown(uint64 cooldown) {
		explodeDelay.updateToCurrentTime();
		explodeDelay.addMiliTime(cooldown);
	}

	/*
	 * Getters
	 */

	int getRescheduleDelay() {
		int delay = 0;

		if (nextAutoFireTime.isFuture()) {
			delay = Time().miliDifference(nextAutoFireTime);
		}

		return delay;
	}

	CreatureObject* getController() {
		return controller.get();
	}

	CreatureObject* getManualTarget() {
		return manualTarget.get();
	}

	int getMaxRange() {
		return maxRange;
	}

	float getAttackSpeed() {
		return attackSpeed;
	}

	Task* getFireTask() {
		return turretTask;
	}

	uint32 getNumberOfPlayersInRange() {
		return numberOfPlayersInRange.get();
	}

	int getMineCount() {
		return mines.size();
	}

	float getMaxMineRange() {
		return maxMineRange;
	}

	bool compareAndSetNumberOfPlayersInRange(uint32 oldVal, uint32 newVal) {
		return numberOfPlayersInRange.compareAndSet(oldVal, newVal);
	}

	bool canExplodeMine() {
		return explodeDelay.isPast();
	}

	bool isTurretData() {
		return true;
	}

	bool hasNotifiedPlayer(const uint64 oid) {
		return notifiedPlayers.contains(oid);
	}

private:
	void addSerializableVariables() {
		addSerializableVariable("mines", &mines);
	}
};

#endif /* TURRETDATACOMPONENT_H_ */
