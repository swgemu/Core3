/*
 * LotteryWindowCallback.h
 *
 *  Created on: Mar 16, 2015
 *      Author: swgemu
 */

#ifndef LOTTERYWINDOWCALLBACK_H_
#define LOTTERYWINDOWCALLBACK_H_


#include "server/zone/packets/MessageCallback.h"

class LotteryWindowCallback : public MessageCallback {
	uint64 containerID;

	uint32 listSize;
	Vector<uint64> lootIDs;

	ObjectControllerMessageCallback* objectControllerMain;

public:
	LotteryWindowCallback(ObjectControllerMessageCallback* objectControllerCallback) :
		MessageCallback(objectControllerCallback->getClient(), objectControllerCallback->getServer()),
		containerID(0), listSize(0), objectControllerMain(objectControllerCallback) {
	}

	void parse(Message* msg) {
		msg->parseInt();
		containerID = msg->parseLong();
		listSize = msg->parseInt();

		for (int i = 0; i < listSize; i++)
			lootIDs.add(msg->parseLong());
	}

	void run() {
	}
};


#endif /* LOTTERYWINDOWCALLBACK_H_ */
