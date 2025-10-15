#ifndef SHIPDOCKINGTASK_H_
#define SHIPDOCKINGTASK_H_

#include "engine/engine.h"
#include "server/zone/objects/ship/ShipObject.h"
#include "server/zone/packets/ship/ShipUpdateTransformMessage.h"
#include "server/zone/packets/scene/PlayClientEffectLocMessage.h"

class ShipDockingTask: public Task, public Logger {
private:
	const static int DURATION_MIN = 10000;
	const static int DURATION_MAX = 60000;

	const static int INTERVAL_INITIALIZE = 2000;
	const static int INTERVAL_TRANSFORM = 200;
	const static int INTERVAL_FINALIZE = 5000;

	constexpr static float SPEED_MIN = 10.f;
	constexpr static float SPEED_MAX = 25.f;

	enum DockingStage : int {
		INITIALIZE = 0,
		TRANSFORM = 1,
		FINALIZE = 2,
	};

protected:
	ManagedWeakReference<ShipObject*> shipRef;
	ManagedWeakReference<ShipObject*> targetRef;
	SpaceTransform dockTransform;

	uint64 timeStart;
	uint64 timeTotal;

	float rotationTime;
	float positionTime;

	int dockingStage;
	bool interlockStatus;

public:
	static bool isShipValid(ShipObject* ship) {
		return ship != nullptr && ship->isShipLaunched() && !ship->isHyperspacing() && !ship->isShipDestroyed() && !ship->isShipDisabled();
	}

	static bool isTargetValid(ShipObject* ship) {
		return ship != nullptr && ship->isShipLaunched() && !ship->isHyperspacing() && !ship->isShipDestroyed() && ship->getCurrentSpeed() <= 0.f;
	}

	static bool isDocking(ShipObject* ship) {
		return ship != nullptr && (ship->getOptionsBitmask() & OptionBitmask::DOCKING);
	}

	ShipDockingTask(ShipObject* ship, ShipObject* target) : Task() {
		setLoggingName("ShipDockingTask");

		shipRef = ship;
		targetRef = target;

		timeStart = System::getMiliTime();
		timeTotal = 0;

		rotationTime = 0.f;
		positionTime = 0.f;

		dockingStage = INITIALIZE;
		interlockStatus = false;
	}

	void run();

private:
	uint64 getTimeElapsed() const {
		return System::getMiliTime() - timeStart;
	}

	void setSpeed(ShipObject* ship) {
		float throttle = 1.f;

		if (rotationTime > 0.f && rotationTime > positionTime) {
			throttle = Math::clamp(0.f, positionTime / rotationTime, 1.f);
		}

		dockTransform.setSpeed(Math::clamp((float)SPEED_MIN, ship->getEngineMaxSpeed() * throttle, (float)SPEED_MAX));
	}

	void setTimeTotal(ShipObject* ship) {
		const auto& sTransform = ship->getCurrentTransform();
		const auto& sPosition = sTransform.getPosition();
		const auto& sRotation = sTransform.getRotation();
		const auto& dPosition = dockTransform.getPosition();
		const auto& dRotation = dockTransform.getRotation();

		if (sPosition != dPosition) {
			positionTime = sPosition.distanceTo(dPosition) / Math::max(ship->getEngineMaxSpeed() * 0.5f, 1.f);
		}

		if (sRotation != dRotation) {
			float tY = SpaceMath::getRotationRate(dRotation[0], sRotation[0]) / Math::max(ship->getEngineYawRate() * 0.5f, 1.f);
			float tP = SpaceMath::getRotationRate(dRotation[1], sRotation[1]) / Math::max(ship->getEnginePitchRate() * 0.5f, 1.f);
			float tR = SpaceMath::getRotationRate(dRotation[2], sRotation[2]) / Math::max(ship->getEngineRollRate() * 0.5f, 1.f);

			rotationTime = Math::max(tY, Math::max(tP, tR));
		}

		timeTotal = Math::clamp((float)DURATION_MIN, Math::max(positionTime, rotationTime), (float)DURATION_MAX);
	}

	void initializeDocking(ShipObject* ship, ShipObject* target);

	void updateTransform(ShipObject* ship, ShipObject* target);

	void finalizeDocking(ShipObject* ship, ShipObject* target);

	void notifyObservers(ShipObject* ship, ShipObject* target);

	void sendSystemMessage(ShipObject* ship, const String& string);

	void sendEffectMessage(ShipObject* ship, const String& effect);

	void clearDockingState(ShipObject* ship, ShipObject* target) const;

	void setDockingTransform(ShipObject* ship, ShipObject* target);

	void setAppearanceTransform(ShipObject* ship, ShipObject* target);

	bool checkLineOfSight(ShipObject* ship, ShipObject* target);

	Vector3 getBoundingPosition(ShipObject* ship, const Vector3& axis);

	Vector3 getBoundingAxis(ShipObject* ship, ShipObject* target);

	Vector3 getRotationAxis(const Vector3& axis);
};

#endif // SHIPDOCKINGTASK_H_
