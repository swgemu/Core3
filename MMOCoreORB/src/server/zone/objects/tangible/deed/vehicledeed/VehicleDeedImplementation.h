#ifndef VEHICLEDEEDIMPLEMENTATION_H_
#define VEHICLEDEEDIMPLEMENTATION_H_

#include "../../../player/Player.h"
#include "../../../../packets.h"

#include "../DeedObject.h"
#include "../DeedObjectImplementation.h"

class DeedObject;
class TangibleObject;
class MountCreature;
class Player;
class CreatureObject;

class VehicleDeedImplementation : public VehicleDeedServant {
protected:
	String vehicleFile;
	int hitPoints;
public:
	static const int ORE = 1;
	static const int MOISTURE = 2;
	static const int LIQUID = 3;
	static const int GAS = 4;
	static const int FLORA = 5;
	static const int CREATURE = 6;

public:

	VehicleDeedImplementation(CreatureObject* creature, uint32 tempcrc, const UnicodeString& n, const String& tempn);
	VehicleDeedImplementation(uint64 objid, uint32 tempcrc, const UnicodeString& n, const String& tempn);
	~VehicleDeedImplementation();

	void init();

	int useObject(Player* player);

	void sendRadialResponseTo(Player* player, ObjectMenuResponse* omr);

	void updateCraftingValues(DraftSchematic* draftSchematic);

	void addAttributes(AttributeListMessage* alm);

	void parseItemAttributes();

	void setHitPoints(int hp){
		hitPoints = hp;
		String name = "hit_points"; //obj_attr_n.stf
		itemAttributes->setFloatAttribute(name, hp);
	}

	int getHitPoints(){
		return hitPoints;
	}

	//void sendTo(Player* player, MountCreature* swoop, bool doClose);

	//inline VehicleDeed* deploy() {
	//	return (VehicleDeed*) SceneObjectImplementation::deploy();
	//}
private:

};

#endif /*VEHICLEDEEDIMPLEMENTATION_H_*/

