
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
	int type, lotSize;

	float maintenanceRate, hopperSize, buildRate, powerRate;
	uint32 surplusMaintenance, surplusPower;
public:
	static const int EQUIPMENT = 1;
	static const int FOOD = 2;
	static const int STRUCTURE = 3;
	static const int WEARABLES = 4;

public:

	FactoryDeedImplementation(CreatureObject* creature, uint32 tempcrc, const UnicodeString& n, const String& tempn);
	FactoryDeedImplementation(uint64 objid, uint32 tempcrc, const UnicodeString& n, const String& tempn);
	FactoryDeedImplementation(CreatureObject* creature, FactoryObject* fact);
	~FactoryDeedImplementation();

	void parseItemAttributes();
	void addAttributes(AttributeListMessage* alm);
	void updateCraftingValues(DraftSchematic* draftSchematic);

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
	inline void setBuildRate(float rate) {
		buildRate = rate;
		String attr("buildRate");
		itemAttributes->setFloatAttribute(attr, (float)buildRate);
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
	inline float getHopperSize() {
		return hopperSize;
	}
	inline int getLotSize() {
		return lotSize;
	}
	inline float getBuildRate() {
		return buildRate;
	}
private:
	void init();
};

#endif /*FACTORYDEEDIMPLEMENTATION_H_*/
