/*
 * ThreatMap.h
 *
 *  Created on: 13/07/2010
 *      Author: victor
 */

#ifndef THREATMAP_H_
#define THREATMAP_H_



#include "engine/engine.h"
#include "ThreatStates.h"
#include "ThreatMatrix.h"
#include "ThreatMapObserver.h"
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

class ThreatMapEntry : public VectorMap<ManagedReference<WeaponObject*>, uint32> {

	int aggroMod;
	uint64 threatBitmask;
	int healAmount;

public:
	ThreatMapEntry() {
		setNullValue(0);
		aggroMod = 0;
		threatBitmask = 0;
		healAmount = 0;
	}

	ThreatMapEntry(const ThreatMapEntry& e) : VectorMap<ManagedReference<WeaponObject*>, uint32>(e) {
		setNullValue(0);
		aggroMod = e.aggroMod;
		threatBitmask = e.threatBitmask;
		healAmount = e.healAmount;
	}

	ThreatMapEntry& operator=(const ThreatMapEntry& e) {
		VectorMap<ManagedReference<WeaponObject*>, uint32>::operator=(e);
		aggroMod = e.aggroMod;
		threatBitmask = e.threatBitmask;
		healAmount = e.healAmount;

		return *this;
	}

	void addDamage(WeaponObject* weapon, uint32 damage);

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

	void removeAggro(int value) {
		aggroMod -= value;
	}

	void clearAggro() {
		aggroMod = 0;
	}
};

class ThreatMap : public VectorMap<ManagedReference<CreatureObject*> , ThreatMapEntry> {
public:
	/// Time between normal target evaluation
	static const int EVALUATIONCOOLDOWN = 12000;

protected:
	ManagedReference<TangibleObject*> self;
	CooldownTimerMap cooldownTimerMap;
	WeakReference<CreatureObject*> currentThreat;
	ThreatMatrix threatMatrix;
	ManagedReference<ThreatMapObserver*> threatMapObserver;

public:
	ThreatMap(TangibleObject* me) {
		self = me;
		currentThreat = NULL;
		setNoDuplicateInsertPlan();
	}

	ThreatMap(const ThreatMap& map) : VectorMap<ManagedReference<CreatureObject*> , ThreatMapEntry>(map) {
		setNoDuplicateInsertPlan();
		self = map.self;
		currentThreat = map.currentThreat;
	}

	~ThreatMap() {
		removeAll();
	}

	void removeAll() {
		removeObservers();
		VectorMap<ManagedReference<CreatureObject*> , ThreatMapEntry>::removeAll();
	}

	void removeObservers();

	void addDamage(CreatureObject* target, uint32 damage);
	void dropDamage(CreatureObject* target);

	bool setThreatState(CreatureObject* target, uint64 state, uint64 duration = 0, uint64 cooldown = 0);
	void clearThreatState(CreatureObject* target, uint64 state);

	bool hasState(uint64 state);
	bool isUniqueState(uint64 state);

	CreatureObject* getHighestDamagePlayer();

	CreatureObject* getHighestThreatCreature();
	uint32 getTotalDamage();

	void addAggro(CreatureObject* target, int value, uint64 duration = 0);
	void removeAggro(CreatureObject* target, int value);
	void clearAggro(CreatureObject* target);

	void addHeal(CreatureObject* target, int value);
private:

	void registerObserver(CreatureObject* target);

};

    }
   }
  }
 }
}

using namespace server::zone::objects::tangible::threat;

#endif /* THREATMAP_H_ */
