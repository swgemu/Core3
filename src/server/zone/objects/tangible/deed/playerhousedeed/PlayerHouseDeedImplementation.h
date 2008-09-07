#ifndef PLAYERHOUSEDEEDIMPLEMENTATION_H_
#define PLAYERHOUSEIMPLEMENTATION_H_

#include "../../../player/Player.h"
#include "../../../../packets.h"

#include "../DeedObject.h"
#include "../DeedObjectImplementation.h"

class DeedObject;
class TangibleObject;
class SceneObject;

class PlayerHouseDeedImplementation : public PlayerHouseDeedServant {
protected:
	int type, cellCount;
public:

public:

	PlayerHouseDeedImplementation(CreatureObject* creature, uint32 tempcrc, const unicode& n, const string& tempn);
	PlayerHouseDeedImplementation(uint64 objid, uint32 tempcrc, const unicode& n, const string& tempn);
	~PlayerHouseDeedImplementation();

	//int useObject(Player* player);

	//inline PlayerHouseDeed* deploy() {
	//	return (PlayerHouseDeed*) SceneObjectImplementation::deploy();
	//}
	inline int getCellCount(){
		return cellCount;
	}
private:
	void init();
};

#endif /*PLAYERHOUSEDEEDIMPLEMENTATION_H_*/

