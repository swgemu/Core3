#ifndef TRANSFORM_H_
#define TRANSFORM_H_

//#define TRANSFORM_DEBUG

#include "server/zone/objects/creature/CreatureObject.h"

#ifdef TRANSFORM_DEBUG
#include "server/zone/packets/ui/CreateClientPathMessage.h"
#include "server/zone/packets/object/ShowFlyText.h"
#endif // TRANSFORM_DEBUG

class Transform {
protected:
	uint32 timeStamp;
	uint32 moveCount;
	uint64 parentID;

	Quaternion direction;
	Vector3 position;

	float speed;

public:
	const static constexpr float POSITIONMOD = 6.f; // broadcast position update distance multiplier

	const static int MINDELTA = 200; // minimum ms elapsed between updates
	const static int MIDDELTA = 400; // ideal ms between low priority update
	const static int MAXDELTA = 800; // maximum ms before high priority update

	const static int SYNCDELTA = 10000; // minimum ms before synchronize update
	const static int SYNCCOUNT = 50; // minimum moveCount for synchronize update

	Transform() {
		timeStamp = 0u;
		moveCount = 0u;
		parentID = 0ul;

		speed = 0.f;
	}

	void parseDataTransform(Message* message) {
		timeStamp = message->parseInt();
		moveCount = message->parseInt();

		parseDirection(message);
		parsePosition(message);

		speed = message->parseFloat();
	}

	void parseDataTransformWithParent(Message* message) {
		timeStamp = message->parseInt();
		moveCount = message->parseInt();
		parentID = message->parseLong();

		parseDirection(message);
		parsePosition(message);

		speed = message->parseFloat();
	}

	void parseDirection(Message* message) {
		float x = Math::clamp(-1.f, message->parseFloat(), 1.f);
		float y = Math::clamp(-1.f, message->parseFloat(), 1.f);
		float z = Math::clamp(-1.f, message->parseFloat(), 1.f);
		float w = Math::clamp(-1.f, message->parseFloat(), 1.f);

		direction.set(w,x,y,z);
	}

	void parsePosition(Message* message) {
		float x = message->parseFloat();
		float z = message->parseFloat();
		float y = message->parseFloat();

		position.set(x,z,y);
	}

	uint32 getTimeStamp() const {
		return timeStamp;
	}

	uint32 getMoveCount() const {
		return moveCount;
	}

	uint64 getParentID() const {
		return parentID;
	}

	float getPositionX() const {
		return position.getX();
	}

	float getPositionY() const {
		return position.getY();
	}

	float getPositionZ() const {
		return position.getZ();
	}

	float getSpeed() const {
		return speed;
	}

	const Vector3& getPosition() const {
		return position;
	}

	const Quaternion& getDirection() const {
		return direction;
	}

	bool isPositionValid() const {
#ifdef PLATFORM_WIN
#undef isnan
#undef isinf
#endif // PLATFORM_WIN
		if (std::isnan(position.getX()) || std::isinf(position.getX()) || std::isnan(position.getY()) || std::isinf(position.getY()) || std::isnan(position.getZ()) || std::isinf(position.getZ())) {
			return false;
		}

		if (parentID == 0) {
			if (position.getX() > 7680.f || position.getX() < -7680.f || position.getY() > 7680.f || position.getY() < -7680.f || position.getZ() > 7680.f || position.getZ() < -7680.f) {
				return false;
			}
		} else {
			if (position.getX() > 1024.f || position.getX() < -1024.f || position.getY() > 1024.f || position.getY() < -1024.f || position.getZ() > 1024.f || position.getZ() < -1024.f) {
				return false;
			}
		}

		return true;
	}

	bool isPostureValid(int posture) const {
		switch (posture) {
		case 0: // CreaturePosture::UPRIGHT
		case 1: // CreaturePosture::CROUCHED
		case 2: // CreaturePosture::PRONE
		case 3: // CreaturePosture::SNEAKING
		case 8: // CreaturePosture::SITTING
		case 9: // CreaturePosture::SKILLANIMATING
			return true;
		default:
			return false;
		}
	}

	bool isInertiaUpdate(const Vector3& creoPosition, const Quaternion* creoDirection, float creoSpeed) const {
		return speed != creoSpeed || isYawUpdate(creoDirection) || getSquaredMoveScale(creoPosition, 1) < 0.975f;
	}

	bool isSynchronizeUpdate(const Quaternion* creoDirection, float creoSpeed) const {
		return moveCount >= SYNCCOUNT && speed == 0.f && creoSpeed == 0.f && !isYawUpdate(creoDirection);
	}

	bool isYawUpdate(const Quaternion* creoDirection) const {
		float deltaW = creoDirection->getW() - direction.getW();
		float deltaY = creoDirection->getY() - direction.getY();

		return deltaW > 0.001f || deltaW < -0.001f || deltaY > 0.001f || deltaY < -0.001f;
	}

	float get2dSquaredDistance(const Vector3& creoPosition) const {
		float deltaX = creoPosition.getX() - position.getX();
		float deltaY = creoPosition.getY() - position.getY();

		return (deltaX * deltaX) + (deltaY * deltaY);
	}

	float getSquaredMoveScale(const Vector3& creoPosition, float interval) const {
		float sqrDistance = get2dSquaredDistance(creoPosition);
		float range = speed * interval * 0.2f;
		float sqrRange = range * range;

		return sqrDistance > sqrRange ? (sqrRange / sqrDistance) : (sqrDistance / sqrRange);
	}

	float getMoveScale(const Vector3& creoPosition, float interval) const {
		float distance = sqrt(get2dSquaredDistance(creoPosition));
		float range = speed * interval * 0.2f;

		return distance > range ? (range / distance) : (distance / range);
	}

	float getTurnScale(const Quaternion* creoDirection, float radians) const {
		float deltaR = (radians - creoDirection->getRadians()) * M_1_PI;

		return deltaR > 1.f ? (deltaR - 2.f) : deltaR < -1.f ? (deltaR + 2.f) : (deltaR);
	}

	Vector3 predictPosition(const Vector3& creoPosition, const Quaternion* creoDirection, int deltaTime) const {
		if (speed < 1.f || deltaTime > MAXDELTA) {
			return position;
		}

		float interval = (int)(deltaTime * 0.005f);
		float vector = POSITIONMOD;

		vector *= (getMoveScale(creoPosition, interval) * 2.f) -1.f;

		float deltaX = position.getX() - creoPosition.getX();
		float deltaY = position.getY() - creoPosition.getY();

		if (speed > 2.f && isYawUpdate(creoDirection)) {
			float deltaR = getTurnScale(creoDirection, atan2(deltaX, deltaY)) * M_PI_2;

			vector *= 1.f - (deltaR < 0.f ? (-deltaR) : (deltaR));

			if (deltaR < M_PI_4 && deltaR > -M_PI_4) {
				float cosR = Math::cos(deltaR);
				float sinR = Math::sin(deltaR);

				deltaX = (deltaX * cosR) + (deltaY * sinR);
				deltaY = (-deltaX * sinR) + (deltaY * cosR);
			}
		}

		if (vector <= interval || vector > POSITIONMOD) {
			return position;
		}

		if (interval > 1.f) {
			vector /= interval;
		}

		float x = (deltaX * vector) + creoPosition.getX();
		float y = (deltaY * vector) + creoPosition.getY();

		return Vector3(x, y, position.getZ());
	}

#ifdef TRANSFORM_DEBUG
	void sendDebug(CreatureObject* creature, const String& message, const Vector3& newPosition, int deltaTime) const {
		if (message.isEmpty()) {
			return;
		}

		sendFlyText(creature, message, deltaTime);

		if (!message.beginsWith("info") && !message.beginsWith("warning")) {
			sendPathMessage(creature, newPosition);
		}

		if (message.beginsWith("warning") || message.beginsWith("error")) {
			sendSystemMessage(creature, newPosition, message, deltaTime);
		}
	}

	void sendFlyText(CreatureObject* creature, const String& type, int deltaTime) const {
		if (creature == nullptr)
			return;

		int r = 128;
		int g = 128;
		int b = 128;

		if (type.beginsWith("sta")) { // static
			g = b = 0;
		} else if (type.beginsWith("pos")) { // position
			r = b = 0;
		} else if (type.beginsWith("pre")) { // prediction
			r = g = 0;
		} else if (type.beginsWith("syn")) { // synchronize
			r = 0;
		} else if (type.beginsWith("err")) { // error
			g = 0;
		} else if (type.beginsWith("war")) { // warning
			b = 0;
		} else if (type.beginsWith("inf")) { // info
			r = g = b = 64;
		}

		auto flyText = new ShowFlyText(creature, type, String::valueOf(deltaTime) + "/ms", r, g, b, 0.5f);
		creature->sendMessage(flyText);
	}

	void sendPathMessage(CreatureObject* creature, const Vector3& newPosition) const {
		if (creature == nullptr)
			return;

		if (parentID != 0.f) {
			return;
		}

		PlayerObject* ghost = creature->getPlayerObject();

		if (ghost == nullptr) {
			return;
		}

		const Vector3& validated = ghost->getLastValidatedPosition()->getPosition();
		const uint64& validParent = ghost->getLastValidatedPosition()->getParent();
		if (validParent != 0) {
			return;
		}

		auto path = new CreateClientPathMessage();

		path->addCoordinate(validated.getX(), validated.getZ(), validated.getY());
		path->addCoordinate(creature->getPositionX(), creature->getPositionZ(), creature->getPositionY());
		path->addCoordinate(position.getX(), position.getZ() , position.getY() );
		path->addCoordinate(newPosition.getX(), newPosition.getZ(), newPosition.getY());

		creature->sendMessage(path);
	}

	void sendSystemMessage(CreatureObject* creature, const Vector3& newPosition, const String& type, int deltaTime) const {
		PlayerObject* ghost = creature->getPlayerObject();

		if (ghost == nullptr) {
			return;
		}

		const Vector3& validated = ghost->getLastValidatedPosition()->getPosition();
		const uint64& validParent = ghost->getLastValidatedPosition()->getParent();

		StringBuffer msg;

		msg << "Transform: "
			<< " Position: " << newPosition.getX()  << ", " << newPosition.getZ()  << ", " << newPosition.getY()
			<< " DeltaTime: " << deltaTime
			<< " Type: " << type
			<< endl
			<< "Parsed: "
			<< " Position: " << position.getX()  << ", " << position.getZ()  << ", " << position.getY()
			<< " Direction: " << direction.getW()  << ", " << direction.getX()  << ", " << direction.getY() << ", " << direction.getZ()
			<< " MoveCount: " << moveCount
			<< " ParentID: " << parentID
			<< " Speed:	" << speed
			<< endl
			<< "Current: "
			<< " Position: " << creature->getPositionX() << ", " << creature->getPositionZ() << ", " << creature->getPositionY()
			<< " Direction: " << creature->getDirectionW() << ", " << creature->getDirectionX() << ", " << creature->getDirectionY() << ", " << creature->getDirectionZ()
			<< " MoveCount: " << creature->getMovementCounter()
			<< " ParentID: " << creature->getParentID()
			<< " Speed: " << creature->getCurrentSpeed()
			<< endl
			<< "Validated: "
			<< " Position: " << validated.getX() << ", " << validated.getZ() << ", " << validated.getY()
			<< " ParentID: " << validParent
			<< " Zone: " << ghost->getSavedTerrainName()
			<< endl

			<< "--------------------------------";

		creature->sendSystemMessage(msg.toString());
	}
#endif // TRANSFORM_DEBUG
};

#endif // TRANSFORM_H_
