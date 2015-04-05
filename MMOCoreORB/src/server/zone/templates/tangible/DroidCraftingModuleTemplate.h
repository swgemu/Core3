/**
 * Droid Module Crafting Template
 * 11/10/2014
 */
#ifndef DROIDCRAFTINGMODULETEMPLATE_H_
#define DROIDCRAFTINGMODULETEMPLATE_H_
#include "server/zone/templates/SharedTangibleObjectTemplate.h"
class DroidCraftingModuleTemplate : public SharedTangibleObjectTemplate {

protected:
	int craftingType;
	String craftingStationTemplate;
	String attributeListString;
public:
	DroidCraftingModuleTemplate() : craftingType(0) {

	}

	~DroidCraftingModuleTemplate() {

	}

	void readObject(LuaObject* templateData) {
		SharedTangibleObjectTemplate::readObject(templateData);
		craftingType = templateData->getIntField("craftingType");
		craftingStationTemplate = templateData->getStringField("craftingStationTemplate");
		attributeListString = templateData->getStringField("attributeListString");
	}

	int getCraftingType() {
		return craftingType;
	}

	String& getCraftingStationTemplate() {
		return craftingStationTemplate;
	}

	String& getAttributeListString() {
		return attributeListString;
	}

	bool isDroidCraftingModuleTemplate() {
		return true;
	}
};
#endif /*DROIDCRAFTINGMODULETEMPLATE_H_*/
