#ifndef DELTAAUTOVARIABLE_H_
#define DELTAAUTOVARIABLE_H_

#include "DeltaBasicVariable.h"
#include "server/zone/packets/DeltaMessage.h"
#include "server/zone/objects/scene/SceneObject.h"

template<typename K, int BaselineName, uint8 Type, int DeltaID>
class DeltaAutoVariable : public DeltaBasicVariable<K> {
public:
	DeltaAutoVariable() {
		DeltaBasicVariable<K>::object = K();
	}

	void update(const K& value, bool notifyClient = false, SceneObject* sceneObject = nullptr, DeltaMessage* message = nullptr) {
		DeltaBasicVariable<K>::set(value);

		if (message != nullptr) {
			addToDeltaMessage(message);
			return;
		}

		if (sceneObject != nullptr && notifyClient) {
			broadcastStandaloneDeltaMessage(sceneObject);
			return;
		}
	}

	void broadcastStandaloneDeltaMessage(SceneObject* sceneObject) {
		DeltaMessage* message = new DeltaMessage(sceneObject->getObjectID(), BaselineName, Type);
		addToDeltaMessage(message);
		message->close();

		sceneObject->broadcastMessage(message, true);
	}

	void addToDeltaMessage(DeltaMessage* message) {
		message->startUpdate(DeltaID);
		DeltaBasicVariable<K>::toBinaryStream(message);
	}
};

#endif // DELTAAUTOVARIABLE_H_
