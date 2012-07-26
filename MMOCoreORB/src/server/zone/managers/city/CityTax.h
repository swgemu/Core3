/*
 * CityTax.h
 *
 *  Created on: Jul 25, 2012
 *      Author: swgemu
 */

#ifndef CITYTAX_H_
#define CITYTAX_H_

#include "engine/engine.h"

class CityTax : public Object {
	int minValue;
	int maxValue;

	String menuText;
	String inputTitle;
	String inputText;
	String statusPrompt;
	String systemMessage;
	String emailSubject;
	String emailBody;

public:
	CityTax() : Object(), minValue(0), maxValue(0) {
	}

	CityTax(const CityTax& tax) : Object() {
		minValue = tax.minValue;
		maxValue = tax.maxValue;
		menuText = tax.menuText;
		inputTitle = tax.inputTitle;
		inputText = tax.inputText;
		statusPrompt = tax.statusPrompt;
		systemMessage = tax.systemMessage;
		emailSubject = tax.emailSubject;
		emailBody = tax.emailBody;
	}

	CityTax& operator=(const CityTax& tax) {
		if (this == &tax)
			return *this;

		minValue = tax.minValue;
		maxValue = tax.maxValue;
		menuText = tax.menuText;
		inputTitle = tax.inputTitle;
		inputText = tax.inputText;
		statusPrompt = tax.statusPrompt;
		systemMessage = tax.systemMessage;
		emailSubject = tax.emailSubject;
		emailBody = tax.emailBody;

		return *this;
	}

	void readObject(LuaObject* luaObject) {
		minValue = luaObject->getIntField("min");
		maxValue = luaObject->getIntField("max");
		menuText = luaObject->getStringField("menuText");
		inputTitle = luaObject->getStringField("inputTitle");
		inputText = luaObject->getStringField("inputText");
		statusPrompt = luaObject->getStringField("statusPrompt");
		systemMessage = luaObject->getStringField("systemMessage");
		emailSubject = luaObject->getStringField("emailSubject");
		emailBody = luaObject->getStringField("emailBody");
	}

	inline int getMinValue() {
		return minValue;
	}

	inline int getMaxValue() {
		return maxValue;
	}

	inline String& getMenuText() {
		return menuText;
	}

	inline String& getInputTitle() {
		return inputTitle;
	}

	inline String& getInputText() {
		return inputText;
	}

	inline String& getStatusPrompt() {
		return statusPrompt;
	}

	inline String& getSystemMessage() {
		return systemMessage;
	}

	inline String& getEmailSubject() {
		return emailSubject;
	}

	inline String& getEmailBody() {
		return emailBody;
	}
};


#endif /* CITYTAX_H_ */
