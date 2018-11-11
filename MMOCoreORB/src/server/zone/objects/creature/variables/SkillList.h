/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef SKILLBOXLIST_H_
#define SKILLBOXLIST_H_

#include "engine/engine.h"
#include "engine/util/json_utils.h"

#include "server/zone/objects/scene/variables/DeltaVector.h"

class Skill;

class SkillList : public DeltaVector<Reference<Skill*> > {
public:
	bool add(Skill* skill, DeltaMessage* message = NULL);
	void remove(Skill* skill, DeltaMessage* message = NULL);

	bool containsSkill(const String& skill);

	bool toBinaryStream(ObjectOutputStream* stream);
	bool parseFromBinaryStream(ObjectInputStream* stream);

	void getStringList(Vector<String>& skills) const;
	void loadFromNames(Vector<String>& skills);

	void insertToMessage(BaseMessage* msg);

	friend void to_json(nlohmann::json& j, const SkillList& s);
};

#endif /*SKILLBOXLIST_H_*/
