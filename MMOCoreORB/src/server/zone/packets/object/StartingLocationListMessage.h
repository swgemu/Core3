/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef STARTINGLOCATIONLISTMESSAGE_H_
#define STARTINGLOCATIONLISTMESSAGE_H_

#include "ObjectControllerMessage.h"

class StartingLocationListMessage : public ObjectControllerMessage {
public:
	StartingLocationListMessage(CreatureObject* creo)
			: ObjectControllerMessage(creo->getObjectID(), 0x1B, 0x1FC) {

		//Populate with PlayerManager::sendStartingLocationListTo()
	}
};

#endif /*STARTINGLOCATIONLISTMESSAGE_H_*/

