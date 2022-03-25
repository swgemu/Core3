/*
 * ThreatMap.h
 *
 *  Created on: 13/07/2010
 *      Author: victor
 */

#ifndef THREATMAP_H_
#define THREATMAP_H_

#include "engine/engine.h"
#include "ThreatMatrix.h"
#include "server/zone/objects/tangible/threat/ThreatMapObserver.h"
#include "server/zone/objects/creature/variables/CooldownTimerMap.h"
#include "server/zone/objects/tangible/weapon/WeaponObject.h"

namespace server {
namespace zone {
namespace objects {
namespace creature {
class CreatureObject;
}
}
}
}

using namespace server::zone::objects::creature;

namespace server {
namespace zone {
namespace objects {
namespace tangible {
namespace threat {

//#define DEBUG

class ThreatMapEntry : public VectorMap<String, uint32> {
	int aggroMod;
	uint64 threatBitmask;
	int healAmount;
	uint32 nonAggroDamageTotal;
	Time startTime;

public:
	ThreatMapEntry() {
		setNullValue(0);
		aggroMod = 0;
		threatBitmask = 0;
		healAmount = 0;
		nonAggroDamageTotal = 0;
	}

	ThreatMapEntry(const ThreatMapEntry& e) : VectorMap<String, uint32>(e) {
		setNullValue(0);
		aggroMod = e.aggroMod;
		threatBitmask = e.threatBitmask;
		healAmount = e.healAmount;
		nonAggroDamageTotal = e.nonAggroDamageTotal;
		startTime = e.startTime;
	}

	ThreatMapEntry& operator=(const ThreatMapEntry& e) {
		if (this == &e)
			return *this;

		aggroMod = e.aggroMod;
		threatBitmask = e.threatBitmask;
		healAmount = e.healAmount;
		nonAggroDamageTotal = e.nonAggroDamageTotal;
		startTime = e.startTime;

		VectorMap<String, uint32>::operator=(e);

		return *this;
	}

	void addDamage(WeaponObject* weapon, uint32 damage);
	void addDamage(String xp, uint32 damage);

	void setThreatState(uint64 state);
	bool hasState(uint64 state);
	void clearThreatState(uint64 state);

	void addAggro(int value) {
		aggroMod += value;
	}

	void addHeal(int value) {
		healAmount += value;
	}

	int getHeal() {
		return healAmount;
	}

	int getAggroMod() {
		return aggroMod;
	}

	uint32 getDurationSeconds() {
		Time now;
		return startTime.miliDifference(now) / 1000.0;
	}

	uint32 getDPS() {
		uint32 duration = getDurationSeconds();

		if (duration > 0) {
			return getTotalDamage() / getDurationSeconds();
		}

		return 0;
	}

	void removeAggro(int value) {
		aggroMod -= value;
	}

	void clearAggro() {
		aggroMod = 0;
	}

	uint32 getTotalDamage() {
		uint32 totalDamage = 0;

		for (int i = 0; i < size(); i++)
			totalDamage += elementAt(i).getValue();

		return totalDamage;
	}

	// getLootDamage excludes damage done by DOT's
	uint32 getLootDamage() {
		uint32 totalDamage = 0;

		for (int i = 0; i < size(); i++) {
			String type = elementAt(i).getKey();
			uint32 damage = elementAt(i).getValue();

			// Logger::console.info("Dam value type " + type + "  #" + String::valueOf(i) + " with a value of " + String::valueOf(damage), true);

			if (type == "dotDMG")
				continue;

			totalDamage += damage;
		}

		// Logger::console.info("Combined total damage = " + String::valueOf(totalDamage), true);

		return totalDamage;
	}

	void setNonAggroDamage(uint32 amount) {
		nonAggroDamageTotal = amount;
	}

	uint32 getNonAggroDamage() {
		return nonAggroDamageTotal;
	}
};

class ThreatMap : public VectorMap<ManagedReference<TangibleObject*>, ThreatMapEntry> {
public:
	/// Time between normal target evaluation
	enum { EVALUATIONCOOLDOWN = 24000 };

protected:
	ManagedWeakReference<TangibleObject*> self;
	CooldownTimerMap cooldownTimerMap;
	ManagedWeakReference<TangibleObject*> currentThreat;
	ThreatMatrix threatMatrix;
	ManagedReference<ThreatMapObserver*> threatMapObserver;
	Mutex lockMutex;

public:
	ThreatMap(TangibleObject* me) : VectorMap<ManagedReference<TangibleObject*>, ThreatMapEntry>(1, 0) {
		self = me;
		currentThreat = nullptr;
		setNoDuplicateInsertPlan();
	}

	ThreatMap(const ThreatMap& map) : VectorMap<ManagedReference<TangibleObject*>, ThreatMapEntry>(map), lockMutex() {
		setNoDuplicateInsertPlan();
		self = map.self;
		currentThreat = map.currentThreat;
		threatMapObserver = map.threatMapObserver;
		threatMatrix = map.threatMatrix;
		cooldownTimerMap = map.cooldownTimerMap;
	}

	ThreatMap& operator=(const ThreatMap& map) {
		if (this == &map)
			return *this;

		setNoDuplicateInsertPlan();
		self = map.self;
		currentThreat = map.currentThreat;
		threatMapObserver = map.threatMapObserver;
		threatMatrix = map.threatMatrix;
		cooldownTimerMap = map.cooldownTimerMap;

		VectorMap<ManagedReference<TangibleObject*>, ThreatMapEntry>::operator=(map);

		return *this;
	}

	~ThreatMap() {
	}

	void removeAll(bool forceRemoveAll = false);

	void removeObservers();

	void addDamage(TangibleObject* target, uint32 damage, String xp = "");
	void dropDamage(TangibleObject* target);

	bool setThreatState(TangibleObject* target, uint64 state, uint64 duration = 0, uint64 cooldown = 0);
	void clearThreatState(TangibleObject* target, uint64 state);

	bool hasState(uint64 state);
	bool isUniqueState(uint64 state);

	CreatureObject* getHighestDamagePlayer();
	CreatureObject* getHighestDamageGroupLeader();

	TangibleObject* getHighestThreatAttacker();
	uint32 getTotalDamage();

	void addAggro(TangibleObject* target, int value, uint64 duration = 0);
	void removeAggro(TangibleObject* target, int value);
	void clearAggro(TangibleObject* target);

	void addHeal(TangibleObject* target, int value);

private:
	void registerObserver(TangibleObject* target);
};
}
}
}
}
}

using namespace server::zone::objects::tangible::threat;

#endif /* THREATMAP_H_ */
