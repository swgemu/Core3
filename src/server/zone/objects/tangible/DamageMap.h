/*
 * DamageMap.h
 *
 *  Created on: 13/07/2010
 *      Author: victor
 */

#ifndef DAMAGEMAP_H_
#define DAMAGEMAP_H_

#include "engine/engine.h"

namespace server {
 namespace zone {
  namespace objects {
   namespace player {
    class PlayerCreature;
   }
  }
 }
}

using namespace server::zone::objects::player;


namespace server {
namespace zone {
namespace objects {
namespace tangible {
namespace weapon {

class WeaponObject;

} // namespace weapon
} // namespace tangible
} // namespace objects
} // namespace zone
} // namespace server

using namespace server::zone::objects::tangible::weapon;

#include "server/zone/objects/tangible/weapon/WeaponObject.h"
#include "server/zone/objects/player/PlayerCreature.h"
#include "server/zone/objects/creature/CreatureObject.h"

class DamageMapEntry : public VectorMap<ManagedReference<WeaponObject*>, uint32> {


public:
	DamageMapEntry() {
		setNullValue(0);
	}

	DamageMapEntry(const DamageMapEntry& e) : VectorMap<ManagedReference<WeaponObject*>, uint32>(e) {
		setNullValue(0);
	}

	DamageMapEntry& operator=(const DamageMapEntry& e) {
		VectorMap<ManagedReference<WeaponObject*>, uint32>::operator=(e);

		return *this;
	}

	void addDamage(WeaponObject* weapon, uint32 damage);

};

class DamageMap : public VectorMap<ManagedReference<CreatureObject*> , DamageMapEntry> {

public:
	DamageMap() {
		setNoDuplicateInsertPlan();
	}

	DamageMap(const DamageMap& map) : VectorMap<ManagedReference<CreatureObject*> , DamageMapEntry>(map) {
		setNoDuplicateInsertPlan();
	}

	void addDamage(CreatureObject* creo, uint32 damage);

	void dropDamage(CreatureObject* creo);

	PlayerCreature* getHighestDamagePlayer();

	CreatureObject* getHighestThreatCreature();

	uint32 getTotalDamage();
};

#endif /* DAMAGEMAP_H_ */
