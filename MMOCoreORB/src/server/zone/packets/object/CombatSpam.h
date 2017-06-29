/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef COMBATSPAM_H_
#define COMBATSPAM_H_

#include "StandaloneObjectControllerMessage.h"

#include "server/zone/objects/tangible/TangibleObject.h"

class CombatSpam : public StandaloneObjectControllerMessage {
public:

	CombatSpam(TangibleObject* attacker, TangibleObject* defender, CreatureObject* receiver, TangibleObject* item, uint32 damage, const String& file, const String& stringName, byte color)
			: StandaloneObjectControllerMessage(receiver->getObjectID(), 0x1B, 0x134) {

		if (attacker != NULL)
			insertLong(attacker->getObjectID()); //%TU in strings.
		else
			insertLong(0);

		if (defender != NULL)
			insertLong(defender->getObjectID()); //%TT in strings.
		else
			insertLong(0);

		if (item != NULL)
			insertLong(item->getObjectID()); //%TO in strings.
		else
			insertLong(0);

		insertInt(damage); //damage of attack, damage mitigated, etc. %DI in strings.

		insertAscii(file.toCharArray()); //file name (ex. "cbt_spam")
		insertInt(0); //padding
		insertAscii(stringName.toCharArray()); //string name (ex. "attack_hit")
		insertByte(color); //colour flag. 0=white, 1=auto green/red, 10=red, 11=yellow

		insertInt(0); //unicode string to display in combat spam.
	}

	//For custom combat spam messages.
	CombatSpam(CreatureObject* receiver, const UnicodeString& uniString, byte color)
			: StandaloneObjectControllerMessage(receiver->getObjectID(), 0x1B, 0x134) {

		insertLong(0);
		insertLong(0);
		insertLong(0);
		insertInt(0);
		insertAscii("");
		insertInt(0);
		insertAscii("");
		insertByte(color);
		insertUnicode(uniString);
	}

};

#endif /*COMBATSPAM_H_*/
