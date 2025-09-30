#ifndef SHIPDOCKINGTASK_H_
#define SHIPDOCKINGTASK_H_

#include "engine/engine.h"
#include "server/zone/objects/ship/ShipObject.h"
#include "server/zone/packets/ship/ShipUpdateTransformMessage.h"
#include "server/zone/packets/scene/PlayClientEffectLocMessage.h"
#include "server/zone/packets/scene/PlayClientEventObjectMessage.h"

class ShipDockingTask: public Task, public Logger {
private:
	const static int DURATION_MIN = 10000;
	const static int DURATION_MAX = 60000;

	const static int INTERVAL_INITIALIZE = 2000;
	const static int INTERVAL_TRANSFORM = 200;
	const static int INTERVAL_FINALIZE = 2000;

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

		dockingStage = INITIALIZE;
		interlockStatus = false;
	}

	void run();

private:
	uint64 getTimeElapsed() const {
		return System::getMiliTime() - timeStart;
	}

	void clearDockingState(ShipObject* ship, ShipObject* target) const {
		if (ship != nullptr) {
			ship->clearOptionBit(OptionBitmask::DOCKING, true);
		}

		if (target != nullptr) {
			target->clearOptionBit(OptionBitmask::DOCKING, true);
		}
	}

	void setDockingTransform(ShipObject* ship, ShipObject* target) {
		uint32 clientType = target->getClientGameObjectType();

		switch (clientType) {
			case SceneObjectType::SPACEOBJECT: // SHIPSTATION
			case SceneObjectType::SHIPCAPITAL: {
				setAppearanceTransform(ship, target);
				break;
			}
			case SceneObjectType::SHIPFIGHTER:
			case SceneObjectType::SHIPTRANSPORT:
			default: {
				setBoundingTransform(ship, target);
			}
		}

		setSpeed(ship);
		setTimeTotal(ship);
	}

	Vector3 getBoundingPosition(ShipObject* ship) {
		auto bounding = ship->getBoundingVolume();

		if (bounding == nullptr) {
			return Vector3::ZERO;
		}

		Vector3 position = Vector3::ZERO;
		Vector3 rotation = Vector3::ZERO;

		if (bounding->isBoundingBox()) {
			const auto& box = bounding->getBoundingBox();
			const auto& boundMax = *box.getMaxBound();
			const auto& boundMin = *box.getMinBound();

			Vector3 center = (boundMin + boundMax) * 0.5f;
			float radius = (boundMax.getY() - boundMin.getY()) * 0.5f;
			position = center + Vector3(0,radius+1.f,0);
		} else {
			const auto& sphere = bounding->getBoundingSphere();
			const auto& center = sphere.getCenter();

			float radius = sphere.getRadius();
			position = center + Vector3(0,radius+1.f,0);
		}

		return position;
	}

	void setBoundingTransform(ShipObject* ship, ShipObject* target) {
		Vector3 position = getBoundingPosition(target) + getBoundingPosition(ship);
		Vector3 rotation = target->getCurrentTransform().getRotation();

		position = position * *target->getConjugateMatrix();
		position = Vector3(position.getX(), position.getZ(), position.getY()) + target->getPosition();

		dockTransform.setPosition(position);
		dockTransform.setRotation(rotation);
	}

	void setAppearanceTransform(ShipObject* ship, ShipObject* target) {
		auto appearance = target->getAppearanceTemplate();

		if (appearance == nullptr) {
			return;
		}

		auto bounding = ship->getBoundingVolume();

		if (bounding == nullptr) {
			return;
		}

		Vector3 position = Vector3::ZERO;
		Vector3 rotation = Vector3::ZERO;

		Vector3 sLocal = (ship->getPosition() - target->getPosition());
		sLocal = Vector3(sLocal.getX(), sLocal.getZ(), sLocal.getY()) * *target->getRotationMatrix();

		const auto& hardpoints = appearance->getHardpoints();
		float distanceMin = FLT_MAX;

		for (int i = 0; i < hardpoints.size(); ++i) {
			auto key = hardpoints.elementAt(i).getKey();

			if (key.length() != 6 || key.subString(0, key.length()-2) != "dock") {
				continue;
			}

			auto hardpointRotation = hardpoints.elementAt(i).getValue();
			auto hardpointPosition = Vector3(hardpointRotation[3][0], hardpointRotation[3][1]+2.5f, hardpointRotation[3][2]);
			float distanceSqr = hardpointPosition.squaredDistanceTo(sLocal);

			if (distanceMin > distanceSqr) {
				distanceMin = distanceSqr;
				position = hardpointPosition;
				rotation = SpaceMath::matrixToRotation(hardpointRotation);
			}
		}

		position = (position + getBoundingPosition(ship)) * *target->getConjugateMatrix();
		position = Vector3(position.getX(), position.getZ(), position.getY()) + target->getPosition();
		rotation = SpaceMath::getRotationRate(target->getCurrentTransform().getRotation() + rotation);

		dockTransform.setPosition(position);
		dockTransform.setRotation(rotation);
	}

	void setSpeed(ShipObject* ship) {
		dockTransform.setSpeed(Math::clamp((float)SPEED_MIN, ship->getEngineMaxSpeed(), (float)SPEED_MAX));
	}

	void setTimeTotal(ShipObject* ship) {
		const auto& sTransform = ship->getCurrentTransform();
		const auto& sPosition = sTransform.getPosition();
		const auto& sRotation = sTransform.getRotation();
		const auto& dPosition = dockTransform.getPosition();
		const auto& dRotation = dockTransform.getRotation();

		float pTime = 0.f;
		float rTime = 0.f;

		if (sPosition != dPosition) {
			pTime = sPosition.distanceTo(dPosition) / Math::max(dockTransform.getSpeed(), 1.f);
		}

		if (sRotation != dRotation) {
			rTime = SpaceMath::getRotationTime(dRotation, sRotation, ship->getEngineYawRate(), ship->getEnginePitchRate());
		}

		timeTotal = Math::clamp((float)DURATION_MIN, Math::max(pTime, rTime), (float)DURATION_MAX);
	}

	bool checkLineOfSight(ShipObject* ship, ShipObject* target) {
		auto appearance = target->getAppearanceTemplate();

		if (appearance == nullptr) {
			return false;
		}

		const auto& dPosition = dockTransform.getPosition();
		const auto& sPosition = ship->getPosition();
		const auto& tPosition = target->getPosition();
		const auto& tRotation = *target->getRotationMatrix();

		Vector3 localStart = SpaceMath::getLocalVector(sPosition - tPosition, tRotation);
		Vector3 localEnd = SpaceMath::getLocalVector(dPosition - tPosition, tRotation);
		Vector3 localDir = localEnd - localStart;
		float distance = SpaceMath::qNormalize(localDir);

		auto ray = Ray(localStart, localDir);
		SortedVector<IntersectionResult> results;
		appearance->intersects(ray, distance, results);

		if (results.size() > 0) {
			float intersection = results.getUnsafe(0).getIntersectionDistance();
			float difference = distance - intersection;
			float radius = ship->getBoundingRadius();

			if (difference > radius) {
				return false;
			}
		}

		return true;
	}

	void initializeDocking(ShipObject* ship, ShipObject* target);

	void updateTransform(ShipObject* ship, ShipObject* target);

	void finalizeDocking(ShipObject* ship, ShipObject* target);

	void notifyObservers(ShipObject* ship, ShipObject* target);

	void sendSystemMessage(ShipObject* ship, const String& string);

	void sendEffectMessage(ShipObject* ship, const String& effect);
};

#endif // SHIPDOCKINGTASK_H_
