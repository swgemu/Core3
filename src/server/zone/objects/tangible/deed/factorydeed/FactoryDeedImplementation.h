
#ifndef FACTORYDEEDIMPLEMENTATION_H_
#define FACTORYDEEDIMPLEMENTATION_H_

#include "../../../player/Player.h"
#include "../../../../packets.h"

#include "../DeedObject.h"
#include "../DeedObjectImplementation.h"

class DeedObject;
class TangibleObject;
class SceneObject;

class FactoryDeedImplementation : public FactoryDeedServant {
protected:
	int type;
public:
	static const int EQUIPMENT = 1;
	static const int FOOD = 2;
	static const int STRUCTURE = 3;
	static const int WEARABLES = 4;

public:

	FactoryDeedImplementation(CreatureObject* creature, uint32 tempcrc, const unicode& n, const string& tempn);
	FactoryDeedImplementation(uint64 objid, uint32 tempcrc, const unicode& n, const string& tempn);
	~FactoryDeedImplementation();

	void init();

	//int useObject(Player* player);

	//inline FactoryDeed* deploy() {
	//	return (FactoryDeed*) SceneObjectImplementation::deploy();
	//}
private:

};

#endif /*FACTORYDEEDIMPLEMENTATION_H_*/
