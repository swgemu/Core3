/*
 * AbilityList.h
 *
 *  Created on: 28/12/2009
 *      Author: victor
 */

#ifndef ABILITYLIST_H_
#define ABILITYLIST_H_

#include "engine/engine.h"
#include "engine/util/json_utils.h"

#include "server/zone/objects/scene/variables/DeltaVector.h"

class Ability;

/**
 * The ability list is just a vector of strings that award the ability to perform specific actions.
 */
class AbilityList : public DeltaVector<Ability*> {
private:
#ifdef ODB_SERIALIZATION
	Vector<String> abilities;
#endif
	void getStringList(Vector<String>& abilities) const;
	void loadFromNames(Vector<String>& abilities);

public:
	bool add(Ability* const& ability, DeltaMessage* message = nullptr, int updates = 1) override;
	bool contains(const String& element) const;

	bool toBinaryStream(ObjectOutputStream* stream) override;
	bool parseFromBinaryStream(ObjectInputStream* stream) override;

	friend void to_json(nlohmann::json& j, const AbilityList& l);

	void insertToMessage(BaseMessage* msg) const override;
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
