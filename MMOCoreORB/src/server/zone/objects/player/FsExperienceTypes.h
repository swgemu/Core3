#ifndef FSEXPERIENCETYPES_H_
#define FSEXPERIENCETYPES_H_

#include "engine/engine.h"

class FsExperienceTypes {
public:
	enum {
		COMBAT        = 1,
		SQUADLEADER   = 2,
		INVESTIGATION = 3,
		IMAGEDESIGNER = 4,
		DANCER        = 5,
		MUSICIAN      = 6,
		CRAFTING      = 7,
		SPACE         = 8,
		HEALING       = 9,
		WEAPON        = 10
	};

	// Ratios.
	enum {
		WEAPON_RATIO = 10,
		COMBAT_RATIO = 1
	};

	static String getFsExperienceTypeName(uint8 type) {
		String name = "";

		// This returns the string to use for "contains" to check experience types.
		switch(type) {
		case COMBAT:
			name = "combat_";
			break;
		case SQUADLEADER:
			name = "squad";
			break;
		case INVESTIGATION:
			name = "bounty";
			break;
		case IMAGEDESIGNER:
			name = "image";
			break;
		case DANCER:
			name = "danc";
			break;
		case MUSICIAN:
			name = "music";
			break;
		case CRAFTING:
			name = "craft";
			break;
		case SPACE:
			name = "space";
			break;
		case HEALING:
			name = "heal";
			break;
		case WEAPON:
			name = "weapon_";
			break;
		default:
			break;
		}

		return name;

	}

	// Getting ratios for conversion.

	static String getFsRatio(String type) {
		if (type.contains(getFsExperienceTypeName(FsExperienceTypes::WEAPON))) {
			return String::valueOf(FsExperienceTypes::WEAPON_RATIO);
		} else if (type.contains(getFsExperienceTypeName(FsExperienceTypes::COMBAT))) {
				return String::valueOf(FsExperienceTypes::COMBAT_RATIO);
			}
		return "";
	}

	/* This boolean checks to see whether or not the experience types are valid from the LUA call for the Experience Converter.
	 * It should be returning true if it's a correct type (according to scrapbook), and false if not.
	 */

	static bool isValid(uint8 type, String experienceType) {
		switch (type) {
		case 0: // Type = Combat Prowess. We want combative-type experiences.
			if ((experienceType.contains(getFsExperienceTypeName(FsExperienceTypes::COMBAT)) ||
					experienceType.contains(getFsExperienceTypeName(FsExperienceTypes::SQUADLEADER)) ||
					experienceType.contains(getFsExperienceTypeName(FsExperienceTypes::INVESTIGATION))) &&
					!experienceType.contains(getFsExperienceTypeName(FsExperienceTypes::SPACE))) {
				return true;
				break;
			}
			return false;
			break;
		case 1: // Type = Heightened Senses. We want entertainer types and healing.
			if (experienceType.contains(getFsExperienceTypeName(FsExperienceTypes::IMAGEDESIGNER)) ||
					experienceType.contains(getFsExperienceTypeName(FsExperienceTypes::DANCER)) ||
					experienceType.contains(getFsExperienceTypeName(FsExperienceTypes::HEALING)) ||
					experienceType.contains(getFsExperienceTypeName(FsExperienceTypes::MUSICIAN))) {
				return true;
				break;
			}
			return false;
			break;
		case 2: // Type = Enhanced Reflexes, same as Combat Prowess.
			if ((experienceType.contains(getFsExperienceTypeName(FsExperienceTypes::COMBAT)) ||
					experienceType.contains(getFsExperienceTypeName(FsExperienceTypes::SQUADLEADER)) ||
					experienceType.contains(getFsExperienceTypeName(FsExperienceTypes::INVESTIGATION))) &&
					!experienceType.contains(getFsExperienceTypeName(FsExperienceTypes::SPACE))) {
				return true;
				break;
			}
			return false;
			break;
		case 3: // Type = Crafting Mastery. Crafting-type experiences.
			if (experienceType.contains(getFsExperienceTypeName(FsExperienceTypes::CRAFTING))) {
				return true;
				break;
			}
			return false;
			break;
		default:
			return false;
			break;
		}
		return false;
	}

};

#endif /* FSEXPERIENCETYPES */
