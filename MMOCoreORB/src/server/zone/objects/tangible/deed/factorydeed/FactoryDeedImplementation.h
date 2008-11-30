
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

	float maintenanceRate, hopperSize;
	uint32 surplusMaintenance, surplusPower;
public:
	static const int EQUIPMENT = 1;
	static const int FOOD = 2;
	static const int STRUCTURE = 3;
	static const int WEARABLES = 4;

public:

	FactoryDeedImplementation(CreatureObject* creature, uint32 tempcrc, const UnicodeString& n, const String& tempn);
	FactoryDeedImplementation(uint64 objid, uint32 tempcrc, const UnicodeString& n, const String& tempn);
	~FactoryDeedImplementation();

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

	// Attribute Getters
	inline uint32 getSurplusMaintenance() {
		return surplusMaintenance;
	}
	inline float getMaintenanceRate() {
		return maintenanceRate;
	}
	inline uint32 getSurplusPower() {
		return surplusPower;
	}
	inline float getHopperSize() {
		return hopperSize;
	}
private:
	void init();
};

#endif /*FACTORYDEEDIMPLEMENTATION_H_*/
