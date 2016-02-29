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
	bool add(Ability* ability, DeltaMessage* message = NULL, int updates = 1);
	bool contains(const String& element);

	bool toBinaryStream(ObjectOutputStream* stream);
	bool parseFromBinaryStream(ObjectInputStream* stream);

	void insertToMessage(BaseMessage* msg);
};


// This is used solely for the ObjectVersionUpdateManager
class AbilityListMigrator : public DeltaVector<Ability*> {
	public:
		Vector<String> names;
		uint32 updateCounter;

		bool toBinaryStream(ObjectOutputStream* stream) {
			TypeInfo<uint32>::toBinaryStream(&updateCounter, stream);
			names.toBinaryStream(stream);

			return true;
		}

		bool parseFromBinaryStream(ObjectInputStream* stream) {
			TypeInfo<uint32>::parseFromBinaryStream(&updateCounter, stream);
			names.parseFromBinaryStream(stream);

			return true;
		}
	};
#endif /* ABILITYLIST_H_ */
