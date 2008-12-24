/*
 * ThrowableWeaponImplementaton.h
 *
 *  Created on: Oct 23, 2008
 *      Author: swgdev
 */

#ifndef TRAPTHROWABLEWEAPONIMPLEMENTATION_H_
#define TRAPTHROWABLEWEAPONIMPLEMENTATION_H_

#include "TrapThrowableWeapon.h"

class TrapThrowableWeaponImplementation : public TrapThrowableWeaponServant {
protected:
	uint32 skill;
	String successString;
	String failureString;
	String animationString;

public:
	TrapThrowableWeaponImplementation(uint64 objid, uint32 tempcrc, const UnicodeString& n, const String& tempn, bool eqp = false);

	TrapThrowableWeaponImplementation(CreatureObject* creature, const String& temp, const UnicodeString& n, const String& tempn, bool eqp = false);

	void initialize();

	int useObject(Player* player);

	void useCharge(Player* player);

	void sendDeltas(Player* player);

	void generateAttributes(SceneObject* obj);

	void addHeaderAttributes(AttributeListMessage* alm);

	void addFooterAttributes(AttributeListMessage* alm);

	void addAttributes(AttributeListMessage* alm);

	void parseItemAttributes();

	bool isUsefull(Player* player);
};

#endif /* TRAPTHROWABLEWEAPONIMPLEMENTATION_H_ */
