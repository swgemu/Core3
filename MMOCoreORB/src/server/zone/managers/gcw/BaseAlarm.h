#ifndef BASEALARM_H_
#define BASEALARM_H_

namespace server {
namespace zone {
namespace managers {
namespace gcw {

class BaseAlarm : public Object {

protected:
	String baseType;
	String alarmType;
	Vector3 spawnLoc;
	int cellID;
	Quaternion rotation;

public:
	BaseAlarm(String base, String alarm, Vector3 loc, int cell, Quaternion rot) : Object() {
		baseType = base;
		alarmType = alarm;
		cellID = cell;
		spawnLoc = loc;
		rotation = rot;
	}

	~BaseAlarm() {
	}

	String getBaseType() {
		return baseType;
	}

	String getAlarmType() {
		return alarmType;
	}

	int getCellID() {
		return cellID;
	}

	inline Vector3* getSpawnLoc() {
		return &spawnLoc;
	}

	Quaternion getRotation() const {
		return rotation;
	}

};

}
}
}
}

#endif /* BASEALARM_H_ */