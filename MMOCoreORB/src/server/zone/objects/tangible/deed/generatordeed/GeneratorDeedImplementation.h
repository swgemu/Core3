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
	int type, lotSize;

	float maintenanceRate, extractionRate, hopperSize;
	uint32 surplusMaintenance;
public:
	static const int FUSION = 1;
	static const int PHOTOBIO = 2;
	static const int SOLAR = 3;
	static const int WIND = 4;

public:

	GeneratorDeedImplementation(CreatureObject* creature, uint32 tempcrc, const UnicodeString& n, const String& tempn);
	GeneratorDeedImplementation(uint64 objid, uint32 tempcrc, const UnicodeString& n, const String& tempn);
	~GeneratorDeedImplementation();

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

#endif /*GENERATORDEEDIMPLEMENTATION_H_*/
