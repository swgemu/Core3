#ifndef DELTAAUTOMAP_H_
#define DELTAAUTOMAP_H_

#include "DeltaVectorMap.h"
#include "server/zone/packets/DeltaMessage.h"
#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/ship/ShipDeltaVector.h"

template <class K, class V, int BaselineName, uint8 DeltaType, int DeltaIndex>
class DeltaAutoMap : public DeltaVectorMap<K,V> {
public:
	DeltaAutoMap() : DeltaVectorMap<K,V>() {
		DeltaVectorMap<K,V>::setNullValue(V());
	}

	void update(const K& key, const V& value, DeltaMessage* message = nullptr, uint8 command = DeltaMapCommands::ADD, ShipDeltaVector* vector = nullptr) {
		if (vector != nullptr) {
			message = vector->getMessage(DeltaType);
		}

		if (message != nullptr) {
			message->startUpdate(DeltaIndex);
		}

		if (command == DeltaMapCommands::ADD) {
			DeltaVectorMap<K,V>::add(key, value, message);
		} else if (command == DeltaMapCommands::DROP) {
			DeltaVectorMap<K,V>::drop(key, message);
		} else if (command == DeltaMapCommands::SET) {
			DeltaVectorMap<K,V>::set(key, value, message);
		}
	}

	void addToDeltaMessage(DeltaMessage* message) {
		message->startUpdate(DeltaIndex);
		DeltaVectorMap<K,V>::insertToMessage(message);
	}

	void addToDeltaMessage(ShipDeltaVector* vector) {
		auto message = vector->getMessage(DeltaType);

		if (message != nullptr) {
			addToDeltaMessage(message);
		}
	}
};

#endif // DELTAAUTOMAP_H_
