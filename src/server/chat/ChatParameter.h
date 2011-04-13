/*
 * ChatParameter.h
 *
 *  Created on: Nov 9, 2010
 *      Author: crush
 */

#ifndef CHATMESSAGEPARAMETER_H_
#define CHATMESSAGEPARAMETER_H_

#include "engine/engine.h"

namespace server {
namespace chat {

class ChatParameter : public virtual Object {
protected:
	virtual void addToPacketStream(Message* packet) = 0;

	virtual void insertHeaderToMessage(Message* message) {
		message->insertByte(TYPE_STRINGID);
		message->insertInt(STRINGID);
	}

public:
	static const byte TYPE_STRINGID = 1;
	static const byte TYPE_WAYPOINT = 4;

	static const int STRINGID = 0xFFFFFFFF;
	static const int WAYPOINT = 0xFFFFFFFD;

	ChatParameter();
	ChatParameter(const ChatParameter& id);

	ChatParameter& operator=(const ChatParameter& id) {
		if (&id == this)
			return *this;

		return *this;
	}

	void insertToMessage(Message* message);
	virtual void parse(Message* message) = 0;

	inline bool isStringIdParameter() {
		return false;
	}

	inline bool isWaypointParameter() {
		return false;
	}
};

}
}
using namespace server::chat;

#endif /* CHATMESSAGEPARAMETER_H_ */
