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
	float specRate;

public:
	GeneratorObjectImplementation(uint64 oid);
	GeneratorObjectImplementation(uint64 oid, GeneratorDeed *deed);
	~GeneratorObjectImplementation();

private:
	void init();
};


#endif /* GENERATOROBJECTIMPLEMENTATION_H_ */
