/*
 * DiceTemplate.h
 *
 *  Created on: March 16, 2012
 *      Author: kyle
 */

#ifndef DICETEMPLATE_H_
#define DICETEMPLATE_H_

#include "templates/SharedTangibleObjectTemplate.h"

class DiceTemplate: public SharedTangibleObjectTemplate {
protected:

	int sides;
	String sidesText;
	String selfSingleResult;
	String othersSingleResult;
	String selfManyResult;
	String othersManyResult;

public:
	DiceTemplate() {
		sides = 0;
		sidesText = "";
		selfSingleResult = "";
		othersSingleResult = "";
		selfManyResult = "";
		othersManyResult = "";
	}

	~DiceTemplate() {

	}

	void readObject(LuaObject* templateData) {
		SharedTangibleObjectTemplate::readObject(templateData);
		sides = templateData->getIntField("sides");
		selfSingleResult = templateData->getStringField("selfSingleResult");
		othersSingleResult = templateData->getStringField("othersSingleResult");
		sidesText = templateData->getStringField("sidesText");
		selfManyResult = templateData->getStringField("selfManyResult");
		othersManyResult = templateData->getStringField("othersManyResult");

	}

	int getSides() {
		return sides;
	}

	String getSidesText() {
		return sidesText;
	}

	String getSelfSingleResult() {
		return selfSingleResult;
	}

	String getOthersSingleResult() {
		return othersSingleResult;
	}

	bool isDiceTemplate() {
		return true;
	}

	bool isChanceCube() {
		return sidesText == "chance cube";
	}

	bool isConfigurable() {
		return sidesText == "configurable dice";
	}

};

#endif /* DICETEMPLATE_H_ */
