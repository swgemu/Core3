
#include "FactionRecruiterContainerComponent.h"
#include "server/chat/ChatManager.h"
#include "server/zone/objects/creature/AiAgent.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/objects/tangible/components/generic/CoaMessageDataComponent.h"

int FactionRecruiterContainerComponent::canAddObject(SceneObject* sceneObject, SceneObject* object, int containmentType, String& errorDescription) {

	if (sceneObject == object) {
		return TransferErrorCode::CANTADDTOITSELF;
	}

	if (!sceneObject->isAiAgent()) {
		return TransferErrorCode::INVALIDTYPE;
	}

	AiAgent* recruiter = cast<AiAgent*>(sceneObject);

	String recruiterFaction = recruiter->getFactionString().toLowerCase();

	if (recruiterFaction != "imperial" && recruiterFaction != "rebel") {
		return TransferErrorCode::INVALIDTYPE;
	}

	CreatureObject* player = object->getParentRecursively(SceneObjectType::PLAYERCREATURE).get().castTo<CreatureObject*>();

	if (player == NULL) {
		return TransferErrorCode::MUSTBEINPLAYERINVENTORY;
	}

	if (object != NULL && object->getObjectTemplate()->getFullTemplateString() == "object/tangible/encoded_disk/message_assembled_base.iff") {
		CoaMessageDataComponent* data = object->getDataObjectComponent()->castTo<CoaMessageDataComponent*>();

		if (data != NULL) {
			String faction = data->getFaction().toLowerCase();
			if (faction == "imperial" || faction == "rebel") {
				return TransferErrorCode::SUCCESS;
			}
		}
	}

	return TransferErrorCode::INVALIDTYPE;
}

bool FactionRecruiterContainerComponent::transferObject(SceneObject* sceneObject, SceneObject* object, int containmentType, bool notifyClient, bool allowOverflow) {
	CoaMessageDataComponent* data = object->getDataObjectComponent()->castTo<CoaMessageDataComponent*>();

	if (data == NULL) {
		return false;
	}

	CreatureObject* player = object->getParentRecursively(SceneObjectType::PLAYERCREATURE).get().castTo<CreatureObject*>();

	if (player == NULL) {
		return false;
	}

	ZoneServer* zoneServer = player->getZoneServer();
	PlayerObject* ghost = player->getPlayerObject();

	if (zoneServer == NULL || ghost == NULL) {
		return false;
	}

	if (!sceneObject->isAiAgent()) {
		return false;
	}

	AiAgent* recruiter = cast<AiAgent*>(sceneObject);

	String recruiterFaction = recruiter->getFactionString().toLowerCase();

	bool hasBadge = ghost->hasBadge(Badge::EVENT_PROJECT_DEAD_EYE_1);

	String faction = data->getFaction().toLowerCase();

	StringBuffer response;

	response << "@encoded_disk/message_fragment:response_event";

	if (faction == "rebel") {
		response << "reb1_";
	} else if (faction == "imperial") {
		response << "imp1_";
	}

	response << recruiterFaction;

	ChatManager* chatManager = zoneServer->getChatManager();

	if (chatManager == NULL) {
		return false;
	}

	Locker locker(recruiter);
	chatManager->broadcastMessage(recruiter,response.toString(), 0, 0, 0);

	object->destroyObjectFromWorld(true);
	object->destroyObjectFromDatabase();

	int credits = System::random(500) + 500;
	player->sendSystemMessage("You receive " + String::valueOf(credits) + " credits.");
	player->addCashCredits(credits, true);

	if (!hasBadge) {
		ghost->awardBadge(Badge::EVENT_PROJECT_DEAD_EYE_1);
		ghost->increaseFactionStanding(recruiterFaction, 500);
	}

	return true;
}
