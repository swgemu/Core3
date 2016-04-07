#ifndef XPPURCHASETEMPLATE_H
#define XPPURCHASETEMPLATE_H

#include "templates/SharedTangibleObjectTemplate.h"

class XpPurchaseTemplate: public SharedTangibleObjectTemplate {
protected:

	String requiredSkill;
	String xpType;
	String grantType, grantName;
	int xpAmount;
	bool noRemove;


public:
	XpPurchaseTemplate() {
		requiredSkill = "";
		xpType = "";
		grantType = "";
		grantName = "";
		xpAmount = 0;
		noRemove = false;

	}

	~XpPurchaseTemplate() {

	}

	void readObject(LuaObject* templateData) {
		SharedTangibleObjectTemplate::readObject(templateData);

		requiredSkill = templateData->getStringField("requiredSkill");
		grantType = templateData->getStringField("grantType");
		grantName = templateData->getStringField("grantName");
		xpType = templateData->getStringField("xpType");
		xpAmount = templateData->getIntField("xpAmount");
		noRemove = templateData->getBooleanField("noRemove");

	}

	const String& getRequiredSkill() {
		return requiredSkill;
	}

	const String& getGrantType() {
		return grantType;
	}

	const String& getGrantName() {
		return grantName;
	}

	const String& getXpType() {
		return xpType;
	}

	bool isNoRemove() {
		return noRemove;
	}

	int getXpAmount() {
		return xpAmount;
	}

};


#endif /* XPPURCHASETEMPLATE_H */
