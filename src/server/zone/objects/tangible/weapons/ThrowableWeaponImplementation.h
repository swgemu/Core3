/*
 * ThrowableWeaponImplementaton.h
 *
 *  Created on: Oct 23, 2008
 *      Author: swgdev
 */

#ifndef THROWABLEWEAPONIMPLEMENTATION_H_
#define THROWABLEWEAPONIMPLEMENTATION_H_

#include "ThrowableWeapon.h"

class ThrowableWeaponImplementation: public ThrowableWeaponServant {
protected:
	uint32 skill;
public:
	ThrowableWeaponImplementation(uint64 objid, uint32 tempcrc, const UnicodeString& n, const String& tempn,const int tp, bool eqp = false);

	ThrowableWeaponImplementation(CreatureObject* creature, const String& temp, const UnicodeString& n, const String& tempn, const int tp, bool eqp = false);

	void initialize();

	virtual void useCharge(Player* player) {

		decreaseUsesRemaining();
		updated = true;

		if (getUsesRemaining() == 0)
			remove(player);
	}

	void remove(Player* player);

	int useObject(Player* player);

	void parseItemAttributes();

	void setSkill(const String& sk);

	int getSkillCRC();

	void setSkillCRC(const int sk);

	bool isUsefull(Player* player);

};

#endif /* THROWABLEWEAPONIMPLEMENTATION_H_ */
