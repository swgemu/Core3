/*
 * SpeedMultiplierModChanges.h
 *
 *  Created on: 24/11/2010
 *      Author: victor
 */

#ifndef SPEEDMULTIPLIERMODCHANGES_H_
#define SPEEDMULTIPLIERMODCHANGES_H_

#include "system/util/ArrayList.h"

#include "engine/util/json_utils.h"

class SpeedModChange {
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

	SpeedModChange(const SpeedModChange& a) {
		newSpeed = a.newSpeed;
		timeStamp = a.timeStamp;
	}

	SpeedModChange& operator=(const SpeedModChange& a) {
		newSpeed = a.newSpeed;
		timeStamp = a.timeStamp;

		return *this;
	}

	inline float getNewSpeed() const {
		return newSpeed;
	}

	inline const Time& getTimeStamp() const {
		return timeStamp;
	}

	bool parseFromBinaryStream(ObjectInputStream* stream) {
		//TypeInfo<float>::parseFromBinaryStream(&newSpeed, stream);


		return false;
	}

	bool toBinaryStream(ObjectOutputStream* stream) {
		return false;
	}

	friend void to_json(nlohmann::json& j, const SpeedModChange& v) {
		j["newSpeed"] = v.newSpeed;
		j["timeStamp"] = v.timeStamp;
	}
};

class SpeedMultiplierModChanges : public ArrayList<SpeedModChange> {

};

#endif /* SPEEDMULTIPLIERMODCHANGES_H_ */
