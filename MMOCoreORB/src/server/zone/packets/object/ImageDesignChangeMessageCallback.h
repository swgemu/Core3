/*
 * ImageDesignChangeMessageCallback.h
 *
 *  Created on: 02/02/2011
 *      Author: Polonel
 */

#ifndef IMAGEDESIGNCHANGEMESSAGECALLBACK_H_
#define IMAGEDESIGNCHANGEMESSAGECALLBACK_H_

#include "ObjectControllerMessageCallback.h"
#include "server/zone/objects/player/sessions/ImageDesignSession.h"
#include "server/zone/objects/player/sessions/ImageDesignData.h"

class ImageDesignChangeMessageCallback : public MessageCallback {
	uint64 designerID;
	uint64 targetID;
	uint64 tentID;
	uint8 type;

	ObjectControllerMessageCallback* objectControllerMain;

	ImageDesignData imageDesignData;

public:
	ImageDesignChangeMessageCallback(ObjectControllerMessageCallback* objectControllerCallback) :
		MessageCallback(objectControllerCallback->getClient(), objectControllerCallback->getServer()),
		designerID(0), targetID(0), tentID(0), type(0), objectControllerMain(objectControllerCallback) {

		setLoggingName("ImageDesignChangeMessageCallback");
	}

	void parse(Message* message) {
		message->shiftOffset(4); // ?Not sure this should be here.

		designerID = message->parseLong();
		targetID = message->parseLong();
		tentID = message->parseLong();
		type = message->parseByte();

		//info(true) << "designerID: " << designerID << "targetID: " << targetID << "Type: " << type;

		imageDesignData.parse(message);
	}

	void run() {
		ManagedReference<CreatureObject*> player = client->getPlayer();

		if (player == nullptr)
			return;

		ManagedReference<Facade*> facade = player->getActiveSession(SessionFacadeType::IMAGEDESIGN);
		ManagedReference<ImageDesignSession*> session = dynamic_cast<ImageDesignSession*>(facade.get());

		if (session == nullptr)
			return;

		session->updateImageDesign(player, designerID, targetID, tentID, type, imageDesignData);
	}
};

#endif /* IMAGEDESIGNCHANGEMESSAGECALLBACK_H_ */
