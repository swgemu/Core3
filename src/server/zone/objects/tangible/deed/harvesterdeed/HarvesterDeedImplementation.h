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
	int type, size, lotSize;

	float maintenanceRate, extractionRate, powerRate, hopperSize;
	uint32 surplusMaintenance, surplusPower;
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

	HarvesterDeedImplementation(CreatureObject* creature, uint32 tempcrc, const UnicodeString& n, const String& tempn);
	HarvesterDeedImplementation(uint64 objid, uint32 tempcrc, const UnicodeString& n, const String& tempn);
	HarvesterDeedImplementation(CreatureObject* creature, HarvesterObject* hino);
	~HarvesterDeedImplementation();

	void initType();
	void initSize();
	int getSize() {
		return size;
	}

	void parseItemAttributes();
	void addAttributes(AttributeListMessage* alm);

	// Attribute Setters
	inline void setSurplusMaintenance(uint32 maint) {
		surplusMaintenance = maint;
		String attr("surplusMaintenance");
		itemAttributes->setIntAttribute(attr, (int)surplusMaintenance);
	}
	inline void setMaintenanceRate(float rate) {
		 maintenanceRate = rate;
		 String attr("maintenanceRate");
		 itemAttributes->setFloatAttribute(attr, (float)maintenanceRate);
	}
	inline void setPowerRate(float rate) {
		 powerRate = rate;
		 String attr("powerRate");
		 itemAttributes->setFloatAttribute(attr, (float)powerRate);
	}

	inline void setSurplusPower(uint32 pow) {
		surplusPower = pow;
		String attr("surplusPower");
		itemAttributes->setIntAttribute(attr, (int)surplusPower);
	}
	inline void setExtractionRate(float rate) {
		extractionRate = rate;
		String attr("extractionRate");
		itemAttributes->setFloatAttribute(attr, (float)extractionRate);
	}
	inline void setHopperSize(float size) {
		hopperSize = size;
		String attr("hopperSize");
		itemAttributes->setFloatAttribute(attr, (float)hopperSize);
	}
	inline void setLotSize(int size) {
		lotSize = size;
		String attr("lotSize");
		itemAttributes->setIntAttribute(attr, lotSize);
	}

	// Attribute Getters
	inline uint32 getSurplusMaintenance() {
		return surplusMaintenance;
	}
	inline float getMaintenanceRate() {
		return maintenanceRate;
	}
	inline float getPowerRate() {
		return powerRate;
	}
	inline uint32 getSurplusPower() {
		return surplusPower;
	}
	inline float getExtractionRate() {
		return extractionRate;
	}
	inline float getHopperSize() {
		return hopperSize;
	}
	inline int getLotSize() {
		return lotSize;
	}
private:
	void init();

};

#endif /*HARVESTERDEEDIMPLEMENTATION_H_*/
