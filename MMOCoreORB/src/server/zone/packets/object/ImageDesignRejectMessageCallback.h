/*
 * ImageDesignMessageCallback.h
 *
 *  Created on: 02/02/2011
 *      Author: Polonel
 */

#ifndef IMAGEDESIGNREJECTMESSAGECALLBACK_H_
#define IMAGEDESIGNREJECTMESSAGECALLBACK_H_

#include "ObjectControllerMessageCallback.h"
#include "ImageDesignMessage.h"
#include "server/zone/objects/player/sessions/ImageDesignSession.h"

class ImageDesignRejectMessageCallback : public MessageCallback {
	uint64 designer;
	uint64 target;
	uint64 tent;
	uint8 type;

	ImageDesignData data;

	ObjectControllerMessageCallback* objectControllerMain;

public:
	ImageDesignRejectMessageCallback(ObjectControllerMessageCallback* objectControllerCallback) :
			MessageCallback(objectControllerCallback->getClient(), objectControllerCallback->getServer()) {

		objectControllerMain = objectControllerCallback;

	}

	void parse(Message* message) {
		message->shiftOffset(4);//?
		designer = message->parseLong();
		target = message->parseLong();
		tent = message->parseLong();
		type = message->parseByte();

		data.parse(message);
	}

	void run() {
		ManagedReference<CreatureObject*> player = (CreatureObject*) client->getPlayer();

		if (player == NULL)
			return;

		ManagedReference<Facade*> facade = player->getActiveSession(SessionFacadeType::IMAGEDESIGN);
		ManagedReference<ImageDesignSession*> session = dynamic_cast<ImageDesignSession*>(facade.get());

		if (session == NULL)
			return;

		session->cancelImageDesign(designer, target, tent, type, data);
	}
};


#endif /* IMAGEDESIGNREJECTMESSAGECALLBACK_H_ */
