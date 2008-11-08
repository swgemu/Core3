#ifndef HARVESTEROBJECTIMPLEMENTATION_H_
#define HARVESTEROBJECTIMPLEMENTATION_H_

#include "engine/engine.h"

#include "../../../../db/ServerDatabase.h"

//#include "../../../objects.h"

class Zone;
class Player;
class DeedObject;
class HarvesterDeed;
class InstallationObject;

#include "HarvesterObject.h"

class HarvesterObjectImplementation : public HarvesterObjectServant {
protected:

	int harvesterType;

	uint64 activeResourceID;
	uint64 activeSpawnID;
	int spawnDensity;
	Time spawnExpireTimestamp;

	Time resourceHopperTimestamp;
	VectorMap<uint64, float> resourceHopper; // ID + Size
	uint32 hopperResourceUpdateCounter;

	float hopperSizeMax;
	float extractionRate; // BER

public:
	HarvesterObjectImplementation(uint64 oid);
	HarvesterObjectImplementation(uint64 oid, HarvesterDeed *deed);
	~HarvesterObjectImplementation();

	void parseItemAttributes();

	// Attribute Setters
	inline void setHopperSizeMax(float size) {
		hopperSizeMax = size;
		string attr("hopperSizeMax");
		itemAttributes->setFloatAttribute(attr, (float)hopperSizeMax);
	}
	inline void setExtractionRate(float rate) {
		extractionRate = rate;
		string attr("extractionRate");
		itemAttributes->setFloatAttribute(attr, (float)extractionRate);
	}
	inline void setActiveResourceID(uint64 rid) {
		activeResourceID = rid;
		string attr("activeResourceID");
		itemAttributes->setUnsignedLongAttribute(attr, activeResourceID);
	}
	inline void setActiveSpawnID(uint64 sid) {
		activeSpawnID = sid;
		string attr("activeSpawnID");
		itemAttributes->setUnsignedLongAttribute(attr, activeSpawnID);
	}
	inline void setSpawnExpireTimestamp(uint32 ts) {
		Time stamp(ts);
		spawnExpireTimestamp = stamp;
		string attr("spawnExpireTimestamp");
		itemAttributes->setUnsignedLongAttribute(attr, ts);
	}
	inline void setResourceHopperTimestamp(uint32 ts) {
		Time stamp(ts);
		resourceHopperTimestamp = stamp;
		string attr("resourceHopperTimestamp");
		itemAttributes->setUnsignedLongAttribute(attr, ts);
	}
	inline void setSpawnDensity(int dens) {
		spawnDensity = dens;
		string attr("spawnDensity");
		itemAttributes->setIntAttribute(attr, dens);
	}


	// Attribute Getters
	inline float getHopperSizeMax() {
		return hopperSizeMax;
	}
	inline float getExtractionRate() {
		return extractionRate;
	}
	inline uint64 getActiveResourceID(){
		return activeResourceID;
	}
	inline uint64 getActiveSpawnID(){
		return activeSpawnID;
	}
	inline uint32 getSpawnExpireTimestamp() {
		return spawnExpireTimestamp.getTime();
	}
	inline uint32 getResourceHopperTimestamp() {
		return resourceHopperTimestamp.getTime();
	}
	inline int getSpawnDensity() {
		return spawnDensity;
	}


	// Updaters
	void changeActiveResourceID(uint64 oid);

	// Other Operational Methods
	void serializeResourceHopper();
	void unserializeResourceHopper(const string& hopper);
	int getHarvesterType();
	inline void setHarvesterType(int type) {
		harvesterType = type;
	}

	void updateOperators();
	void verifyOperators();

	// Harvester Operation

	void updateHopper();
	void updateOperatorsAddBlankActiveRescource();
	void updateOperatorsEmptyHopper();
	float getActualRate();



	// Harvester Hopper
	inline float getHopperSize() {
		float hopperSize = 0.0f;

		for (int i = 0; i < resourceHopper.size(); i++) {
			hopperSize += resourceHopper.get(i);
		}

		return hopperSize;
	}

	inline int getHopperItemCount() {
		return resourceHopper.size();
	}

	inline uint64 getHopperItemID(int index) {
		if(index < resourceHopper.size() && resourceHopper.size() >= 1) {
			VectorMapEntry<uint64, float>* entry = ((SortedVector<VectorMapEntry<uint64, float>*>*)&resourceHopper)->get(index);
			return entry->getKey();
		} else
		{
			return 0;
		}
	}
	inline float getHopperItemQuantity(int index) {
		if(index < resourceHopper.size() && resourceHopper.size() >= 1) {
			VectorMapEntry<uint64, float>* entry = ((SortedVector<VectorMapEntry<uint64, float>*>*)&resourceHopper)->get(index);
			return entry->getValue();
		} else {
			return 0.0f;
		}
	}
	inline float getHopperItemQuantity(uint64 rid) {
		if(resourceHopper.contains(rid))
			return resourceHopper.get(rid);
		else
			return 0.0f;
	}
	inline void setHopperUpdateCounter(uint32 counter) {
		hopperResourceUpdateCounter = counter;
	}
	inline uint32 getHopperUpdateCounter() {
		return hopperResourceUpdateCounter;
	}
	inline uint32 getNewHopperUpdateCounter(uint32 update) {
		hopperResourceUpdateCounter += update;
		return hopperResourceUpdateCounter;
	}
	inline float removeHopperItem(uint64 rid, uint32 quantity) {
		if(!resourceHopper.contains(rid))
			return 0.0f;

		float hopperQuantity = resourceHopper.get(rid);
		if((int)hopperQuantity < quantity)
			quantity = (int)hopperQuantity;

		resourceHopper.drop(rid);
		resourceHopper.put(rid, hopperQuantity - quantity); // update quantity

		return quantity;
	}

private:
	void init();
};

#endif /*HARVESTEROBJECTIMPLEMENTATION_H_*/
