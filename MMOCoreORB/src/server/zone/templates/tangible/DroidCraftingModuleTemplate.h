/*
 * DroidCraftingModuleTemplate.h
 *
 *  Created on: 2/7/2013
 *      Author: Klivian
 */

#ifndef DROIDCRAFTINGMODULETEMPLATE_H_
#define DROIDCRAFTINGMODULETEMPLATE_H_

#include "../SharedTangibleObjectTemplate.h"

class DroidCraftingModuleTemplate : public SharedTangibleObjectTemplate {
	int craftingType;
	String craftingStationTemplate;
	String attributeListString;

public:
	DroidCraftingModuleTemplate() {

	}

	~DroidCraftingModuleTemplate() {

	}

	void readObject(LuaObject* templateData) {
		SharedTangibleObjectTemplate::readObject(templateData);

		craftingType = templateData->getIntField("craftingType");
		craftingStationTemplate = templateData->getStringField("craftingStationTemplate");
		attributeListString = templateData->getStringField("attributeListString");

    }

    inline int getCraftingType() const {
		return craftingType;
	}

    inline String& getCraftingStationTemplate() {
		return craftingStationTemplate;
	}

    inline String& getAttributeListString() {
    		return attributeListString;
	}

	bool isDroidCraftingModuleTemplate() {
		return true;
	}

};


#endif /* DROIDCRAFTINGMODULETEMPLATE_H_ */
