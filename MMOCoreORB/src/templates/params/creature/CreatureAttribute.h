/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef CREATUREATTRIBUTE_H_
#define CREATUREATTRIBUTE_H_

#include "system/lang.h"

class CreatureEncumbrance {
public:
	static const uint8 HEALTH;
	static const uint8 ACTION;
	static const uint8 MIND;
};

class CreatureAttribute {
public:
	static const uint8 HEALTH;
	static const uint8 STRENGTH;
	static const uint8 CONSTITUTION;
	static const uint8 ACTION;
	static const uint8 QUICKNESS;
	static const uint8 STAMINA;
	static const uint8 MIND;
	static const uint8 FOCUS;
	static const uint8 WILLPOWER;
	static const uint8 UNKNOWN;

	static const uint8 ARRAYSIZE;

	static bool isHAM(uint8 attribute);

	static uint8 getAttribute(String attribute);

	static String getName(const uint8 attribute, bool initialCap = false);
};

#endif /* CREATUREATTRIBUTE_H_ */
