/*
*
* ShipDeltaVector.cpp
*
*/

#include "server/zone/objects/ship/ShipDeltaVector.h"
#include "server/zone/objects/ship/ShipObject.h"

void ShipDeltaVector::sendMessages(ShipObject* ship) {
	Locker lock(&deltaMutex);

	auto owner = ship->getOwner().get();

	for (int i = 0; i < deltaVector.size(); ++i) {
		auto deltaID = deltaVector.elementAt(i).getKey();
		auto message = deltaVector.elementAt(i).getValue();

		if (message == nullptr) {
			continue;
		}

		message->close();

		int deltaType = getDeltaType(deltaID);

		if (deltaType == DeltaType::Private) {
			if (owner != nullptr) {
				owner->sendMessage(message->clone());
			}

			ship->sendMembersBaseMessage(message->clone(), false);
		} else if (deltaType == DeltaType::Public) {
			ship->broadcastMessage(message->clone(), true);
		}
	}

	reset();
}
