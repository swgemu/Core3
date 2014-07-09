#ifndef FSEXPERIENCETYPES_H_
#define FSEXPERIENCETYPES_H_

#include "engine/engine.h"

class FsExperienceTypes {
public:
	static const int COMBAT = 1;
	static const int SQUADLEADER = 2;
	static const int INVESTIGATION = 3;
	static const int IMAGEDESIGNER = 4;
	static const int DANCER = 5;
	static const int MUSICIAN = 6;
	static const int CRAFTING = 7;
	static const int SPACE = 8;

	static String getFsExperienceTypeName(uint8 type) {
		String name = "";

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
		default:
			break;
		}

		return name;

	}


	static bool isValid(uint8 type, String experienceType) {
		switch (type) {
		case 0:
			if ((experienceType.contains(getFsExperienceTypeName(FsExperienceTypes::COMBAT)) ||
				experienceType.contains(getFsExperienceTypeName(FsExperienceTypes::SQUADLEADER)) ||
				experienceType.contains(getFsExperienceTypeName(FsExperienceTypes::INVESTIGATION))) &&
				!experienceType.contains(getFsExperienceTypeName(FsExperienceTypes::SPACE))) {
				return true;
				break;
			}
			return false;
			break;
		case 1:
			if (experienceType.contains(getFsExperienceTypeName(FsExperienceTypes::IMAGEDESIGNER)) ||
					experienceType.contains(getFsExperienceTypeName(FsExperienceTypes::DANCER)) ||
					experienceType.contains(getFsExperienceTypeName(FsExperienceTypes::MUSICIAN))) {
				return true;
				break;
			}
			return false;
			break;
		case 2:
			if (experienceType.contains(getFsExperienceTypeName(FsExperienceTypes::COMBAT)) ||
				experienceType.contains(getFsExperienceTypeName(FsExperienceTypes::SQUADLEADER)) ||
				experienceType.contains(getFsExperienceTypeName(FsExperienceTypes::INVESTIGATION))) {
				return true;
				break;
			}
			return false;
			break;
		case 3:
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
