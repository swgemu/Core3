
#ifndef MOUNTSPEEDDATA_H_
#define MOUNTSPEEDDATA_H_

#include "templates/params/primitives/StringParam.h"

namespace server {
namespace zone {
namespace managers {
namespace creature {

class MountSpeedData : public Object {

protected:
	StringParam appearanceFilename;
	float runSpeed;
	float gallopSpeedMultiplier;
	int gallopDuration;
	int gallopCooldown;

public:
	MountSpeedData(String file, float run, float multiplier, int duration, int cooldown) : Object() {
		String filename = file;
		appearanceFilename.setValue(filename);

		runSpeed = run;
		gallopSpeedMultiplier = multiplier;
		gallopDuration = duration;
		gallopCooldown = cooldown;
	}

	~MountSpeedData() {

	}

	String getAppearanceFilename() {
		return appearanceFilename;
	}

	float getRunSpeed() {
		return runSpeed;
	}

	float getGallopSpeedMultiplier() {
		return gallopSpeedMultiplier;
	}

	int getGallopDuration() {
		return gallopDuration;
	}

	int getGallopCooldown() {
		return gallopCooldown;
	}
};

}
}
}
}

#endif /* MOUNTSPEEDDATA_H_ */
