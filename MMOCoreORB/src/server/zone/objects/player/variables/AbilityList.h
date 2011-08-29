/*
 * AbilityList.h
 *
 *  Created on: 28/12/2009
 *      Author: victor
 */

#ifndef ABILITYLIST_H_
#define ABILITYLIST_H_

#include "engine/engine.h"
#include "server/zone/objects/scene/variables/DeltaVector.h"

class Ability;

/**
 * The ability list is just a vector of strings that award the ability to perform specific actions.
 */
class AbilityList : public DeltaVector<Ability*> {
private:
	void getStringList(Vector<String>& abilities);
	void loadFromNames(Vector<String>& abilities);

public:
	bool contains(const String& element);

	bool toBinaryStream(ObjectOutputStream* stream);
	bool parseFromBinaryStream(ObjectInputStream* stream);

	void insertToMessage(BaseMessage* msg);
};


#endif /* ABILITYLIST_H_ */
