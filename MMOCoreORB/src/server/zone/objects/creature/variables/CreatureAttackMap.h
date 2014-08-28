/*
 * CreatureAttackMap.h
 *
 *  Created on: Sep 28, 2010
 *      Author: dannuic
 */

#ifndef CREATUREATTACKMAP_H_
#define CREATUREATTACKMAP_H_

#include "engine/engine.h"

class CreatureAttack : public Variable {
protected:
	String command;
	String arguments;

public:
	CreatureAttack() {}
	virtual ~CreatureAttack() {}

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

	String getCommand() {
		return command;
	}

	String getArguments() {
		return arguments;
	}

	void setCommand(String c) {
		command = c;
	}

	void setArguments(String a) {
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

	String getCommand(int i) {
		return get(i).getCommand();
	}

	String getArguments(int i) {
		return get(i).getArguments();
	}

	int getRandomAttackNumber() {
		return System::random(size() - 1);
	}
};

#endif /* CREATUREATTACKMAP_H_ */
