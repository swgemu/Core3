/*
 * FactoryObjectImplementation.h
 *
 *  Created on: Oct 18, 2008
 *      Author: swgemu
 */

#ifndef FACTORYOBJECTIMPLEMENTATION_H_
#define FACTORYOBJECTIMPLEMENTATION_H_


#include "engine/engine.h"

#include "../../../../db/ServerDatabase.h"

class Zone;
class Player;
class DeedObject;
class FactoryDeed;
class InstallationObject;

#include "FactoryObject.h"

class FactoryObjectImplementation : public FactoryObjectServant {
protected:
	float hopperSizeMax;

public:
	FactoryObjectImplementation(uint64 oid);
	FactoryObjectImplementation(uint64 oid, FactoryDeed *deed);
	~FactoryObjectImplementation();

	// Attribute Setters
	inline void setHopperSizeMax(float size) {
		hopperSizeMax = size;
		String attr("hopperSizeMax");
		itemAttributes->setFloatAttribute(attr, (float)hopperSizeMax);
	}

	// Attribute Getters
	inline float getHopperSizeMax() {
		return hopperSizeMax;
	}
	int getFactoryType();
private:
	void init();
};


#endif /* FACTORYOBJECTIMPLEMENTATION_H_ */
