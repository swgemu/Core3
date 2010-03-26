/*
 * SkillList.h
 *
 *  Created on: 28/12/2009
 *      Author: victor
 */

#ifndef SKILLLIST_H_
#define SKILLLIST_H_

#include "engine/engine.h"
#include "server/zone/objects/scene/variables/DeltaVector.h"

class Skill;

class SkillList : public DeltaVector<Skill*> {
public:
	bool add(Skill* element, DeltaMessage* message = NULL, int updates = 1);

	bool toString(String& str);
	bool parseFromString(const String& str, int version = 0);

	bool toBinaryStream(ObjectOutputStream* stream);
	bool parseFromBinaryStream(ObjectInputStream* stream);

	void getStringList(Vector<String>& skills);
	void loadFromNames(Vector<String>& skills);

	void insertToMessage(BaseMessage* msg);
};


#endif /* SKILLLIST_H_ */
