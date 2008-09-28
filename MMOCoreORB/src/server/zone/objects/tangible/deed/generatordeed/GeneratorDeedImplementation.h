#ifndef GENERATORDEEDIMPLEMENTATION_H_
#define GENERATORDEEDIMPLEMENTATION_H_

#include "../../../player/Player.h"
#include "../../../../packets.h"

#include "../DeedObject.h"
#include "../DeedObjectImplementation.h"

class DeedObject;
class TangibleObject;
class SceneObject;

class GeneratorDeedImplementation : public GeneratorDeedServant {
protected:
	int type;
public:
	static const int FUSION = 1;
	static const int PHOTOBIO = 2;
	static const int SOLAR = 3;
	static const int WIND = 4;

public:

	GeneratorDeedImplementation(CreatureObject* creature, uint32 tempcrc, const unicode& n, const string& tempn);
	GeneratorDeedImplementation(uint64 objid, uint32 tempcrc, const unicode& n, const string& tempn);
	~GeneratorDeedImplementation();

	//inline GeneratorDeed* deploy() {
	//	return (GeneratorDeed*) SceneObjectImplementation::deploy();
	//}
private:
	void init();
};

#endif /*GENERATORDEEDIMPLEMENTATION_H_*/
