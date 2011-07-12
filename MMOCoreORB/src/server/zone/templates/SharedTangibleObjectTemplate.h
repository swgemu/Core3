 /*
 * SharedTangibleObjectTemplate.h
 *
 *  Created on: 30/04/2010
 *      Author: victor
 */

#ifndef SHAREDTANGIBLEOBJECTTEMPLATE_H_
#define SHAREDTANGIBLEOBJECTTEMPLATE_H_

#include "server/zone/objects/draftschematic/resourceweight/ResourceWeight.h"

#include "SharedObjectTemplate.h"

class StructureFootprint;

class SharedTangibleObjectTemplate : public SharedObjectTemplate {
protected:
	/*PaletteColorCustomizationVariables paletteColorCustomizationVariables;
	RangedIntCustomizationVariables rangedIntCustomizationVariables;

	SocketDestinations socketDestinations;*/

	Reference<StructureFootprint*> structureFootprint;

	BoolParam targetable;

	uint16 playerUseMask;

	int level;

	Vector<String> certificationsRequired;

	int maxCondition;

	uint32 optionsBitmask;
	uint32 pvpStatusBitmask;

	int useCount;

	bool sliceable;

	Vector<short>* numberExperimentalProperties;
	Vector<String>* experimentalProperties;
	Vector<short>* experimentalWeights;
	Vector<String>* experimentalGroupTitles;
	Vector<String>* experimentalSubGroupTitles;
	Vector<int>* experimentalMin;
	Vector<int>* experimentalMax;
	Vector<short>* experimentalPrecision;

	Vector<Reference<ResourceWeight* > >* resourceWeights;
	//CustomizationVariableMapping customizationVariableMapping;

public:
	SharedTangibleObjectTemplate();

	~SharedTangibleObjectTemplate();

	void readObject(LuaObject* templateData);
	void readObject(IffStream* iffStream);

	void parseFileData(IffStream* str);

	void parseVariableData(const String& varName, Chunk* data);
	void parseVariableData(const String& varName, LuaObject* data);

	inline int getMaxCondition() const {
		return maxCondition;
	}

	inline uint32 getOptionsBitmask() const {
		return optionsBitmask;
	}

	inline uint32 getPvpStatusBitmask() const {
		return pvpStatusBitmask;
	}

	void setMaxCondition(int maxCondition) {
		this->maxCondition = maxCondition;
	}

	void setOptionsBitmask(uint32 optionsBitmask) {
		this->optionsBitmask = optionsBitmask;
	}

	void setPvpStatusBitmask(uint32 pvpStatusBitmask) {
		this->pvpStatusBitmask = pvpStatusBitmask;
	}

	inline Vector<String> getCertificationsRequired() const {
		return certificationsRequired;
	}

	inline int getLevel() const {
		return level;
	}

	inline int getUseCount() const {
		return useCount;
	}

    inline uint16 getPlayerUseMask() const {
		return playerUseMask;
	}

	inline StructureFootprint* getStructureFootprint() const {
		return structureFootprint;
	}

	inline bool getTargetable() const {
		return targetable;
	}

	void setCertificationsRequired(Vector<String> certificationsRequired) {
		this->certificationsRequired = certificationsRequired;
	}

	void setPlayerUseMask(uint16 playerUseMask) {
		this->playerUseMask = playerUseMask;
	}

	void setTargetable(bool targetable) {
		this->targetable = targetable;
	}

	inline bool getSliceable() const {
		return sliceable;
	}

    Vector<short >* getNumberExperimentalProperties() {
        return numberExperimentalProperties;
    }

    Vector<String>* getExperimentalProperties() {
        return experimentalProperties;
    }

    Vector<short >* getExperimentalWeights() {
        return experimentalWeights;
    }

    Vector<String>* getExperimentalGroupTitles() {
        return experimentalGroupTitles;
    }

    Vector<String>* getExperimentalSubGroupTitles() {
        return experimentalSubGroupTitles;
    }

    Vector<int>* getExperimentalMin() {
        return experimentalMin;
    }

    Vector<int>* getExperimentalMax() {
        return experimentalMax;
    }

    Vector<short >* getExperimentalPrecision() {
        return experimentalPrecision;
    }

    void addResourceWeight(ResourceWeight* weight) {
		resourceWeights->add(weight);
	}

    Vector<Reference<ResourceWeight* > >* getResourceWeights() {
    	return resourceWeights;
    }
};



#endif /* SHAREDTANGIBLEOBJECTTEMPLATE_H_ */
