#ifndef DELTAAUTOVARIABLE_H_
#define DELTAAUTOVARIABLE_H_

#include "DeltaBasicVariable.h"
#include "server/zone/packets/DeltaMessage.h"
#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/ship/ShipDeltaVector.h"

template<typename K, int BaselineName, uint8 DeltaType, int DeltaIndex>
class DeltaAutoVariable : public DeltaBasicVariable<K> {
public:
	DeltaAutoVariable() {
		DeltaBasicVariable<K>::object = K();
	}

	void update(const K& value, bool notifyClient = false, SceneObject* sceneObject = nullptr, DeltaMessage* message = nullptr, ShipDeltaVector* vector = nullptr) {
		DeltaBasicVariable<K>::set(value);

		if (message != nullptr) {
			addToDeltaMessage(message);
			return;
		}

		if (vector != nullptr) {
			addToDeltaMessage(vector);
			return;
		}

		if (sceneObject != nullptr && notifyClient) {
			broadcastStandaloneDeltaMessage(sceneObject);
			return;
		}
	}

	void broadcastStandaloneDeltaMessage(SceneObject* sceneObject) {
		DeltaMessage* message = new DeltaMessage(sceneObject->getObjectID(), BaselineName, DeltaType);
		addToDeltaMessage(message);
		message->close();

		sceneObject->broadcastMessage(message, true);
	}

	void addToDeltaMessage(DeltaMessage* message) {
		message->startUpdate(DeltaIndex);
		DeltaBasicVariable<K>::toBinaryStream(message);
	}

	void addToDeltaMessage(ShipDeltaVector* vector) {
		auto message = vector->getMessage(DeltaType);

		if (message != nullptr) {
			addToDeltaMessage(message);
		}
	}
};

#endif // DELTAAUTOVARIABLE_H_
