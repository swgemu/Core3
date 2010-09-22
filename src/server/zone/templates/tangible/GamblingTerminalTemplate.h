/*
 * GamblingTerminalTemplate.h
 *
 *  Created on: May 7, 2010
 *      Author: swgemu
 */

#ifndef GAMBLINGTERMINALTEMPLATE_H_
#define GAMBLINGTERMINALTEMPLATE_H_

#include "../SharedTangibleObjectTemplate.h"

class GamblingTerminalTemplate : public SharedTangibleObjectTemplate {
	int machineType;

public:
	GamblingTerminalTemplate() {

	}

	~GamblingTerminalTemplate() {

	}

	void readObject(LuaObject* templateData) {
		SharedTangibleObjectTemplate::readObject(templateData);

		machineType = templateData->getIntField("machineType");
    }

    inline int getMachineType() const {
        return machineType;
    }

    void setMachineType(int machineType) {
    	this->machineType = machineType;
    }

	bool isGamblingTerminalTemplate() {
		return true;
	}
};



#endif /* GAMBLINGTERMINALTEMPLATE_H_ */
