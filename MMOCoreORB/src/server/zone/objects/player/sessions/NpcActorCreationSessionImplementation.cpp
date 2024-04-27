/*
* NpcActorCreationSessionImplementation.cpp
*
* 2024-04-23
* By: Hakry
*
*/

#include "server/zone/objects/player/sessions/NpcActorCreationSession.h"
#include "server/zone/ZoneServer.h"
#include "server/zone/Zone.h"
#include "server/zone/ZoneProcessServer.h"
#include "server/zone/managers/vendor/VendorSelectionNode.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/managers/vendor/VendorManager.h"
#include "server/zone/objects/player/sessions/sui/NpcActorSuiCallback.h"
#include "server/zone/objects/player/sessions/sui/NameNpcActorSuiCallback.h"
#include "server/zone/objects/tangible/components/EventPerkDataComponent.h"

int NpcActorCreationSessionImplementation::initializeSession() {
	ManagedReference<CreatureObject*> player = weakPlayer.get();
	ManagedReference<EventPerkDeed*> eventPerkDeed = weakPerkDeed.get();

	if (player == nullptr || eventPerkDeed == nullptr) {
		return 0;
	}

	if (player->containsActiveSession(SessionFacadeType::NPCACTORCREATION)) {
		return 0;
	}

	ManagedReference<PlayerObject*> ghost = player->getPlayerObject();
	auto zoneServer = player->getZoneServer();

	if (ghost == nullptr || zoneServer == nullptr) {
		cancelSession();
		return 0;
	}

	// Store the players position, just in case they try to move. The zone name is stored in the constructor
	actorPosition = player->getWorldPosition();

	currentNode = VendorManager::instance()->getRootNode();

	if (!currentNode->hasChildNode()) {
		cancelSession();

		error() << "Vendor Root node has no children in NpcActorCreationSession.";

		return 0;
	}

	// NPC Node
	currentNode = currentNode->getNode(2);

	if (currentNode == nullptr) {
		cancelSession();
		return 0;
	}

	actorSelection = new SuiListBox(player, SuiWindowType::STRUCTURE_CREATE_VENDOR);

	if (actorSelection == nullptr) {
		cancelSession();
		return 0;
	}

	actorSelection->setCallback(new NpcActorSuiCallback(zoneServer));

	actorSelection->setPromptTitle("@event_perk_npc_actor:race_type_t"); // "Select Race"
	actorSelection->setPromptText("@event_perk_npc_actor:race_type_d"); // "Select the race you would like for the actor."

	actorSelection->setCancelButton(true, "@cancel");

	currentNode->addChildrenToListBox(actorSelection, 100);

	ghost->addSuiBox(actorSelection);
	player->sendMessage(actorSelection->generateMessage());

	player->addActiveSession(SessionFacadeType::NPCACTORCREATION, _this.getReferenceUnsafeStaticCast());

	return 0;
}

void NpcActorCreationSessionImplementation::setNpcActorSelection(int menuID) {
	ManagedReference<CreatureObject*> player = weakPlayer.get();

	if (player == nullptr) {
		return;
	}

	auto ghost = player->getPlayerObject();

	if (ghost == nullptr) {
		return;
	}

	actorSelection->clearOptions();
	actorSelection->removeAllMenuItems();

	VendorSelectionNode* node = currentNode->getNode(menuID);

	// Set the title and text off the parent node.
	actorSelection->setPromptTitle("@event_perk_npc_actor:gender_t"); // "Select Gender"
	actorSelection->setPromptText("@event_perk_npc_actor:gender_d"); // "Select the gender of your actor."

	templatePath = templatePath + node->getTemplatePath();

	if (node->hasChildNode()) {
		currentNode = node;
		currentNode->addChildrenToListBox(actorSelection, 100);

		// If there are selections available for vendor type
		if (actorSelection->getMenuSize() != 0) {
			player->sendMessage(actorSelection->generateMessage());
			ghost->addSuiBox(actorSelection);

			return;
		}

		templatePath = templatePath + currentNode->getRandomTemplate(100);

		const char* path = templatePath.toCharArray();

		if (path[strlen(path) - 1] == '_') {
			templatePath = templatePath + (System::random(1) == 0 ? "male.iff" : "female.iff");
		}
	}

	templatePath = "object/mobile/vendor/" + templatePath;

	// Prompt for naming
	promptNameSelection();
}

void NpcActorCreationSessionImplementation::promptNameSelection() {
	ManagedReference<CreatureObject*> player = weakPlayer.get();

	if (player == nullptr) {
		return;
	}

	auto ghost = player->getPlayerObject();

	if (ghost == nullptr) {
		return;
	}

	SuiInputBox* namingBox = new SuiInputBox(player, SuiWindowType::STRUCTURE_NAME_VENDOR);

	if (namingBox == nullptr) {
		cancelSession();
		return;
	}

	namingBox->setCallback(new NameNpcActorSuiCallback(player->getZoneServer()));
	namingBox->setCancelButton(true, "@cancel");

	namingBox->setPromptTitle("@event_perk_npc_actor:name_t"); // "Select Name"
	namingBox->setPromptText("@event_perk_npc_actor:name_d"); // "Enter the name you wish to use for the actor."

	player->sendMessage(namingBox->generateMessage());
	ghost->addSuiBox(namingBox);
}

void NpcActorCreationSessionImplementation::createNpcActor(const String& name) {
	ManagedReference<CreatureObject*> player = weakPlayer.get();
	ManagedReference<EventPerkDeed*> eventPerkDeed = weakPerkDeed.get();

	if (player == nullptr || eventPerkDeed == nullptr) {
		return;
	}

	Locker locker(player);

	auto zoneServer = player->getZoneServer();

	if (zoneServer == nullptr) {
		return;
	}

	auto nameManager = zoneServer->getNameManager();

	if (nameManager == nullptr || !nameManager->validateName(name)) {
		player->sendSystemMessage("@event_perk_npc_actor:obscene"); // "The text entered has been deemed inappropriate. Please try again."

		promptNameSelection();
		return;
	}

	auto zone = zoneServer->getZone(zoneName);

	if (zone == nullptr) {
		return;
	}

	// Spawn the invisible perk object that handles the NPC actor despawn
	ManagedReference<TangibleObject*> perkObject = nullptr;

	try {
		perkObject = (zoneServer->createObject(STRING_HASHCODE("object/tangible/event_perk/npc_actor_perk.iff"), "playerstructures", 1)).castTo<TangibleObject*>();

		if (perkObject == nullptr) {
			player->sendSystemMessage("Error generating EventPark object.");

			cancelSession();
			return;
		}
	} catch (Exception& e) {
		error(e.getMessage());
	}

	Locker perkLocker(perkObject, player);

	perkObject->initializePosition(actorPosition.getX(), actorPosition.getZ(), actorPosition.getY());
	perkObject->setDirection(player->getDirection()->getRadians());

	if (!zone->transferObject(perkObject, -1)) {
		perkObject->destroyObjectFromWorld(true);
		perkObject->destroyObjectFromDatabase(true);

		cancelSession();
		return;
	}

	// Spawn the NPC actor itself
	ManagedReference<CreatureObject*> npcActor = nullptr;

	try {
		npcActor = zoneServer->createObject(templatePath.hashCode(), perkObject->getPersistenceLevel()).castTo<CreatureObject*>();
	} catch (Exception& e) {
		error(e.getMessage());
	}

	if (npcActor == nullptr) {
		error() << "Failed to create NPC Actor using template: " << templatePath;

		perkObject->destroyObjectFromWorld(true);
		perkObject->destroyObjectFromDatabase(true);

		cancelSession();

		return;
	}

	Locker clocker(npcActor, player);

	// Clear the vendor option bitmask
	npcActor->clearOptionBit(OptionBitmask::VENDOR);

	// Add the NPC as a child of Perk Object
	perkObject->addChildObject(npcActor);

	// Set the menu component for the actor
	npcActor->setObjectMenuComponent("EventPerkActorMenuComponent");

	// Set the container component for the actor
	npcActor->setContainerComponent("EventPerkActorContainerComponent");

	// Set the Actors name
	npcActor->setCustomObjectName(name, false);

	// Randomize the look of the actor
	VendorManager::instance()->randomizeVendorLooks(npcActor);

	// Initialize the position and direction for zone placement
	npcActor->initializePosition(actorPosition.getX(), actorPosition.getZ(), actorPosition.getY());
	npcActor->setDirection(player->getDirection()->getRadians());

	if (!zone->transferObject(npcActor, -1)) {
		npcActor->destroyObjectFromWorld(true);
		npcActor->destroyObjectFromDatabase(true);

		perkObject->destroyObjectFromWorld(true);
		perkObject->destroyObjectFromDatabase(true);

		cancelSession();
		return;
	}

	// Update the deed and the perk object data component
	Locker deedLock(eventPerkDeed, player);

	eventPerkDeed->setGeneratedObject(perkObject);
	eventPerkDeed->setGenerated(true);

	EventPerkDataComponent* data = cast<EventPerkDataComponent*>(perkObject->getDataObjectComponent()->get());

	if (data == nullptr) {
		// The data is null, destroying everything and end the session
		perkObject->destroyObjectFromWorld(true);
		perkObject->destroyObjectFromDatabase(true);

		npcActor->destroyObjectFromWorld(true);
		npcActor->destroyObjectFromDatabase(true);

		cancelSession();
		return;
	}

	// Store the deed and the actor on the data component
	data->setDeed(eventPerkDeed);
	data->setActor(npcActor);

	// Parse the child objects so permissions are updated
	eventPerkDeed->parseChildObjects(perkObject);

	// Schedule ask to destroy the perk and actor
	eventPerkDeed->activateRemoveEvent(false);

	// Destroy the deed from the world only, it is held in reference by the data component
	eventPerkDeed->destroyObjectFromWorld(true);

	// End the actor creation session
	cancelSession();
}
