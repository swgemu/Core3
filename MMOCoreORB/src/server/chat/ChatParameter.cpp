/*
 * ChatParameter.cpp
 *
 *  Created on: Nov 9, 2010
 *      Author: crush
 */

#include "ChatParameter.h"

ChatParameter::ChatParameter() {
}

ChatParameter::ChatParameter(const ChatParameter& cp) : Object() {
}

void ChatParameter::insertToMessage(Message* message) {
	int offset = message->getOffset();

	message->insertShort(0);

	insertHeaderToMessage(message);

	addToPacketStream(message);

	if ((message->getOffset() - offset) & 1) {
		message->insertByte(0);
		message->insertShort(offset, 1);
	}
}
