/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef BUFFATTRIBUTE_H_
#define BUFFATTRIBUTE_H_

#include "engine/engine.h"

class BuffAttribute {
public:
	enum {
		HEALTH,
		STRENGTH,
		CONSTITUTION,
		ACTION,
		QUICKNESS,
		STAMINA,
		MIND,
		FOCUS,
		WILLPOWER,
		POISON,
		DISEASE,
		UNKNOWN
	};

	//TODO: This entire class needs to be removed. Posion and Disease are not attributes.
	//THEY ARE SKILLMODS
	static const uint8 ARRAYSIZE = 11;

	static bool isHAM(uint8 attribute) {
		return (attribute == HEALTH || attribute == ACTION || attribute == MIND);
	}

	static bool isProtection(uint8 attribute) {
		return (attribute == POISON || attribute == DISEASE);
	}

	static String getProtectionString(uint8 attribute) {
		String name = "";

		switch(attribute) {
		case POISON:
			name = "resistance_poison";
			break;
		case DISEASE:
			name = "resistance_disease";
			break;
		default:
			name = "unknown";
			break;
		}

		return name;
	}

	static String getAbsorptionString(uint8 attribute) {
		String name = "";

		switch(attribute) {
		case POISON:
			name = "absorption_poison";
			break;
		case DISEASE:
			name = "absorption_disease";
			break;
		default:
			name = "unknown";
			break;
		}

		return name;
	}

	static uint8 getAttribute(String attribute) {
		attribute = attribute.toLowerCase();

		if (attribute == "health")
			return HEALTH;
		else if (attribute == "action")
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
		else if (attribute == "poison")
			return POISON;
		else if (attribute == "disease")
			return DISEASE;
		else
			return UNKNOWN;

	}

	static String getName(const uint8 attribute, bool initialCap = false) {
		String name = "";

		switch (attribute) {
		case HEALTH:
			name ="health";
			break;
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
		case POISON:
			name = "poison";
			break;
		case DISEASE:
			name = "disease";
			break;
		default:
			name = "unknown";
			break;
		}

		if (initialCap)
			name[0] = toupper(name[0]);

		return name;
	}
};


#endif /* BUFFATTRIBUTE_H_ */
