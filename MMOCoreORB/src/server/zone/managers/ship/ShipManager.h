/*
 * ShipManager.h
 *
 *  Created on: 18/10/2013
 *      Author: victor
 */

#ifndef SHIPMANAGER_H_
#define SHIPMANAGER_H_

#include "engine/engine.h"
#include "server/zone/objects/ship/ShipComponent.h"

class ShipManager : public Singleton<ShipManager>, public Object, public Logger {
	HashTable<uint32, Reference<ShipComponent*> > shipComponents;

public:
	ShipManager();

	ShipComponent* getShipComponent(const String& name) {
		return shipComponents.get(name.hashCode());
	}

	ShipComponent* getShipComponent(uint32 hash) {
		return shipComponents.get(hash);
	}
};



#endif /* SHIPMANAGER_H_ */
