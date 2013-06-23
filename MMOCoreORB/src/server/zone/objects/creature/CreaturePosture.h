/*
Copyright (C) 2007 <SWGEmu>

This File is part of Core3.

This program is free software; you can redistribute
it and/or modify it under the terms of the GNU Lesser
General Public License as published by the Free Software
Foundation; either version 2 of the License,
or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
See the GNU Lesser General Public License for
more details.

You should have received a copy of the GNU Lesser General
Public License along with this program; if not, write to
the Free Software Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA

Linking Engine3 statically or dynamically with other modules
is making a combined work based on Engine3.
Thus, the terms and conditions of the GNU Lesser General Public License
cover the whole combination.

In addition, as a special exception, the copyright holders of Engine3
give you permission to combine Engine3 program with free software
programs or libraries that are released under the GNU LGPL and with
code included in the standard release of Core3 under the GNU LGPL
license (or modified versions of such code, with unchanged license).
You may copy and distribute such a system following the terms of the
GNU LGPL for Engine3 and the licenses of the other code concerned,
provided that you include the source code of that other code when
and as the GNU LGPL requires distribution of source code.

Note that people who make modified versions of Engine3 are not obligated
to grant this special exception for their modified versions;
it is their choice whether to do so. The GNU Lesser General Public License
gives permission to release a modified version without this exception;
this exception also makes it possible to release a modified version
which carries forward this exception.
*/

#ifndef CREATUREPOSTURE_H_
#define CREATUREPOSTURE_H_

#include "engine/engine.h"
#include "server/zone/templates/datatables/DataTableIff.h"
#include "server/zone/templates/datatables/DataTableRow.h"
#include "server/zone/managers/templates/TemplateManager.h"

#include "CreatureLocomotion.h"

class CreatureMovementEntry : public Variable {
public:
	UnsignedCharacter posture;
	UnsignedCharacter stationary;
	UnsignedCharacter slow;
	UnsignedCharacter fast;
	Float movementScale;
	Float accelerationScale;
	Float turnScale;
	Float canSeeHeightMod;

	CreatureMovementEntry() : Variable() {
		posture = 0;
		stationary = 0;
		slow = 0;
		fast = 0;
		movementScale = 0;
		accelerationScale = 0;
		turnScale = 0;
		canSeeHeightMod = 0;
	}

	CreatureMovementEntry(const CreatureMovementEntry& m) : Variable() {
		posture = m.posture;
		stationary = m.stationary;
		slow = m.slow;
		fast = m.fast;
		movementScale = m.movementScale;
		accelerationScale = m.accelerationScale;
		turnScale = m.turnScale;
		canSeeHeightMod = m.canSeeHeightMod;
	}

	bool operator==(CreatureMovementEntry entry) {
		return posture == entry.posture; // only need posture here because I am sure that these are unique to entries
	}

	bool toString(String& str) {
		return posture.toString(str) && stationary.toString(str) && slow.toString(str) && fast.toString(str) && movementScale.toString(str) && accelerationScale.toString(str) && turnScale.toString(str) && canSeeHeightMod.toString(str);
	}

	bool parseFromString(const String& str, int version = 0) {
		return posture.parseFromString(str, version) && stationary.parseFromString(str, version) && slow.parseFromString(str, version) && fast.parseFromString(str, version) && movementScale.parseFromString(str, version) && accelerationScale.parseFromString(str, version) && turnScale.parseFromString(str, version) && canSeeHeightMod.parseFromString(str, version);
	}

	bool toBinaryStream(ObjectOutputStream* stream) {
		posture.toBinaryStream(stream);
		stationary.toBinaryStream(stream);
		slow.toBinaryStream(stream);
		fast.toBinaryStream(stream);
		movementScale.toBinaryStream(stream);
		accelerationScale.toBinaryStream(stream);
		turnScale.toBinaryStream(stream);
		canSeeHeightMod.toBinaryStream(stream);

		return true;
	}

	bool parseFromBinaryStream(ObjectInputStream* stream) {
		posture.parseFromBinaryStream(stream);
		stationary.parseFromBinaryStream(stream);
		slow.parseFromBinaryStream(stream);
		fast.parseFromBinaryStream(stream);
		movementScale.parseFromBinaryStream(stream);
		accelerationScale.parseFromBinaryStream(stream);
		turnScale.parseFromBinaryStream(stream);
		canSeeHeightMod.parseFromBinaryStream(stream);

		return true;
	}
};

class CreaturePosture : public Singleton<CreaturePosture>, public Object, public Logger {
public:
	static const uint8 INVALID = 0xFF;
	static const uint8 UPRIGHT = 0;
	static const uint8 CROUCHED = 1;
	static const uint8 PRONE = 2;
	static const uint8 SNEAKING = 3;
	static const uint8 BLOCKING = 4;
	static const uint8 CLIMBING = 5;
	static const uint8 FLYING = 6;
	static const uint8 LYINGDOWN = 7;
	static const uint8 SITTING = 8;
	static const uint8 SKILLANIMATING = 9;
	static const uint8 DRIVINGVEHICLE = 10;
	static const uint8 RIDINGCREATURE = 11;
	static const uint8 KNOCKEDDOWN = 12;
	static const uint8 INCAPACITATED = 13;
	static const uint8 DEAD = 14;

	HashTable<uint8, CreatureMovementEntry> movementTable;

	CreaturePosture() {}

	~CreaturePosture() {}

	uint8 getLocomotion(uint8 pos, uint8 speed) {
		CreatureMovementEntry* move = &movementTable.get(pos);

		switch (speed) {
		case CreatureLocomotion::STATIONARY:
			return move->stationary;
			break;
		case CreatureLocomotion::SLOW:
			return move->slow;
			break;
		case CreatureLocomotion::FAST:
			return move->fast;
			break;
		default:
			return CreatureLocomotion::INVALID;
		}

		return CreatureLocomotion::INVALID;
	}

	uint8 getSpeed(uint8 pos, uint8 loc) {
		CreatureMovementEntry* move = &movementTable.get(pos);

		if (loc == move->stationary)
			return CreatureLocomotion::STATIONARY;

		if (loc == move->slow)
			return CreatureLocomotion::SLOW;

		if (loc == move->fast)
			return CreatureLocomotion::FAST;

		return CreatureLocomotion::INVALID;
	}

	float getMovementScale(uint8 pos) {
		return movementTable.get(pos).movementScale;
	}

	float getAccelerationScale(uint8 pos) {
		return movementTable.get(pos).accelerationScale;
	}

	float getTurnScale(uint8 pos) {
		return movementTable.get(pos).turnScale;
	}

	float getCanSeeHeightMod(uint8 pos) {
		return movementTable.get(pos).canSeeHeightMod;
	}

	void loadMovementData() {
		IffStream* iffStream = TemplateManager::instance()->openIffFile("datatables/movement/movement_human.iff");

		if (iffStream == NULL) {
			error("Could not load movement data.");
			return;
		}

		DataTableIff dtiff;
		dtiff.readObject(iffStream);

		delete iffStream;

		for (int i = 0; i < dtiff.getTotalRows(); i++) {
			DataTableRow* row = dtiff.getRow(i);
			CreatureMovementEntry entry;
			int value;
			float scale;

			row->getValue(0, value);
			if (value < 0) entry.posture = 0xFF;
			else entry.posture = (uint8)value;

			row->getValue(1, value);
			if (value < 0) entry.stationary = 0xFF;
			else entry.stationary = (uint8)value;

			row->getValue(2, value);
			if (value < 0) entry.slow = 0xFF;
			else entry.slow = (uint8)value;

			row->getValue(3, value);
			if (value < 0) entry.fast = 0xFF;
			else entry.fast = (uint8)value;

			row->getValue(4, scale);
			entry.movementScale = scale;
			row->getValue(5, scale);
			entry.accelerationScale = scale;
			row->getValue(6, scale);
			entry.turnScale = scale;
			row->getValue(7, scale);
			entry.canSeeHeightMod = scale;

			movementTable.put(entry.posture, entry);
		}
	}
};

#endif /* CREATUREPOSTURE_H_ */
