#ifndef DELTAAUTOMAP_H_
#define DELTAAUTOMAP_H_

#include "DeltaVectorMap.h"
#include "server/zone/packets/DeltaMessage.h"
#include "server/zone/objects/scene/SceneObject.h"

template <class K, class V, int BaselineName, uint8 Type, int DeltaID>
class DeltaAutoMap : public DeltaVectorMap<K,V> {
public:
	DeltaAutoMap() : DeltaVectorMap<K,V>() {
		DeltaVectorMap<K,V>::setNullValue(V());
	}

	void update(const K& key, const V& value, DeltaMessage* message = nullptr, uint8 command = DeltaMapCommands::ADD) {
		if (message != nullptr) {
			message->startUpdate(DeltaID);
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
		message->startUpdate(DeltaID);
		DeltaVectorMap<K,V>::insertToMessage(message);
	}
};

#endif // DELTAAUTOMAP_H_
