/*
 * WaypointChatParameter.h
 *
 *  Created on: Nov 12, 2010
 *      Author: crush
 */

#ifndef WAYPOINTCHATPARAMETER_H_
#define WAYPOINTCHATPARAMETER_H_

#include "server/chat/ChatParameter.h"

namespace server {
namespace zone {
namespace objects {
namespace waypoint {
	class WaypointObject;
}
}
}
}

using namespace server::zone::objects::waypoint;

namespace server {
namespace chat {

class WaypointChatParameter : public ChatParameter, public Serializable {
protected:
	UnicodeString waypointName;
	uint64 pointerParameter;
	uint64 cellID;
	uint32 planetCRC;
	uint32 unknownInt;
	float positionX;
	float positionY;
	float positionZ;
	byte color;
	bool active;

	inline void addSerializableVariables() {
		addSerializableVariable("waypointName", &waypointName);
		addSerializableVariable("pointerParameter", &pointerParameter);
		addSerializableVariable("cellID", &cellID);
		addSerializableVariable("planetCRC", &planetCRC);
		addSerializableVariable("unknownInt", &unknownInt);
		addSerializableVariable("positionX", &positionX);
		addSerializableVariable("positionY", &positionY);
		addSerializableVariable("positionZ", &positionZ);
		addSerializableVariable("color", &color);
		addSerializableVariable("active", &active);
	}

	void insertHeaderToMessage(Message* message) {
		message->insertByte(TYPE_WAYPOINT);
		message->insertInt(WAYPOINT);
	}

	void addToPacketStream(Message* packet);

public:
	WaypointChatParameter();
	WaypointChatParameter(WaypointObject* waypoint);
	WaypointChatParameter(const WaypointChatParameter& custom);

	WaypointChatParameter& operator=(const WaypointChatParameter& par) {
		if (this == &par)
			return *this;

		waypointName = par.waypointName;
		pointerParameter = par.pointerParameter;
		cellID = par.cellID;
		planetCRC = par.planetCRC;
		unknownInt = par.unknownInt;
		positionX = par.positionX;
		positionY = par.positionY;
		positionZ = par.positionZ;
		color = par.color;
		active = par.active;

		return *this;
	}

	void parse(Message* message);

	void set(WaypointObject* waypoint);
	void set(const UnicodeString& name, float x, float z, float y, uint32 planetcrc, uint64 pointer = 0, uint64 cellid = 0, byte clr = 1, bool actv = false);

	inline UnicodeString& getWaypointName() {
		return waypointName;
	}

	inline uint64 getPointerParameter() {
		return pointerParameter;
	}

	inline uint64 getCellID() {
		return cellID;
	}

	inline uint32 getPlanetCRC() {
		return planetCRC;
	}

	inline uint32 getUnknownInt() {
		return unknownInt;
	}

	inline float getPositionX() {
		return positionX;
	}

	inline float getPositionY() {
		return positionY;
	}

	inline float getPositionZ() {
		return positionZ;
	}

	inline byte getColor() {
		return color;
	}

	inline bool isActive() {
		return active;
	}
};

}
}

using namespace server::chat;


#endif /* WAYPOINTCHATPARAMETER_H_ */
