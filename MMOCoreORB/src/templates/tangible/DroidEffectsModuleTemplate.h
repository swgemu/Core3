/**
 * Droid Module Effects Template
 * 11/26/2014
 */

#ifndef DROIDEFFECTSMODULETEMPLATE_H_
#define DROIDEFFECTSMODULETEMPLATE_H_

#include "templates/SharedTangibleObjectTemplate.h"

class DroidEffectsModuleTemplate : public SharedTangibleObjectTemplate {

protected:
	String effectName;
	String animation;

public:
	DroidEffectsModuleTemplate()  {}
	~DroidEffectsModuleTemplate() {}

	void readObject(LuaObject* templateData) {
		SharedTangibleObjectTemplate::readObject(templateData);
		effectName = templateData->getStringField("effectName");
		animation = templateData->getStringField("animation");
	}

	String& getEffectName() {
		return effectName;
	}

	String& getAnimation() {
		return animation;
	}

	 bool isDroidEffectsModuleTemplate() {
		 return true;
	 }
};

#endif /*DROIDEFFECTSMODULETEMPLATE_H_*/
