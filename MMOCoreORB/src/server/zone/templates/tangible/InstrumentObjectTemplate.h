/*
 * InstrumentObjectTemplate.h
 *
 *  Created on: 22/09/2010
 *      Author: victor
 */

#ifndef INSTRUMENTOBJECTTEMPLATE_H_
#define INSTRUMENTOBJECTTEMPLATE_H_

#include "../SharedTangibleObjectTemplate.h"

class InstrumentObjectTemplate : public SharedTangibleObjectTemplate {
	int instrumentType;

public:
	InstrumentObjectTemplate() {
		instrumentType = 0;
	}

	void readObject(LuaObject* templateData) {
		SharedTangibleObjectTemplate::readObject(templateData);

		instrumentType = templateData->getIntField("instrumentType");
	}

	inline int getInstrumentType() {
		return instrumentType;
	}

	bool isInstrumentObjectTemplate() {
		return true;
	}
};


#endif /* INSTRUMENTOBJECTTEMPLATE_H_ */
