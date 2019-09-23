/*
 * WaypointChatParameter.h
 *
 *  Created on: Nov 12, 2010
 *      Author: crush
 */

#ifndef WAYPOINTCHATPARAMETER_H_
#define WAYPOINTCHATPARAMETER_H_

#include "server/chat/ChatParameter.h"

#include "engine/util/json_utils.h"

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

	void insertHeaderToMessage(Message* message) const override {
		message->insertByte(TYPE_WAYPOINT);
		message->insertInt(WAYPOINT);
	}

	void addToPacketStream(Message* packet) const override;

public:
	WaypointChatParameter();
	WaypointChatParameter(WaypointObject* waypoint);
	WaypointChatParameter(const WaypointChatParameter& custom);

	friend void to_json(nlohmann::json& j, const WaypointChatParameter& p) {
		j["waypointName"] = p.waypointName;
		j["pointerParameter"] = p.pointerParameter;
		j["cellID"] = p.cellID;
		j["planetCRC"] = p.planetCRC;
		j["unknownInt"] = p.unknownInt;
		j["positionX"] = p.positionX;
		j["positionY"] = p.positionY;
		j["positionZ"] = p.positionZ;
		j["color"] = p.color;
		j["active"] = p.active;
       	}

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

	void parse(Message* message) override;

	void set(WaypointObject* waypoint);
	void set(const UnicodeString& name, float x, float z, float y, uint32 planetcrc, uint64 pointer = 0, uint64 cellid = 0, byte clr = 1, bool actv = false);

	inline const UnicodeString& getWaypointName() const {
		return waypointName;
	}

	inline uint64 getPointerParameter() const {
		return pointerParameter;
	}

	inline uint64 getCellID() const {
		return cellID;
	}

	inline uint32 getPlanetCRC() const {
		return planetCRC;
	}

	inline uint32 getUnknownInt() const {
		return unknownInt;
	}

	inline float getPositionX() const {
		return positionX;
	}

	inline float getPositionY() const {
		return positionY;
	}

	inline float getPositionZ() const {
		return positionZ;
	}

	inline byte getColor() const {
		return color;
	}

	inline bool isActive() const {
		return active;
	}
};

}
}

using namespace server::chat;


#endif /* WAYPOINTCHATPARAMETER_H_ */
