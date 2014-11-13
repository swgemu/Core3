/**
 * Droid Module Armor Template
 * 11/11/2014
 */
#ifndef DROIDARMORMODULETEMPLATE_H_
#define DROIDARMORMODULETEMPLATE_H_
#include "server/zone/templates/SharedTangibleObjectTemplate.h"

class DroidArmorModuleTemplate : public SharedTangibleObjectTemplate {

protected:
	int moduleLevel;
public:
	DroidArmorModuleTemplate()  {}
	~DroidArmorModuleTemplate() {}
	void readObject(LuaObject* templateData) {
		SharedTangibleObjectTemplate::readObject(templateData);
		moduleLevel = templateData->getIntField("moduleLevel");
	}
	int getModuleLevel() {
		return moduleLevel;
	}
	 bool isDroidArmorModuleTemplate() {
		 return true;
	 }
};
#endif /*DROIDARMORMODULETEMPLATE_H_*/
