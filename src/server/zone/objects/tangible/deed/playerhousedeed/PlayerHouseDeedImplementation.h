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
	int type, cellCount, lotSize;

public:
	PlayerHouseDeedImplementation(CreatureObject* creature, uint32 tempcrc, const UnicodeString& n, const String& tempn);
	PlayerHouseDeedImplementation(uint64 objid, uint32 tempcrc, const UnicodeString& n, const String& tempn);
	~PlayerHouseDeedImplementation();

	inline int getCellCount() {
		return cellCount;
	}

	// Attribute Setters
	inline void setLotSize(int size) {
		lotSize = size;
		String attr("lotSize");
		itemAttributes->setIntAttribute(attr, lotSize);
	}

	// Attribute Getters

private:
	void init();
};

#endif /*PLAYERHOUSEDEEDIMPLEMENTATION_H_*/

