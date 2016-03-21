/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#include "CreatureAttribute.h"

const uint8 CreatureEncumbrance::HEALTH = 0;
const uint8 CreatureEncumbrance::ACTION = 1;
const uint8 CreatureEncumbrance::MIND = 2;

const uint8 CreatureAttribute::HEALTH = 0;
const uint8 CreatureAttribute::STRENGTH = 1;
const uint8 CreatureAttribute::CONSTITUTION = 2;
const uint8 CreatureAttribute::ACTION = 3;
const uint8 CreatureAttribute::QUICKNESS = 4;
const uint8 CreatureAttribute::STAMINA = 5;
const uint8 CreatureAttribute::MIND = 6;
const uint8 CreatureAttribute::FOCUS = 7;
const uint8 CreatureAttribute::WILLPOWER = 8;
const uint8 CreatureAttribute::UNKNOWN = 9;

const uint8 CreatureAttribute::ARRAYSIZE = 9;


bool CreatureAttribute::isHAM(uint8 attribute) {
	return (attribute == HEALTH || attribute == ACTION || attribute == MIND);
}

uint8 CreatureAttribute::getAttribute(String attribute) {
	attribute = attribute.toLowerCase();

	if (attribute == "action")
		return ACTION;
	else if (attribute == "mind")
		return MIND;
	else if (attribute == "strength")
		return STRENGTH;
	else if (attribute == "constitution")
		return CONSTITUTION;
	else if (attribute == "quickness")
		return QUICKNESS;
	else if (attribute == "stamina")
		return STAMINA;
	else if (attribute == "focus")
		return FOCUS;
	else if (attribute == "willpower")
		return WILLPOWER;
	else
		return HEALTH;

}

String CreatureAttribute::getName(const uint8 attribute, bool initialCap) {
	String name = "";

	switch (attribute) {
	case ACTION:
		name = "action";
		break;
	case MIND:
		name = "mind";
		break;
	case STRENGTH:
		name = "strength";
		break;
	case CONSTITUTION:
		name = "constitution";
		break;
	case QUICKNESS:
		name = "quickness";
		break;
	case STAMINA:
		name = "stamina";
		break;
	case FOCUS:
		name = "focus";
		break;
	case WILLPOWER:
		name = "willpower";
		break;
	default:
	case HEALTH:
		name = "health";
		break;
	}

	if (initialCap)
		name[0] = toupper(name[0]);

	return name;
}