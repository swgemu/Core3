/*
 * GeneratorObjectImplementation.h
 *
 *  Created on: Oct 18, 2008
 *      Author: swgemu
 */

#ifndef GENERATOROBJECTIMPLEMENTATION_H_
#define GENERATOROBJECTIMPLEMENTATION_H_

#include "engine/engine.h"

#include "../../../../db/ServerDatabase.h"

class Zone;
class Player;
class DeedObject;
class GeneratorDeed;
class InstallationObject;

#include "GeneratorObject.h"

class GeneratorObjectImplementation : public GeneratorObjectServant {
protected:

	float hopperSizeMax;
	float extractionRate; // BER

public:
	GeneratorObjectImplementation(uint64 oid);
	GeneratorObjectImplementation(uint64 oid, GeneratorDeed *deed);
	~GeneratorObjectImplementation();

	// Attribute Setters
	inline void setHopperSizeMax(float size) {
		hopperSizeMax = size;
		String attr("hopperSizeMax");
		itemAttributes->setFloatAttribute(attr, (float)hopperSizeMax);
	}
	inline void setExtractionRate(float rate) {
		extractionRate = rate;
		String attr("extractionRate");
		itemAttributes->setFloatAttribute(attr, (float)extractionRate);
	}

	// Attribute Getters
	inline float getHopperSizeMax() {
		return hopperSizeMax;
	}
	inline float getExtractionRate() {
		return extractionRate;
	}
private:
	void init();
};


#endif /* GENERATOROBJECTIMPLEMENTATION_H_ */
