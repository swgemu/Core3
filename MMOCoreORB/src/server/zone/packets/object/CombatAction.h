/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef COMBATACTION_H_
#define COMBATACTION_H_

#include "ObjectControllerMessage.h"

class CombatAction : public ObjectControllerMessage {
	int defenderSize;


public:
	// set the new posture of attacker and defender BEFORE constructing a CombatAction
	CombatAction(CreatureObject* attacker, CreatureObject* defender, uint32 animcrc, uint8 hit, uint8 trails, long weaponID = 0) :
		ObjectControllerMessage(attacker->getObjectID(), 0x1B, 0xCC) {

		insertInt(animcrc);

		insertLong(attacker->getObjectID());
		if (weaponID == 0)
			insertLong(attacker->getWeaponID());
		else
			insertLong(weaponID);

		insertByte(attacker->getPosture()); // AttackerEndPosture: 0x0-Standing 0x1-Kneeling 0x2-Prone 0xD-Incapacitated
		insertByte(trails); // Trails: 0x01-left_foot 0x02-right_foot 0x04-left_hand 0x08-right_hand 0x10-weapon
		insertByte(0x00); // AttackerSpecialMoveEffect: disabled in the client

		defenderSize = 1;

		insertShort(1);
		insertLong(defender->getObjectID());
		insertByte(defender->getPosture()); // DefenderEndPosture: 0x0-Standing 0x1-Kneeling 0x2-Prone 0xD-Incapacitated
		insertByte(hit); // HitType: 0x0-MISS 0x1-HIT 0x2-BLOCK 0x3-DODGE 0x5-COUNTER 0x7-RICOCHET 0x8-REFLECT 0x9-REFLECT_TO_TARGET
		insertByte(0x00); // DefenderSpecialMoveEffect: disabled in the client
	}

	CombatAction(CreatureObject* attacker, TangibleObject* defender, uint32 animcrc, uint8 hit, uint8 trails, long weaponID = 0) :
				ObjectControllerMessage(attacker->getObjectID(), 0x1B, 0xCC) {

		insertInt(animcrc);

		insertLong(attacker->getObjectID());
		if (weaponID == 0)
			insertLong(attacker->getWeaponID());
		else
			insertLong(weaponID);

		insertByte(attacker->getPosture());
		insertByte(trails);
		insertByte(0x00);

		defenderSize = 1;

		insertShort(1);
		insertLong(defender->getObjectID());
		insertByte(0);
		insertByte(hit);
		insertByte(0);
	}

	CombatAction(CreatureObject* attacker, uint32 animcrc) :
		ObjectControllerMessage(attacker->getObjectID(), 0x1B, 0xCC) {
		insertInt(animcrc);

		insertLong(attacker->getObjectID());
		insertLong(attacker->getWeaponID());

		insertByte(attacker->getPosture());
		insertByte(0xFF);
		insertByte(0xFF);

		defenderSize = 0;
		insertShort(0); // number of defenders
	}

	CombatAction(CreatureObject* attacker, uint32 animcrc, long weaponID) :
		ObjectControllerMessage(attacker->getObjectID(), 0x1B, 0xCC) {
		insertInt(animcrc);

		insertLong(attacker->getObjectID());
		insertLong(weaponID);

		insertByte(attacker->getPosture());
		insertByte(0xFF);
		insertByte(0xFF);

		defenderSize = 0;
		insertShort(0); // number of defenders
	}


	CombatAction(TangibleObject* attacker, CreatureObject* defender, uint32 animcrc,uint8 hit, long wpnID = 0) :
		ObjectControllerMessage(attacker->getObjectID(), 0x1B, 0xCC) {
			insertInt(animcrc);

			insertLong(attacker->getObjectID());
			insertLong(wpnID);

			insertByte(0x0);
			insertByte(0xFF);
			insertByte(0xFF);

			defenderSize = 1;

			insertShort(1);
			insertLong(defender->getObjectID());
			insertByte(defender->getPosture());
			insertByte(hit);
			insertByte(0);
	}


	CombatAction(CreatureObject* attacker, CreatureObject* defender,
			uint32 animcrc,uint8 hit, long wpnID) :
		ObjectControllerMessage(attacker->getObjectID(), 0x1B, 0xCC) {
		insertInt(animcrc);

		insertLong(attacker->getObjectID());
		insertLong(wpnID);

		insertByte(attacker->getPosture());
		insertByte(0xFF);
		insertByte(0xFF);

		defenderSize = 1;

		insertShort(1);
		insertLong(defender->getObjectID());
		insertByte(defender->getPosture());
		insertByte(hit);
		insertByte(0);
	}

	void updateDefenderSize() {
		insertShort(53, ++defenderSize);
	}

	void addDefender(CreatureObject* defender, uint8 hit) {
		insertLong(defender->getObjectID());
		insertByte(defender->getPosture());
		insertByte(hit);
		insertByte(0);

		updateDefenderSize();
	}
};

#endif /*COMBATACTION_H_*/
