/*
 * 				Copyright <SWGEmu>
		See file COPYING for copying conditions. */

#include "DroidPersonalityModuleDataComponent.h"
#include "server/zone/ZoneServer.h"
#include "server/zone/objects/tangible/component/droid/DroidComponent.h"
#include "templates/tangible/DroidPersonalityModuleTemplate.h"
#include "server/chat/ChatManager.h"
#include "server/zone/managers/reaction/ReactionManager.h"
#include "server/zone/objects/creature/ai/DroidObject.h"

DroidPersonalityModuleDataComponent::DroidPersonalityModuleDataComponent() {
	setLoggingName("DroidPersonalityModule");
}

DroidPersonalityModuleDataComponent::~DroidPersonalityModuleDataComponent() {

}

String DroidPersonalityModuleDataComponent::getModuleName() const {
	return "personality_chip";
}

void DroidPersonalityModuleDataComponent::initializeTransientMembers() {
	// load template data here
	DroidComponent* droidComponent = cast<DroidComponent*>(getParent());
	if (droidComponent == nullptr) {
		info("droidComponent was null");
		return;
	}

	Reference<DroidPersonalityModuleTemplate*> moduleTemplate = cast<DroidPersonalityModuleTemplate*>(droidComponent->getObjectTemplate());
	if (moduleTemplate == nullptr) {
		info("Module was null");
		return;
	}

	personalityBase = moduleTemplate->getReactionName();
	chipName = moduleTemplate->getChipName();
	convoTemplate = moduleTemplate->getConversationTemplate();
	personalityStf = moduleTemplate->getPersonalityStf();
}

void DroidPersonalityModuleDataComponent::initialize(DroidObject* droid) {
	// do we need to change any droid stats: no
	// when installed we get converse options.
}

void DroidPersonalityModuleDataComponent::fillAttributeList(AttributeListMessage* alm, CreatureObject* droid) {
	alm->insertAttribute("personality_module", chipName);
}

void DroidPersonalityModuleDataComponent::handlePetCommand(String cmd, CreatureObject* speaker) {
	// no op
}

int DroidPersonalityModuleDataComponent::getBatteryDrain() {
	return 0;
}

void DroidPersonalityModuleDataComponent::deactivate() {
	// no op
}

String DroidPersonalityModuleDataComponent::toString() const {
	return BaseDroidModuleComponent::toString();
}

void DroidPersonalityModuleDataComponent::onCall() {
	ManagedReference<DroidObject*> droid = getDroidObject();
	if (droid == nullptr) {
		info("Droid is null");
		return;
	}

	if (convoTemplate.hashCode() > 0) {
		droid->setOptionBit(OptionBitmask::CONVERSE, true);
	} else {
		droid->clearOptionBit(OptionBitmask::CONVERSE, true);
	}

	if (observer == nullptr) {
		observer = new DroidPersonalityObserver(this);
		observer->deploy();
	}

	Locker plock(droid);

	droid->registerObserver(ObserverEventType::DEFENDERADDED, observer);

	droid->sendReactionChat(nullptr, ReactionManager::HI, ReactionManager::NICE, true);
}

void DroidPersonalityModuleDataComponent::onStore() {
	ManagedReference<DroidObject*> droid = getDroidObject();
	if (droid == nullptr) {
		info("Droid is null");
		return;
	}

	if (observer == nullptr) {
		info("bad observer");
		return;
	}

	Locker dlock(droid);

	droid->dropObserver(ObserverEventType::DEFENDERADDED, observer);
	droid->sendReactionChat(nullptr, ReactionManager::BYE, ReactionManager::NICE, true);
}

void DroidPersonalityModuleDataComponent::copy(BaseDroidModuleComponent* other) {
	// no Op when the new object is made, init transient is called so all info is set.
}

void DroidPersonalityModuleDataComponent::quip(String m,DroidObject* droid) {
	StringBuffer message;
	message << personalityBase << ":" << m << "_" << (System::random(15) + 1);

	StringIdChatParameter chat;
	chat.setStringId(message.toString());

	droid->getZoneServer()->getChatManager()->broadcastChatMessage(droid, chat, 0, 0, 0);
}

void DroidPersonalityModuleDataComponent::notifyEvent(unsigned int eventType, ManagedObject* arg1, int64 arg2, bool forced) {
	ManagedReference<DroidObject*> droid = getDroidObject();
	if (droid == nullptr) {
		info("Droid is null");
		return;
	}

	if (droid->getCooldownTimerMap()->isPast("Droid_Quip") || forced) {
		// cooldown has passed
		int roll = System::random(100);
		StringBuffer message;

		if (roll > 50 || forced) {
			if (eventType == ObserverEventType::DEFENDERADDED) {
				short type = System::random(1);

				if (type == 0)
					quip("threat", droid);
				else
					quip("alert", droid);
			}

			// we are going to do something
			// END
			droid->getCooldownTimerMap()->updateToCurrentAndAddMili("Droid_Quip", 1800000); // 30 minute cooldown
		}
	}
}

String DroidPersonalityModuleDataComponent::getPersonalityBase() {
	return personalityBase;
}

uint32 DroidPersonalityModuleDataComponent::getPersonalityConversationTemplate() {
	return convoTemplate.hashCode();
}
