/*
 * SuiBoxImplementation.cpp
 *
 *  Created on: 30/01/2010
 *      Author: victor
 */

#include "server/zone/objects/player/sui/SuiBox.h"
#include "server/zone/packets/ui/SuiCreatePageMessage.h"
#include "server/zone/packets/ui/SuiForceClosePage.h"
#include "server/zone/objects/scene/SceneObject.h"

void SuiBoxImplementation::generateHeader(SuiCreatePageMessage* message) {
	//[UI DECLARATION HEADER]
	String hdrVar = "";
	String hdrType = "";

	//The header needs to be repeated twice. (Why SOE?)
	for (int i = 0; i < 2; ++i) {
		message->insertByte(5); //# of vars to follow, not inc strings
		message->insertInt(0);
		message->insertInt(3+hdrOptCount); //# of shorts (inc ascii string size shorts), excluding the counter
		message->insertShort(0); // 1
		message->insertShort(1); // 2
		message->insertByte(9 + i); //counter

		message->insertAscii(handlerStr);

		for(int k = 0; k < headerSets.size(); k++) {
			StringTokenizer hdrTok(headerSets.get(k)); //ex. List.lstList~SelectedRow
			hdrTok.setDelimeter("~"); //Split & parse
			hdrTok.getStringToken(hdrVar);
			hdrTok.getStringToken(hdrType);
			message->insertHeaderOption(hdrVar, hdrType);//, (i->0));
		}
	}
}

void SuiBoxImplementation::generateBody(SuiCreatePageMessage* message) {
	//[UI BODY]
	String bdyTypeStr = "";
	int bdyType = 0;
	String bdyVar = "";
	String bdySetting = "";
	String bdyValue = "";

	for(int k = 0; k < optionSets.size(); ++k) {
		StringTokenizer bdyTok(optionSets.get(k)); //ex. 3~Prompt.lblTitle~Text~LOL

		bdyTok.setDelimeter("~"); //Split & parse
		bdyTok.getStringToken(bdyTypeStr);

		bdyType = Integer::valueOf(bdyTypeStr);

		bdyTok.getStringToken(bdyVar);

		if((bdyType == 3) || (bdyType == 4)) {
			bdyTok.getStringToken(bdySetting);
			bdyTok.getStringToken(bdyValue);
		}

		message->insertOption(bdyType, bdyValue, bdyVar, bdySetting);
	}
}

BaseMessage* SuiBoxImplementation::generateCloseMessage() {
	SuiForceClosePage* msg = new SuiForceClosePage(boxID);
	clearOptions();
	return msg;
}

void SuiBoxImplementation::addSetting(const String& optType, const String& variable, const String& setting, const String& value) {
	String setName = "", setVal = "";
	setName = setting;
	setVal = value;

	//These checks and settings ensure parsing of the optStr wont screw up in generateBody()
	if ((variable.length() == 0) || (optType.length() == 0))
		return;

	if (setName.length() == 0)
		setName = " ";

	if (setVal.length() == 0)
		setVal = " ";

	String optStr = "";
	int optTypeInt = 0;
	optStr+=(optType+"~"+variable);
	optTypeInt = Integer::valueOf(optType);

	//OptionType 3 & 4 have variable settings and values (see documentation for packet)
	if((optTypeInt == 3) || (optTypeInt == 4)) {
		optStr+=("~"+setName+"~"+setVal);
	}

	// Insert the option into the list:
	optionSets.add(optStr);
}

void SuiBoxImplementation::addHeader(const String& variable, const String& type) {
	if((variable.length() == 0) || (type.length() == 0))
		return;

	//Add's the header option to the list
	String headerStr = "";
	headerStr+=(variable+"~"+type);
	headerSets.add(headerStr);

	//The header count increases by 2. 1 for the variable name, 1 for the data type.
	hdrOptCount+=2;
}

void SuiBoxImplementation::generateFooter(SuiCreatePageMessage* message, int type) {
	ManagedReference<SceneObject*> usingObject = this->usingObject.get();
	if(usingObject != NULL)
		message->insertFooter(usingObject->getObjectID(), forceCloseDistance, type);
	else
		message->insertFooter(0, 0, type);
}

void SuiBoxImplementation::setCancelButton(bool value, const String& cancelText) {
	if(cancelText.length() > 0)
		cancelButtonText = cancelText;

	cancelButton = value;
}

void SuiBoxImplementation::setOtherButton(bool value, const String& backText) {
	if(backText.length() > 0)
		otherButtonText = backText;

	otherButton = value;
}

void SuiBoxImplementation::setOkButton(bool value, const String& okText) {
	if(okText.length() > 0)
		okButtonText = okText;

	okButton = value;
}

void SuiBoxImplementation::setForceCloseDistance(float dist) {
	forceCloseDistance = dist;
}

void SuiBoxImplementation::setForceCloseDisabled() {
	forceCloseDistance = 0;
}

