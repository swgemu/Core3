/*
 * Skill.h
 *
 *  Created on: 28/12/2009
 *      Author: victor
 */

#ifndef SKILL_H_
#define SKILL_H_

#include "engine/engine.h"

class Skill {
protected:
	String name;

	int type;

public:
	const static int CERTIFICATION = 1;
	const static int QUEUECOMMAND = 2;

	Skill(const String& Name) {
		name = Name;

		type = 0;
	}

	virtual ~Skill() {

	}

	inline String& getName() {
		return name;
	}

	inline bool isCertification() {
		return type == CERTIFICATION;
	}

	inline bool isQueueCommand() {
		return type == QUEUECOMMAND;
	}
};

#endif /* SKILL_H_ */
