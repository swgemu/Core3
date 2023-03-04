 /*
 * SharedTangibleObjectTemplate.h
 *
 *  Created on: 30/04/2010
 *      Author: victor
 */

#ifndef SHAREDTANGIBLEOBJECTTEMPLATE_H_
#define SHAREDTANGIBLEOBJECTTEMPLATE_H_

#include "templates/crafting/resourceweight/ResourceWeight.h"

#include "templates/SharedObjectTemplate.h"

class StructureFootprint;

class SharedTangibleObjectTemplate : public SharedObjectTemplate {
protected:
	/*PaletteColorCustomizationVariables paletteColorCustomizationVariables;
	RangedIntCustomizationVariables rangedIntCustomizationVariables;

	SocketDestinations socketDestinations;*/

	Reference<const StructureFootprint*> structureFootprint;

	BoolParam targetable;

	uint16 playerUseMask;

	int level;

	Vector<String> certificationsRequired;

	int maxCondition;

	uint32 optionsBitmask;
	uint32 pvpStatusBitmask;

	int useCount;

	bool sliceable;

	bool jediRobe;

	bool invisible;

	unsigned int faction;

	int junkDealerNeeded;
	int junkValue;

	VectorMap<String, int> skillMods;

	Vector<short>* numberExperimentalProperties;
	Vector<String>* experimentalProperties;
	Vector<short>* experimentalWeights;
	Vector<String>* experimentalAttributes;
	Vector<String>* experimentalGroups;
	Vector<float>* experimentalMin;
	Vector<float>* experimentalMax;
	Vector<short>* experimentalPrecision;
	Vector<short>* experimentalCombineType;
	Vector<uint32>* playerRaces;

	Vector<Reference<ResourceWeight* > >* resourceWeights;
	//CustomizationVariableMapping customizationVariableMapping;

public:
	SharedTangibleObjectTemplate();

	~SharedTangibleObjectTemplate();

	void readObject(LuaObject* templateData) override;
	void readObject(IffStream* iffStream) override;

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

	inline const Vector<String>& getCertificationsRequired() const {
		return certificationsRequired;
	}

	inline int getLevel() const {
		return level;
	}

	inline bool isInvisible() const {
		return invisible;
	}

	inline int getUseCount() const {
		return useCount;
	}

	inline uint16 getPlayerUseMask() const {
		return playerUseMask;
	}

	inline unsigned int getFaction() const {
		return faction;
	}

	inline int getJunkDealerNeeded() const {
		return junkDealerNeeded;
	}

	inline int getJunkValue() const {
		return junkValue;
	}

	inline const StructureFootprint* getStructureFootprint() const {
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

	inline bool isJediRobe() const {
		return jediRobe;
	}

	void setJediRobe(bool jediRobe) {
		this->jediRobe = jediRobe;
	}

	const Vector<short >* getNumberExperimentalProperties() const {
		return numberExperimentalProperties;
	}

	const Vector<String>* getExperimentalProperties() const {
		return experimentalProperties;
	}

	const Vector<short >* getExperimentalWeights() const {
		return experimentalWeights;
	}

	const Vector<String>* getExperimentalGroups() const {
		return experimentalGroups;
	}

	const Vector<String>* getExperimentalAttributes() const {
		return experimentalAttributes;
	}

	const Vector<float>* getExperimentalMin() const {
		return experimentalMin;
	}

	const Vector<float>* getExperimentalMax() const {
		return experimentalMax;
	}

	const Vector<short >* getExperimentalPrecision() const {
		return experimentalPrecision;
	}

	const Vector<uint32>* getPlayerRaces() const {
		return playerRaces;
	}

	const Vector<Reference<ResourceWeight* > >* getResourceWeights() const {
		return resourceWeights;
	}

	const VectorMap<String, int>* getSkillMods() const {
		return &skillMods;
	}

	int getSkillMod(const String& mod) const {
		return skillMods.get(mod);
	}

	bool isSharedTangibleObjectTemplate() const override {
		return true;
	}
};



#endif /* SHAREDTANGIBLEOBJECTTEMPLATE_H_ */
