/*
 * InstrumentObjectTemplate.h
 *
 *  Created on: 22/09/2010
 *      Author: victor
 */

#ifndef INSTRUMENTOBJECTTEMPLATE_H_
#define INSTRUMENTOBJECTTEMPLATE_H_

#include "templates/SharedTangibleObjectTemplate.h"

class InstrumentObjectTemplate : public SharedTangibleObjectTemplate {
	int instrumentType;

public:
	InstrumentObjectTemplate() {
		instrumentType = 0;
	}

	void readObject(LuaObject* templateData) override {
		SharedTangibleObjectTemplate::readObject(templateData);

		instrumentType = templateData->getIntField("instrumentType");
	}

	inline int getInstrumentType() const {
		return instrumentType;
	}

	bool isInstrumentObjectTemplate() const override {
		return true;
	}
};


#endif /* INSTRUMENTOBJECTTEMPLATE_H_ */
