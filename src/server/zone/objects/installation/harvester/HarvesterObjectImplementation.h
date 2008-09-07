#ifndef HARVESTEROBJECTIMPLEMENTATION_H_
#define HARVESTEROBJECTIMPLEMENTATION_H_

#include "engine/engine.h"

#include "../../../../db/ServerDatabase.h"

//#include "../../../objects.h"

class Zone;
class Player;
class DeedObject;
class InstallationObject;

#include "HarvesterObject.h"

class HarvesterObjectImplementation : public HarvesterObjectServant {
protected:
	uint64 activeResourceID;

	int harvesterType;
	int hopperSize;

	bool operating;

	float capacity;
	float specRate;
	float actualRate;
	float totalHopperQuantity;

	string temp;


public:

public:
	HarvesterObjectImplementation(uint64 oid);
	HarvesterObjectImplementation(uint64 oid, DeedObject * deed);
	~HarvesterObjectImplementation();

	void initialize();

	void insertToZone(Zone* zone);

	void sendTo(Player* player, bool doClose = true);

	void sendRadialResponseTo(Player* player, ObjectMenuResponse* omr);

	int getAvailableResourcesCount();

	void update();

	inline uint64 getActiveResourceID(){
		return activeResourceID;
	}



	inline bool isOperating(){
		return operating;
	}

	inline float getCapacity() {
		return capacity;
	}
	inline float getSpecRate() {
		return specRate;
	}
	inline float getActualRate() {
		return actualRate;
	}
	inline float getTotalHopperQuantity() {
		return totalHopperQuantity;
	}
	inline int getHopperSize() {
		return hopperSize;
	}

	//inline HarvesterObject* deploy() {
	//	return (HarvesterObject*) SceneObjectImplementation::deploy();
	//}
};

#endif /*HARVESTEROBJECTIMPLEMENTATION_H_*/
