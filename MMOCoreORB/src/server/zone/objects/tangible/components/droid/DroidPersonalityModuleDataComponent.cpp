/*
 * Copyright (C) 2014 <SWGEmu>
 * This File is part of Core3.
 * This program is free software; you can redistribute
 * it and/or modify it under the terms of the GNU Lesser
 * General Public License as published by the Free Software
 * Foundation; either version 2 of the License,
 * or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU Lesser General Public License for
 * more details.
 *
 * You should have received a copy of the GNU Lesser General
 * Public License along with this program; if not, write to
 * the Free Software Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA
 *
 * Linking Engine3 statically or dynamically with other modules
 * is making a combined work based on Engine3.
 * Thus, the terms and conditions of the GNU Lesser General Public License
 * cover the whole combination.
 *
 * In addition, as a special exception, the copyright holders of Engine3
 * give you permission to combine Engine3 program with free software
 * programs or libraries that are released under the GNU LGPL and with
 * code included in the standard release of Core3 under the GNU LGPL
 * license (or modified versions of such code, with unchanged license).
 * You may copy and distribute such a system following the terms of the
 * GNU LGPL for Engine3 and the licenses of the other code concerned,
 * provided that you include the source code of that other code when
 * and as the GNU LGPL requires distribution of source code.
 *
 * Note that people who make modified versions of Engine3 are not obligated
 * to grant this special exception for their modified versions;
 * it is their choice whether to do so. The GNU Lesser General Public License
 * gives permission to release a modified version without this exception;
 * this exception also makes it possible to release a modified version
 * which carries forward this exception.
 */

#include "DroidPersonalityModuleDataComponent.h"
#include "server/zone/ZoneServer.h"
#include "server/zone/objects/tangible/component/droid/DroidComponent.h"
#include "server/zone/templates/tangible/DroidPersonalityModuleTemplate.h"
#include "server/chat/ChatManager.h"

DroidPersonalityModuleDataComponent::DroidPersonalityModuleDataComponent() {
	setLoggingName("DroidCraftingModule");
}
DroidPersonalityModuleDataComponent::~DroidPersonalityModuleDataComponent() {

}
String DroidPersonalityModuleDataComponent::getModuleName() {
	return "personality_chip";
}
void DroidPersonalityModuleDataComponent::initializeTransientMembers() {
	// load template data here
	DroidComponent* droidComponent = cast<DroidComponent*>(getParent());
	if (droidComponent == NULL) {
		info("droidComponent was null");
		return;
	}

	ManagedReference<DroidPersonalityModuleTemplate*> moduleTemplate = cast<DroidPersonalityModuleTemplate*>(droidComponent->getObjectTemplate());
	if (moduleTemplate == NULL){
		info("Module was null");
		return;
	}
	personalityBase = moduleTemplate->getReactionName();
	chipName = moduleTemplate->getChipName();
}
void DroidPersonalityModuleDataComponent::initialize(CreatureObject* droid) {
	// do we need to change any droid stats: no
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
String DroidPersonalityModuleDataComponent::toString(){
	return BaseDroidModuleComponent::toString();
}
void DroidPersonalityModuleDataComponent::onCall() {
	ManagedReference<DroidObject*> droid = getDroidObject();
	if( droid == NULL ){
		info( "Droid is null" );
		return;
	}
	if (observer == NULL) {
		observer = new DroidPersonalityObserver(this);
		observer->deploy();
	}
	Locker plock(droid);
	notifyEvent(ObserverEventType::ENTEREDAREA,NULL,0,true);
	droid->registerObserver(ObserverEventType::KILLEDCREATURE, observer);
	droid->registerObserver(ObserverEventType::DAMAGERECEIVED, observer);
	droid->registerObserver(ObserverEventType::ENTEREDAREA, observer);
	droid->registerObserver(ObserverEventType::EXITEDAREA, observer);
	droid->registerObserver(ObserverEventType::STARTCOMBAT, observer);
	droid->registerObserver(ObserverEventType::DEFENDERADDED, observer);
	droid->registerObserver(ObserverEventType::PLAYERKILLED, observer);
	droid->registerObserver(ObserverEventType::PEACE, observer);
	droid->registerObserver(ObserverEventType::FLEEING, observer);
}
void DroidPersonalityModuleDataComponent::onStore() {
	ManagedReference<DroidObject*> droid = getDroidObject();
	if( droid == NULL ){
		info( "Droid is null" );
		return;
	}
	if (observer == NULL) {
		info("bad observer");
		return;
	}
	Locker dlock( droid );
	notifyEvent(ObserverEventType::EXITEDAREA,NULL,0,true);

	droid->dropObserver(ObserverEventType::KILLEDCREATURE, observer);
	droid->dropObserver(ObserverEventType::DAMAGERECEIVED, observer);
	droid->dropObserver(ObserverEventType::ENTEREDAREA, observer);
	droid->dropObserver(ObserverEventType::EXITEDAREA, observer);
	droid->dropObserver(ObserverEventType::STARTCOMBAT, observer);
	droid->dropObserver(ObserverEventType::DEFENDERADDED, observer);
	droid->dropObserver(ObserverEventType::PLAYERKILLED, observer);
	droid->dropObserver(ObserverEventType::PEACE, observer);
	droid->dropObserver(ObserverEventType::FLEEING, observer);
}

void DroidPersonalityModuleDataComponent::copy(BaseDroidModuleComponent* other) {
	// no Op when the new object is made, init transient is called so all info is set.
}
void DroidPersonalityModuleDataComponent::quip(String m,DroidObject* droid) {
	StringBuffer message;
	message << personalityBase << ":" << m << "_" << (System::random(15) + 1);
	StringIdChatParameter chat;
	chat.setStringId(message.toString());
	droid->getZoneServer()->getChatManager()->broadcastMessage(droid,chat,0,0,0);
}
void DroidPersonalityModuleDataComponent::notifyEvent(unsigned int eventType, ManagedObject* arg1, int64 arg2, bool forced) {
	ManagedReference<DroidObject*> droid = getDroidObject();
	if( droid == NULL ){
		info( "Droid is null" );
		return;
	}
	if (droid->getCooldownTimerMap()->isPast("Droid_Quip") || forced) {
		// cooldown has passed
		int roll = System::random(100);
		StringBuffer message;
		if (roll > 50 || forced) {
			if (eventType == ObserverEventType::KILLEDCREATURE || eventType == ObserverEventType::PLAYERKILLED) {
				// Droid killed a creature or player
				quip("gloat",droid);
			}
			if (eventType == ObserverEventType::ENTEREDAREA || eventType == ObserverEventType::EXITEDAREA) {
				if (eventType ==ObserverEventType::ENTEREDAREA)
					message << "hi_";
				else
					message << "bye_";
				String responseAttitude;
				if (responseAttitude == "") {
					short type = System::random(2);
					if (type == 0)
						responseAttitude = "mean";
					else if (type == 1)
						responseAttitude = "mid";
					else
						responseAttitude = "nice";
				}
				if (forced) {
					responseAttitude = "nice";
				}
				message << responseAttitude;
				quip(message.toString(),droid);
			}
			if (eventType == ObserverEventType::STARTCOMBAT) {
				quip("attacked",droid);
			}
			if (eventType == ObserverEventType::FLEEING) {
				quip("flee",droid);
			}
			if (eventType == ObserverEventType::PEACE) {
				quip("calm",droid);
			}
			if (eventType == ObserverEventType::DEFENDERADDED) {
				short type = System::random(1);
				if (type == 0)
					quip("threat",droid);
				else
					quip("alert",droid);
			}
			if (eventType == ObserverEventType::DAMAGERECEIVED) {
				// cast arg1 to a creature object
				SceneObject* sceno = dynamic_cast<SceneObject*>(arg1);
				if (sceno == NULL) {
					return;
				}
				CreatureObject* target = dynamic_cast<CreatureObject*>(sceno);
				if (target == NULL) {
					return;
				}
				// is the target our guard target?
				// quip("ally",droid);
				if (target->getObjectID() == droid->getObjectID()) {
					// it was us, how low is our health?
					if (droid->isIncapacitated() || droid->isDead()) {
						quip("death",droid);
					}
					int h,a,m, hM, aM, mM;
					h = droid->getHAM(0);
					a = droid->getHAM(3);
					m = droid->getHAM(6);
					hM = droid->getMaxHAM(0);
					aM = droid->getMaxHAM(3);
					mM = droid->getMaxHAM(6);
					if ( (hM - h < (hM/2)) || (aM - a < (aM/2)) || (mM - m < (mM/2))) {
						quip("help",droid);
					} else {
						quip("hit",droid);
					}
				} else {
					// droid hit a target
					quip("hit_target",droid);
				}
			}
			// we are going todo something
			// END
			droid->getCooldownTimerMap()->updateToCurrentAndAddMili("Droid_Quip",1800000); // 30 minute cooldown
		}
	}
}

