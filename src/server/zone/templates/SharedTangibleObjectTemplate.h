 /*
 * SharedTangibleObjectTemplate.h
 *
 *  Created on: 30/04/2010
 *      Author: victor
 */

#ifndef SHAREDTANGIBLEOBJECTTEMPLATE_H_
#define SHAREDTANGIBLEOBJECTTEMPLATE_H_

#include "SharedObjectTemplate.h"

class SharedTangibleObjectTemplate : public SharedObjectTemplate {
protected:
	/*PaletteColorCustomizationVariables paletteColorCustomizationVariables;
	RangedIntCustomizationVariables rangedIntCustomizationVariables;

	SocketDestinations socketDestinations;*/

	String structureFootprintFileName;

	bool useStructureFootprintOutline;
	bool targetable;

	uint16 playerUseMask;

	int level;

	Vector<String> certificationsRequired;

	int maxCondition;

	uint32 optionsBitmask;
	uint32 pvpStatusBitmask;

	int useCount;

	bool sliceable;

	//CustomizationVariableMapping customizationVariableMapping;

public:
	SharedTangibleObjectTemplate() {

	}

	~SharedTangibleObjectTemplate() {

	}

	void readObject(LuaObject* templateData);

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

	inline String getStructureFootprintFileName() const {
		return structureFootprintFileName;
	}

	inline bool getTargetable() const {
		return targetable;
	}

	inline bool getUseStructureFootprintOutline() const {
		return useStructureFootprintOutline;
	}

	void setCertificationsRequired(Vector<String> certificationsRequired) {
		this->certificationsRequired = certificationsRequired;
	}

	void setPlayerUseMask(uint16 playerUseMask) {
		this->playerUseMask = playerUseMask;
	}

	void setStructureFootprintFileName(String structureFootprintFileName) {
		this->structureFootprintFileName = structureFootprintFileName;
	}

	void setTargetable(bool targetable) {
		this->targetable = targetable;
	}

	void setUseStructureFootprintOutline(bool useStructureFootprintOutline) {
		this->useStructureFootprintOutline = useStructureFootprintOutline;
	}

	inline bool getSliceable() const {
		return sliceable;
	}

};



#endif /* SHAREDTANGIBLEOBJECTTEMPLATE_H_ */
