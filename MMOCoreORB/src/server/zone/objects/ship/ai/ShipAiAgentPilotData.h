#ifndef SHIPAIAGENTPILOTDATA_H_
#define SHIPAIAGENTPILOTDATA_H_

#include "engine/engine.h"

class ShipAiAgentPilotData : public Object {
public:
	const static int DATA_SIZE = 16;

protected:
	String pilotName;
	String pilotType;
	int holdFire;
	float speedRotationFactorMin;
	float speedRotationFactorOptimal;
	float speedRotationFactorMax;
	float slideDamp;
	float engineSpeed;
	float engineAccel;
	float engineDecel;
	float engineYaw;
	float engineYawAccel;
	float enginePitch;
	float enginePitchAccel;
	float engineRoll;
	float engineRollAccel;

public:
	ShipAiAgentPilotData() : Object() {
		holdFire = 0;
		speedRotationFactorMin = 0.f;
		speedRotationFactorOptimal = 0.f;
		speedRotationFactorMax = 0.f;
		slideDamp = 0.f;
		engineSpeed = 0.f;
		engineAccel = 0.f;
		engineDecel = 0.f;
		engineYaw = 0.f;
		engineYawAccel = 0.f;
		enginePitch = 0.f;
		enginePitchAccel = 0.f;
		engineRoll = 0.f;
		engineRollAccel = 0.f;
	}

	void readObject(LuaObject* row) {
		if (row == nullptr || row->getTableSize() < DATA_SIZE) {
			return;
		}

		pilotName = row->getStringAt(1);
		pilotType = row->getStringAt(2);
		holdFire = row->getIntAt(3);
		speedRotationFactorMin = row->getFloatAt(4);
		speedRotationFactorOptimal = row->getFloatAt(5);
		speedRotationFactorMax = row->getFloatAt(6);
		slideDamp = row->getFloatAt(7);
		engineSpeed = row->getFloatAt(8);
		engineAccel = row->getFloatAt(9);
		engineDecel = row->getFloatAt(10);
		engineYaw = row->getFloatAt(11) * Math::DEG2RAD;
		engineYawAccel = row->getFloatAt(12) * Math::DEG2RAD;
		enginePitch = row->getFloatAt(13) * Math::DEG2RAD;
		enginePitchAccel = row->getFloatAt(14) * Math::DEG2RAD;
		engineRoll = row->getFloatAt(15) * Math::DEG2RAD;
		engineRollAccel = row->getFloatAt(16) * Math::DEG2RAD;
	}

	String getPilotName() const {
		return pilotName;
	}

	String getPilotType() const {
		return pilotType;
	}

	int getHoldFire() const {
		return holdFire;
	}

	float getSpeedRotationFactorMin() const {
		return speedRotationFactorMin;
	}

	float getSpeedRotationFactorOptimal() const {
		return speedRotationFactorOptimal;
	}

	float getSpeedRotationFactorMax() const {
		return speedRotationFactorMax;
	}

	float getSlideDamp() const {
		return slideDamp;
	}

	float getEngineSpeed() const {
		return engineSpeed;
	}

	float getEngineAccel() const {
		return engineAccel;
	}

	float getEngineDecel() const {
		return engineDecel;
	}

	float getEngineYaw() const {
		return engineYaw;
	}

	float getEngineYawAccel() const {
		return engineYawAccel;
	}

	float getEnginePitch() const {
		return enginePitch;
	}

	float getEnginePitchAccel() const {
		return enginePitchAccel;
	}

	float getEngineRoll() const {
		return engineRoll;
	}

	float getEngineRollAccel() const {
		return engineRollAccel;
	}
};

#endif // SHIPAIAGENTPILOTDATA_H_
