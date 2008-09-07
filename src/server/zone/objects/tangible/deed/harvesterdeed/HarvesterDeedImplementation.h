#ifndef HARVESTERDEEDIMPLEMENTATION_H_
#define HARVESTERDEEDIMPLEMENTATION_H_

#include "../../../player/Player.h"
#include "../../../../packets.h"

#include "../DeedObject.h"
#include "../DeedObjectImplementation.h"

class DeedObject;
class TangibleObject;
class SceneObject;

class HarvesterDeedImplementation : public HarvesterDeedServant {
protected:
	int type, size;
public:
	static const int ORE = 1;
	static const int MOISTURE = 2;
	static const int LIQUID = 3;
	static const int GAS = 4;
	static const int FLORA = 5;
	static const int CREATURE = 6;

	static const int SMALL = 1;
	static const int MEDIUM = 2;
	static const int LARGE = 3;
public:

	HarvesterDeedImplementation(CreatureObject* creature, uint32 tempcrc, const unicode& n, const string& tempn);
	HarvesterDeedImplementation(uint64 objid, uint32 tempcrc, const unicode& n, const string& tempn);
	~HarvesterDeedImplementation();

	void init();

	void getType();

	void getSize();

	//inline HarvesterDeed* deploy() {
	//	return (HarvesterDeed*) SceneObjectImplementation::deploy();
	//}
private:

};

#endif /*HARVESTERDEEDIMPLEMENTATION_H_*/
