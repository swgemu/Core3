/*
 * SendMailTask.h
 *
 *  Created on: 14/01/2013
 *      Author: victor
 */

#ifndef SENDMAILTASK_H_
#define SENDMAILTASK_H_

#include "engine/engine.h"

#include "server/zone/objects/creature/CreatureObject.h"
#include "PersistentMessage.h"

class SendMailTask : public Task {
	ManagedReference<CreatureObject*> receiver;
	ManagedReference<PersistentMessage*> mail;
	UnicodeString senderName;
public:
	SendMailTask(CreatureObject* receiver, PersistentMessage* mail, const UnicodeString& sender) {
		this->receiver = receiver;
		this->mail = mail;
		senderName = sender;
	}

	void run() {
		Locker locker(receiver);

		PlayerObject* ghost = receiver->getPlayerObject();

		ghost->addPersistentMessage(mail->getObjectID());

		if (receiver->isOnline())
			mail->sendTo(receiver, false);
	}
};


#endif /* SENDMAILTASK_H_ */
