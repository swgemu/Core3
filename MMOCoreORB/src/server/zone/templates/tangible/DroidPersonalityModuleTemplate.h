/**
 * Droid Module Effects Template
 * 11/26/2014
 */
#ifndef DROIDPERSONALITYMODULETEMPLATE_H_
#define DROIDPERSONALITYMODULETEMPLATE_H_
#include "server/zone/templates/SharedTangibleObjectTemplate.h"
class DroidPersonalityModuleTemplate : public SharedTangibleObjectTemplate {

protected:
	String reactionName;
public:
	DroidPersonalityModuleTemplate()  {}
	~DroidPersonalityModuleTemplate() {}
	void readObject(LuaObject* templateData) {
		SharedTangibleObjectTemplate::readObject(templateData);
		reactionName = templateData->getStringField("reactionName");
	}

	String& getReactionName() {
		return reactionName;
	}

	 bool isDroidPersonalityModuleTemplate() {
		 return true;
	 }
};
#endif /*DROIDPERSONALITYMODULETEMPLATE_H_*/
