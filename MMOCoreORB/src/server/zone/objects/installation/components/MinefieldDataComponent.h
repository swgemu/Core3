/*
 * MinefieldDataComponent.h
 *
 *  Created on: Dec 17, 2012
 *      Author: root
 */

#ifndef MINEFIELDDATACOMPONENT_H_
#define MINEFIELDDATACOMPONENT_H_
#include "engine/engine.h"
#include "server/zone/objects/scene/components/DataObjectComponent.h"
#include "server/zone/objects/tangible/weapon/WeaponObject.h"
#include "templates/installation/SharedInstallationObjectTemplate.h"

class MinefieldDataComponent : public DataObjectComponent {
protected:
	const static int CAPACITY = 20;

	Time explodeDelay;
	float attackSpeed;
	float maxRange;

	Vector<ManagedReference<WeaponObject*>> mines;
	SharedInstallationObjectTemplate* templateData;
	SynchronizedSortedVector<uint64> notifiedPlayers;

public:
	MinefieldDataComponent() {
		attackSpeed = 5.f;
		maxRange = 32.f;

		templateData = nullptr;
		explodeDelay.updateToCurrentTime();

		addSerializableVariables();
	}

	virtual ~MinefieldDataComponent() {
	}

	void writeJSON(nlohmann::json& j) const {
		DataObjectComponent::writeJSON(j);

		SERIALIZE_JSON_MEMBER(mines);
	}

	void initializeTransientMembers() {
		// Logger::Logger tlog("minefieldata");
		// tlog.info("initializing minefield transients",true);
		if (getParent() != nullptr) {
			templateData = dynamic_cast<SharedInstallationObjectTemplate*>(getParent()->getObjectTemplate());
			attackSpeed = 5;
		}
	}

	bool isMinefieldData() {
		return true;
	}

	bool canExplode() {
		return explodeDelay.isPast();
	}

	int getCapacity() {
		return CAPACITY;
	}

	void updateCooldown(uint64 cooldown) {
		explodeDelay.updateToCurrentTime();
		explodeDelay.addMiliTime(cooldown);
	}

	void addMine(WeaponObject* weapon) {
		if (weapon == nullptr) {
			return;
		}

		mines.add(weapon);
	}

	WeaponObject* getMine(int indx) {
		return mines.get(indx);
	}

	WeaponObject* removeMine(int indx) {
		return mines.remove(indx);
	}

	int getMineCapacity() {
		return CAPACITY;
	}

	int getMineCount() {
		return mines.size();
	}

	void setMaxRange(float val) {
		maxRange = val;
	}

	float getMaxRange() {
		return maxRange;
	}

	bool hasNotifiedPlayer(const uint64 oid) {
		return notifiedPlayers.contains(oid);
	}

	void addNotifiedPlayer(const uint64 oid) {
		notifiedPlayers.put(oid);
	}

	void removeNotifiedPlayer(const uint64 oid) {
		notifiedPlayers.drop(oid);
	}

private:
	void addSerializableVariables() {
		addSerializableVariable("mines", &mines);
	}
};

#endif /* MINEFIELDDATACOMPONENT_H_ */
