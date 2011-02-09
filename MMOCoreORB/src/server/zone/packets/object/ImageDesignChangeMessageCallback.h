/*
 * ImageDesignMessageCallback.h
 *
 *  Created on: 02/02/2011
 *      Author: Polonel
 */

#ifndef IMAGEDESIGNCHANGEMESSAGECALLBACK_H_
#define IMAGEDESIGNCHANGEMESSAGECALLBACK_H_

#include "ObjectControllerMessageCallback.h"
#include "ImageDesignMessage.h"
#include "server/zone/objects/player/ImageDesignSession.h"

class ImageDesignChangeMessageCallback : public MessageCallback {
	uint64 designer;
	uint64 target;
	uint64 tent;
	uint8 type;

	String hairObject;

	String ukstring1;
	uint32 ukint1;

	uint32 timestamp;
	uint32 requiredPayment;
	uint32 offeredPayment;

	uint8 designerAccepted;
	uint8 targetAccepted;

	uint8 statMigration;

	//unknowns
	uint32 ukint4;
	uint32 ukint5;
	uint32 ukint6;
	uint32 ukint7;

	uint32 sizeFloatAttrs;

	uint32 attributesSize;

	String holoEmote;

	VectorMap<String, float> floatMap;

	VectorMap<String, uint32> colorMap;

	ObjectControllerMessageCallback* objectControllerMain;


public:
	ImageDesignChangeMessageCallback(ObjectControllerMessageCallback* objectControllerCallback) :
			MessageCallback(objectControllerCallback->getClient(), objectControllerCallback->getServer()) {

		objectControllerMain = objectControllerCallback;

	}

	void parse(Message* message) {
		message->shiftOffset(4);
		designer = message->parseLong();
		target = message->parseLong();
		tent = message->parseLong();

		type = message->parseByte();

		message->parseAscii(hairObject);
		message->parseAscii(ukstring1);

		ukint1 = message->parseInt();
		timestamp = message->parseInt();

		requiredPayment = message->parseInt();
		offeredPayment = message->parseInt();

		designerAccepted = message->parseByte();
		targetAccepted = message->parseInt();

		statMigration = message->parseByte();

		ukint4 = message->parseInt();
		ukint5 = message->parseInt();
		ukint6 = message->parseInt();
		ukint7 = message->parseInt();

		sizeFloatAttrs = message->parseInt();

		if(sizeFloatAttrs > 0) {
			for (int i = 0; i < sizeFloatAttrs; i++) {
				String attr;
				message->parseAscii(attr);
				float val = message->parseFloat();

				floatMap.put(attr,val);
			}
		}

		attributesSize = message->parseInt();

		if(attributesSize > 0) {
			for (int i = 0; i < attributesSize; i++) {
				String attr;
				message->parseAscii(attr);
				uint32 val = message->parseInt();

				colorMap.put(attr,val);
			}
		}

		message->parseAscii(holoEmote);

	}

	void run() {
		ManagedReference<PlayerCreature*> player = (PlayerCreature*) client->getPlayer();

		if(player == NULL)
			return;

		ManagedReference<Facade*> facade = player->getActiveSession(SessionFacadeType::IMAGEDESIGN);
		ManagedReference<ImageDesignSession*> session = dynamic_cast<ImageDesignSession*>(facade.get());

		if(session == NULL)
			return;

		session->setHairObject(hairObject);
		session->setUkstring1(ukstring1);
		session->setUnknownInt1(ukint1);
		session->setTimeStamp(timestamp);
		session->setRequiredPayment(requiredPayment);
		session->setOfferedPayment(offeredPayment);
		session->setDesignerAccepted(designerAccepted);
		session->setTargetAccepted(targetAccepted);
		session->setStatMigration(statMigration);

		session->setUnknownInt4(ukint4);
		session->setUnknownInt5(ukint5);
		session->setUnknownInt6(ukint6);
		session->setUnknownInt7(ukint7);

		session->setSizeFloatAttrs(sizeFloatAttrs);
		session->setAttributesSize(attributesSize);

		session->setFloatMap(floatMap);
		session->setColorMap(colorMap);
		session->setHoloEmote(holoEmote);

		session->updateImageDesign(player->getObjectID(), designer,target,tent,type);

	}


};


#endif /* IMAGEDESIGNCHANGEMESSAGECALLBACK_H_ */
