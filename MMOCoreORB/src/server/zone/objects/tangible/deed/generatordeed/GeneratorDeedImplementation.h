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

	float maintenanceRate, extractionRate, hopperSize;
	uint32 surplusMaintenance;
public:
	static const int FUSION = 1;
	static const int PHOTOBIO = 2;
	static const int SOLAR = 3;
	static const int WIND = 4;

public:

	GeneratorDeedImplementation(CreatureObject* creature, uint32 tempcrc, const unicode& n, const string& tempn);
	GeneratorDeedImplementation(uint64 objid, uint32 tempcrc, const unicode& n, const string& tempn);
	~GeneratorDeedImplementation();

	void parseItemAttributes();
	void addAttributes(AttributeListMessage* alm);

	// Attribute Setters
	inline void setSurplusMaintenance(uint32 maint) {
		surplusMaintenance = maint;
		string attr("surplusMaintenance");
		itemAttributes->setIntAttribute(attr, (int)surplusMaintenance);
	}
	inline void setMaintenanceRate(float rate) {
		 maintenanceRate = rate;
		 string attr("maintenanceRate");
		 itemAttributes->setFloatAttribute(attr, (float)maintenanceRate);
	}
	inline void setExtractionRate(float rate) {
		extractionRate = rate;
		string attr("extractionRate");
		itemAttributes->setFloatAttribute(attr, (float)extractionRate);
	}
	inline void setHopperSize(float size) {
		hopperSize = size;
		string attr("hopperSize");
		itemAttributes->setFloatAttribute(attr, (float)hopperSize);
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
private:
	void init();
};

#endif /*GENERATORDEEDIMPLEMENTATION_H_*/
