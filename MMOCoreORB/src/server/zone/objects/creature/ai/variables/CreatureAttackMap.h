/*
 * CreatureAttackMap.h
 *
 *  Created on: Sep 28, 2010
 *      Author: dannuic
 */

#ifndef CREATUREATTACKMAP_H_
#define CREATUREATTACKMAP_H_

#include "engine/engine.h"

#include "engine/util/json_utils.h"

class CreatureAttack {
protected:
	String command;
	String arguments;

public:
	CreatureAttack() {}

	bool toBinaryStream(ObjectOutputStream* stream) {
		bool val = command.toBinaryStream(stream);
		bool val2 = arguments.toBinaryStream(stream);

		return val && val2;
	}

	bool parseFromBinaryStream(ObjectInputStream* stream) {
		bool val = command.parseFromBinaryStream(stream);
		bool val2 = arguments.parseFromBinaryStream(stream);

		return val && val2;
	}

	friend void to_json(nlohmann::json& j, const CreatureAttack& a) {
		j["command"] = a.command;
		j["arguments"] = a.arguments;
	}

	const String& getCommand() const {
		return command;
	}

	const String& getArguments() const {
		return arguments;
	}

	void setCommand(const String& c) {
		command = c;
	}

	void setArguments(const String& a) {
		arguments = a;
	}
};

class CreatureAttackMap : public Vector<CreatureAttack> {
public:
	CreatureAttackMap() {}
	virtual ~CreatureAttackMap() {}

	void addAttack(String c, String a) {
		CreatureAttack attack;
		attack.setCommand(c);
		attack.setArguments(a);
		add(attack);
	}

	const String& getCommand(int i) const {
		return get(i).getCommand();
	}

	const String& getArguments(int i) const {
		return get(i).getArguments();
	}

	int getRandomAttackNumber() const {
		return System::random(size() - 1);
	}
};

#endif /* CREATUREATTACKMAP_H_ */
