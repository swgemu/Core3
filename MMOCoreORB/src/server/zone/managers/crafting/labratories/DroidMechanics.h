#ifndef DROID_MECHANICS_H
#define DROID_MECHANICS_H

#include "server/zone/objects/creature/ai/DroidObject.h"

namespace server {
namespace zone {
namespace managers {
namespace crafting {
namespace labratories {

class DroidMechanics {
public:
	DroidMechanics();
	virtual ~DroidMechanics();
	static float determineHam(float quality, int droidType){
		int maxHam = 55;
		int minHam = 45;
		if(droidType == DroidObject::R_SERIES) {
			maxHam = 4500;
			minHam = 1125;
		}
		if(droidType == DroidObject::DZ70 || droidType == DroidObject::PROBOT) {
			maxHam = 3200;
			minHam = 800;
		}
		if(droidType == DroidObject::LE_REPAIR) {
			maxHam = 6000;
			minHam = 1500;
		}
		if (droidType == DroidObject::MSE || droidType == DroidObject::POWER_DROID || droidType == DroidObject::PROTOCOL || droidType == DroidObject::SURGICAL || droidType == DroidObject::TREADWELL) {
			maxHam = 55;
			minHam = 45;
		}
		if (droidType == DroidObject::BLL) {
			maxHam = 1400;
			minHam = 1200;
		}
		float hamValue = quality * (float)maxHam;
		if (hamValue < minHam) {
			hamValue = minHam;
		}
		return hamValue;
	}
	static float determineSpeed(int droidType, float ham) {
		if(droidType == DroidObject::R_SERIES)
			return 2.0 - (( 1.0 - ((4500.0 - ham)/1125.0))/2.0);
		if(droidType == DroidObject::PROBOT || droidType == DroidObject::DZ70)
			return 1.0 - (( 1.0 - ((3200.0 - ham)/800.0))/4.0);
		if (droidType == DroidObject::LE_REPAIR)
			return 2.0 - (( 1.0 - ((6000.0 - ham)/1500.0))/2.0);
		return 0.0;
	}
	static float determineHit(int droidType, float ham) {
		if(droidType == DroidObject::R_SERIES)
			return 0.33 + (0.08*(1.0 - ((4500.0-ham)/1125.0)));
		if(droidType == DroidObject::LE_REPAIR)
			return 0.33 + (0.08*(1.0 - ((6000.0-ham)/1500.0)));
		if(droidType == DroidObject::DZ70 || droidType == DroidObject::PROBOT)
			return 0.33 + (0.08*(1.0 - ((3200.0-ham)/800.0)));

		return 0.0;
	}
	static float determineMinDamage(int droidType, int rating) {
		if (rating == 0)
			return 1;
		if(droidType == DroidObject::R_SERIES)
			return ((int)((rating/600.0) * 80.0)) + 80;
		if(droidType == DroidObject::LE_REPAIR)
			return ((int)((rating/600.0) * 45.0)) + 45;
		if(droidType == DroidObject::PROBOT || droidType == DroidObject::DZ70)
			return ((int)((rating/600.0) * 95.0)) + 95;
		return 1;
	}
	static float determineMaxDamage(int droidType, int rating) {
		if (rating == 0)
			return 1;
		if(droidType == DroidObject::R_SERIES)
			return ((int)((rating/600.0) * 85.0)) + 85;
		if(droidType == DroidObject::LE_REPAIR)
			return ((int)((rating/600.0) * 55.0)) + 55;
		if(droidType == DroidObject::PROBOT || droidType == DroidObject::DZ70)
			return ((int)((rating/600.0) * 100.0)) + 100;
		return 1;
	}
	/** Used to determine harvest droid and trap droid skill mod*/
	static int determineDroidSkillBonus(float playerSkill, float droidSkill, float baseAmount) {
		float p1 = (playerSkill + 1)/(float)100;
		float p2 = 3.55 * p1;
		float p3 = droidSkill/p2;
		float p4 = p3/100;
		float bonus = (baseAmount * p4);
		return ceil(bonus);
	}
};

}
}
}
}
}

using namespace server::zone::managers::crafting::labratories;

#endif /* DROID_MECHANICS_H */
