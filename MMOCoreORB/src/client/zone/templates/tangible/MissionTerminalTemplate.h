/*
 * MissionTerminalTemplate.h
 *
 *  Created on: 21/06/2010
 *      Author: victor
 */

#ifndef MISSIONTERMINALTEMPLATE_H_
#define MISSIONTERMINALTEMPLATE_H_

#include "../SharedTangibleObjectTemplate.h"

class MissionTerminalTemplate : public SharedTangibleObjectTemplate {
	String missionTerminalType;

public:
	MissionTerminalTemplate() {
	}

	~MissionTerminalTemplate() {
	}

	void readObject(LuaObject* templateData) {
		SharedTangibleObjectTemplate::readObject(templateData);

		missionTerminalType = templateData->getStringField("missionTerminalType");
    }

	inline String& getMissionTerminalType() {
		return missionTerminalType;
	}

	bool isMissionTerminalTemplate() {
		return true;
	}
};


#endif /* MISSIONTERMINALTEMPLATE_H_ */
