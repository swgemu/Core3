
#ifndef COAMESSAGEFRAGMENTSUICALLBACK_H_
#define COAMESSAGEFRAGMENTSUICALLBACK_H_

#include "server/zone/objects/player/sui/SuiCallback.h"
#include "server/zone/objects/tangible/components/generic/CoaMessageDataComponent.h"

class CoaMessageFragmentSuiCallback : public SuiCallback {

public:
	CoaMessageFragmentSuiCallback(ZoneServer* serv) :
		SuiCallback(serv) {

	}

	void run(CreatureObject* player, SuiBox* suiBox, uint32 eventIndex, Vector<UnicodeString>* args) {
		bool cancelPressed = (eventIndex == 1);

		if (cancelPressed) {
			return;
		}

		TangibleObject* usingObject = suiBox->getUsingObject().get().castTo<TangibleObject*>();

		if (usingObject == NULL || usingObject->getObjectTemplate()->getFullTemplateString() != "object/tangible/encoded_disk/message_fragment_base.iff") {
			return;
		}

		if (!usingObject->isASubChildOf(player)) {
			player->sendSystemMessage("@encoded_disk/message_fragment:sys_not_in_inv"); // The disk can't be used unless it is in your inventory!
			return;
		}

		TangibleObject* partOne = NULL;
		TangibleObject* partTwo = NULL;
		TangibleObject* partThree = NULL;
		TangibleObject* partFour = NULL;

		String usingObjectName = usingObject->getCustomObjectName().toString();
		String usingObjectFaction = "";

		if (usingObjectName.contains("[1/4]")) {
			partOne = usingObject;
		} else if (usingObjectName.contains("[2/4]")) {
			partTwo = usingObject;
		} else if (usingObjectName.contains("[3/4]")) {
			partThree = usingObject;
		} else if (usingObjectName.contains("[4/4]")) {
			partFour = usingObject;
		}

		if (usingObjectName.contains("Imperial")) {
			usingObjectFaction = "Imperial";
		} else if (usingObjectName.contains("Rebel")) {
			usingObjectFaction = "Rebel";
		}

		if (usingObjectFaction.isEmpty() || (partOne == NULL && partTwo == NULL && partThree == NULL && partFour == NULL)) {
			return;
		}

		SceneObject* inventory = player->getSlottedObject("inventory");

		if (inventory == NULL) {
			return;
		}

		for (int i = 0; i < inventory->getContainerObjectsSize(); i++) {
			TangibleObject* item = inventory->getContainerObject(i).castTo<TangibleObject*>();

			if (item == NULL || item->getObjectTemplate()->getFullTemplateString() != "object/tangible/encoded_disk/message_fragment_base.iff") {
				continue;
			}

			String itemName = item->getCustomObjectName().toString();

			if (!itemName.contains(usingObjectFaction)) {
				continue;
			}

			if (itemName.contains("[1/4]")) {
				if (partOne == NULL) {
					partOne = item;
				}
			} else if (itemName.contains("[2/4]")) {
				if (partTwo == NULL) {
					partTwo = item;
				}
			} else if (itemName.contains("[3/4]")) {
				if (partThree == NULL) {
					partThree = item;
				}
			} else if (itemName.contains("[4/4]")) {
				if (partFour == NULL) {
					partFour = item;
				}
			}
		}

		if (partOne == NULL || partTwo == NULL || partThree == NULL || partFour == NULL) {
			player->sendSystemMessage("@encoded_disk/message_fragment:sys_not_all_parts"); // You don't have all of the fragments of this message.
			return;
		}

		Locker pOneLocker(partOne);
		Locker pTwoLocker(partTwo);
		Locker pThreeLocker(partThree);
		Locker pFourLocker(partFour);

		String fullTemplate = "object/tangible/encoded_disk/message_assembled_base.iff";
		ManagedReference<TangibleObject*> assembledMessage = server->createObject(fullTemplate.hashCode(), 1).castTo<TangibleObject*>();

		if (assembledMessage == NULL) {
			return;
		}

		Locker assembledMessageLocker(assembledMessage);

		CoaMessageDataComponent* data = assembledMessage->getDataObjectComponent()->castTo<CoaMessageDataComponent*>();

		if (data == NULL) {
			assembledMessage->destroyObjectFromDatabase(true);
			return;
		}

		if (usingObjectFaction == "Imperial") {
			data->setFaction("Imperial");
			StringId stringId("encoded_disk/message_fragment", "name_eventimp1");
			assembledMessage->setObjectName(stringId, false);
		} else if (usingObjectFaction == "Rebel") {
			data->setFaction("Rebel");
			StringId stringId("encoded_disk/message_fragment", "name_eventreb1");
			assembledMessage->setObjectName(stringId, false);
		}

		data->setNumber(System::random(20) + 1);

		partOne->destroyObjectFromWorld(true);
		partOne->destroyObjectFromDatabase();
		partTwo->destroyObjectFromWorld(true);
		partTwo->destroyObjectFromDatabase();
		partThree->destroyObjectFromWorld(true);
		partThree->destroyObjectFromDatabase();
		partFour->destroyObjectFromWorld(true);
		partFour->destroyObjectFromDatabase();

		inventory->transferObject(assembledMessage, -1, true);

		assembledMessage->sendTo(player, true);

		player->sendSystemMessage("@encoded_disk/message_fragment:sys_message_assembled"); // You successfully assemble the fragments into a single file.
	}
};


#endif /* COAMESSAGEFRAGMENTSUICALLBACK_H_ */
