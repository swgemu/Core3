/*
 * Skill.h
 *
 *  Created on: 28/12/2009
 *      Author: victor
 */

#ifndef SKILL_H_
#define SKILL_H_

#include "engine/engine.h"

class Skill : public Object {
protected:
	String name;

	int skillType;

public:
	const static int CERTIFICATION = 1;
	const static int QUEUECOMMAND = 2;
	const static int SKILLBOX = 3;
	const static int PROFESSION = 4;

	Skill(const String& Name) {
		name = Name;

		skillType = 0;
	}

	virtual ~Skill() {

	}

	int compareTo(Skill* command) {
		return this->name.compareTo(command->name);
	}

	inline String& getName() {
		return name;
	}

	inline bool isCertification() {
		return skillType == CERTIFICATION;
	}

	inline bool isQueueCommand() {
		return skillType == QUEUECOMMAND;
	}

	inline bool isProfession() {
		return skillType == PROFESSION;
	}

	inline bool isSkillBox() {
		return skillType == SKILLBOX;
	}
};

#endif /* SKILL_H_ */
