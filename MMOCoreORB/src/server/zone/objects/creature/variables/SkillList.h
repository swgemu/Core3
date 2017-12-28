/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef SKILLBOXLIST_H_
#define SKILLBOXLIST_H_

#include <stddef.h>
#include <algorithm>

#include "engine/engine.h"
#include "server/zone/objects/scene/variables/DeltaVector.h"
#include "system/lang/String.h"
#include "system/lang/ref/Reference.h"

class DeltaMessage;
class Skill;
namespace engine {
namespace service {
namespace proto {
class BaseMessage;
}  // namespace proto
}  // namespace service
}  // namespace engine
namespace sys {
namespace io {
class ObjectInputStream;
class ObjectOutputStream;
}  // namespace io
namespace util {
template <class E> class Vector;
}  // namespace util
}  // namespace sys

class SkillList : public DeltaVector<Reference<Skill*> > {
public:
	bool add(Skill* skill, DeltaMessage* message = NULL);
	void remove(Skill* skill, DeltaMessage* message = NULL);

	bool containsSkill(const String& skill);

	bool toBinaryStream(ObjectOutputStream* stream);
	bool parseFromBinaryStream(ObjectInputStream* stream);

	void getStringList(Vector<String>& skills);
	void loadFromNames(Vector<String>& skills);

	void insertToMessage(BaseMessage* msg);
};

#endif /*SKILLBOXLIST_H_*/
