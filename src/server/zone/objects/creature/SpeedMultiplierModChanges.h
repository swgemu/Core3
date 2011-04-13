/*
 * SpeedMultiplierModChanges.h
 *
 *  Created on: 24/11/2010
 *      Author: victor
 */

#ifndef SPEEDMULTIPLIERMODCHANGES_H_
#define SPEEDMULTIPLIERMODCHANGES_H_

class SpeedModChange : public Object {
	float newSpeed;
	Time timeStamp;

public:
	SpeedModChange() {
		newSpeed = 0;
	}

	SpeedModChange(float speed) {
		newSpeed = speed;
		timeStamp.updateToCurrentTime();
	}

	SpeedModChange(float speed, Time& tm) {
		newSpeed = speed;
		timeStamp = tm;
	}

	SpeedModChange(const SpeedModChange& a) : Object() {
		newSpeed = a.newSpeed;
		timeStamp = a.timeStamp;
	}

	SpeedModChange& operator=(const SpeedModChange& a) {
		newSpeed = a.newSpeed;
		timeStamp = a.timeStamp;

		return *this;
	}

	inline float getNewSpeed() {
		return newSpeed;
	}

	inline Time& getTimeStamp() {
		return timeStamp;
	}
};

class SpeedMultiplierModChanges : public Vector<SpeedModChange> {

};

#endif /* SPEEDMULTIPLIERMODCHANGES_H_ */
