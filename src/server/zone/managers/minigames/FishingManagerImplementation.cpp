/*
 * FishingManagerImplementation.cpp
 *
 *  Created on: Apr 11, 2010
 *      Author: swgemu
 */

#include "FishingManager.h"
#include "server/zone/objects/player/PlayerCreature.h"
#include "server/zone/objects/player/sui/listbox/SuiListBox.h"
#include "server/zone/objects/tangible/weapon/WeaponObject.h"
#include "server/zone/objects/tangible/fishing/FishingPoleObject.h"
#include "server/zone/objects/tangible/fishing/FishingBaitObject.h"
#include "server/zone/managers/terrain/TerrainManager.h"
#include "server/zone/Zone.h"
#include "server/zone/managers/planet/PlanetManager.h"
#include "server/zone/ZoneServer.h"
#include "server/zone/objects/scene/variables/ParameterizedStringId.h"
#include "server/zone/managers/minigames/events/FishingEvent.h"
#include "server/zone/managers/minigames/events/FishingSplashEvent.h"

/*
 * startFishing checks for Fishing Pole, Fishing Bait and Water at the position of the bobber,
 * creates the bobber and opens the window for Fishing.
 *
 */
int FishingManagerImplementation::startFishing(PlayerCreature* player) {
	ManagedReference<FishingPoleObject*> pole = getPole(player);

	if (pole == NULL) {
		player->sendSystemMessage("You don't have a pole equipped.");
		return 1;
	}

	ManagedReference<FishingBaitObject*> bait = getBait(player);

	if (bait == NULL) {
		player->sendSystemMessage("You don't have any bait equipped.");
		return 2; // NOBAIT
	}


	int quality = pole->getQuality();
	// CALCULATING BOBBER POS
	float x = player->getPositionX();
	float y = player->getPositionY();
	float deg = player->getDirectionAngle();

	if (deg > 360) {
		deg = deg - 360;
	}

	float dist = MAX(quality / 10.f, 2.1);
	float rad = 2 * M_PI * deg / 360;
	float newx = x + sin(rad) * (dist);
	float newy = y + cos(rad) * (dist);

	/*
	StringBuffer msg;
	msg << "creating marker at x: " << newx << " y:" << newy << " at dist:" << dist;
	info(msg.toString(), true);*/

	ManagedReference<Zone*> zone = player->getZone();
	TerrainManager* terrain = zone->getPlanetManager()->getTerrainManager();

	float newz;
	float height = zone->getHeight(newx, newy);

	if (!terrain->getWaterHeight(newx, newy, newz)) {
		player->sendSystemMessage("@fishing:bad_cast"); // Your cast goes astray and lands at a non-fishable spot.
		return 3; // NOWATER
	}

	if (newz < height) {
		player->sendSystemMessage("@fishing:bad_cast");
		return 4; // TERRAINABOVEWATER
	}

	if (player->isSwimming()) {
		player->sendSystemMessage("Cannot fish while swimming.");
		return 5; // SWIMMING
	}

	ManagedReference<SceneObject*> markerObject = createMarker(newx, newy, newz, zone);
	createSplash(newx, newy, newz, zone, player);

	//player->sendSystemMessage(String::valueOf(deg) + " " + String::valueOf(newx) + " " + String::valueOf(newy) + " " + String::valueOf(newz));
	//player->sendSystemMessage("Angle: " + String::valueOf(deg) + " Current Pos: " + String::valueOf(x) + " " + String::valueOf(y) + " New Pos: " + String::valueOf(newx) + " " + String::valueOf(newy));

	createFishingEvent(player, DONOTHING, zoneServer, markerObject, 0, 0, WAITING);
	uint32 boxID = createWindow(player, 0);

	Reference<FishingEvent*> fishingEvent = player->getFishingEvent();

	if (fishingEvent != NULL) {
		fishingEvent->setFishBoxID(boxID);
	}

	player->doAnimation("fishing_cast");
	return 0;
}

void FishingManagerImplementation::stopFishing(PlayerCreature* player, uint32 boxID, bool rem) {
	player->doAnimation("fishing_reel");
	setFishingState(player, NOTFISHING);

	ManagedReference<SceneObject*> marker = getFishMarker(player);

	if (marker != NULL) {
		createSplash(marker->getPositionX(), marker->getPositionY(), marker->getPositionZ(), player->getZone(), player);
	}

	uint32 id = boxID;

	if (boxID == 0) {
		Reference<FishingEvent*> fishingEvent = player->getFishingEvent();
		id = fishingEvent->getFishBoxID();
	}

	// close windows
	closeMenu(player, id);

	// stop events
	if (rem) {
		removeMarker(player);
		stopFishingEvent(player);
	}
}

void FishingManagerImplementation::fishingStep(PlayerCreature* player, int nextAction, SceneObject* marker, int fish, uint32 boxID) {
	// close windows
	closeMenu(player, boxID);

	// get fishing state
	int state = getFishingState(player);

	// Random Event & Mishap
	int event = System::random(5);
	int mishap = System::random(1);

	// Luck might have it a mishap turns into something else!
	/*if (event == MISHAP) {
		chance = System::random(luck/10);
		if (chance >= (int)((luck / 10) * (3 / 4))) event--;
	}*/

	// Accounting for bad Bait
	ManagedReference<FishingBaitObject*> bait = getBait(player);

	if ((bait->getFreshness() >= MUSH) && (state < CATCH)) {
		mishapEvent("@fishing:toss_bait", player, boxID, true);
		return; // NOBAIT
	}

	//debug player->sendSystemMessage("Event: " + String::valueOf(event) + " Mishap: " + String::valueOf(mishap) + " Next Action: " + String::valueOf(nextAction));

	// animate character
	animate(player, nextAction);

	switch (state) {
	case WAITING:
	{
		// CALCULATING FISH
		int newFish = getFish(player);

		if (event == MISHAP) {
			fishingProceed(player, nextAction, marker, newFish, boxID, WAITING, false);
		} else if (event >= PROCEED) {
			fishingProceed(player, nextAction, marker, newFish, boxID, NIBBLE, true);
		} else {
			fishingProceed(player, nextAction, marker, newFish, boxID, SNAGGED, true);
		}
		break;
	}
	case SNAGGED:
	{
		if (event >= PROCEED) {
			fishingProceed(player, nextAction, marker, fish, boxID, NIBBLE, true);
		} else {
			fishingProceed(player, nextAction, marker, fish, boxID, SNAGGED, false);
		}
		break;
	}
	case NIBBLE:
	{
		if (event == MISHAP) {
			if (mishap == 0) { // Line snapped, losing bait
				mishapEvent("@fishing:line_snap", player, boxID, true);
			} else { // Lost catch
				mishapEvent("@fishing:lost_catch", player, boxID, false);
			}
		} else if ((event >= PROCEED) && (nextAction >= TUGUP && nextAction <= TUGLEFT)) {
			fishingProceed(player, nextAction, marker, fish, boxID, BITE, true);
		} else {
			fishingProceed(player, nextAction, marker, fish, boxID, NIBBLE, false);
		}
		break;
	}
	case BITE:
	{
		if (event == MISHAP) {
			if (mishap == 0) { // Lost Bait
				mishapEvent("@fishing:lost_bait", player, boxID, true);
			} else { // Fish pulled out the line, but the player has no penalty - appearently every fisherman can fix his line :)
				mishapEvent("@fishing:line_spooled", player, boxID, false);
			}
		} else if ((event >= PROCEED) && (nextAction >= TUGUP && nextAction <= TUGLEFT)) {
			fishingProceed(player, nextAction, marker, fish, boxID, CATCH, true);
		} else {
			fishingProceed(player, nextAction, marker, fish, boxID, BITE, false);
		}
		break;
	}
	case CATCH:
	{
		if (player->isInRange(marker, 2.0)) { // in case reeling closer gets it into catching range but neither did the position change nor did he do nothing or reel
			success(player, fish, marker, boxID);
		} else {
			if (event == MISHAP) { // Fish is trying to get away
				fishingProceed(player, nextAction, marker, fish, boxID, CATCH, true);
			}  else if (nextAction != DONOTHING && nextAction != REEL) {
				updateMarker(player, nextAction, marker);
				fishingProceed(player, nextAction, getFishMarker(player), fish, boxID, CATCH, false);
			} else {
				fishingProceed(player, nextAction, marker, fish, boxID, REELING, true);
			}
			break;
		}
	}
	case REELING:
	{
		if (player->isInRange(marker, 2.0)) {
			success(player, fish, marker, boxID);
		} else {
			mishapEvent("The fish got away with your bait.", player, boxID, true);
		}
		break;
	}
	}
}

void FishingManagerImplementation::success(PlayerCreature* player, int fish, SceneObject* marker, uint32 boxID) {
	Zone* zone = player->getZone();
	ParameterizedStringId body("fishing","prose_notify_catch");
	String itemName;

	if (fish != -1) {
		if (fish > 93){ // NON-FISH ITEM WAS CAUGHT!

			int chance = System::random(99)/*+(luck/10)*/;
			if (chance > 94) { // RARE ITEM WAS CAUGHT!

				int i = rareLoot.size();
				String loot = rareLoot.get(System::random(i - 1));
				ManagedReference<SceneObject*> lootObject = zoneServer->createObject(loot.hashCode(),0);
				lootObject->sendTo(player);

				if (marker->addObject(lootObject, -1, true)) {
					marker->openContainerTo(player);
					lootObject->getObjectName()->getFullPath(itemName);
					body.setTT(itemName);
					player->sendSystemMessage(body);
				}

			} else { // MISC ITEM WAS CAUGHT!

				int i = miscLoot.size();
				String loot = miscLoot.get(System::random(i - 1));

				ManagedReference<SceneObject*> lootObject = zoneServer->createObject(loot.hashCode(),0);
				lootObject->sendTo(player);

				if (marker->addObject(lootObject, -1, true)) {
					marker->openContainerTo(player);
					lootObject->getObjectName()->getFullPath(itemName);
					body.setTT(itemName);
					player->sendSystemMessage(body);
				}
			}
		} else {
			String lootFish = "object/tangible/fishing/fish/shared_" + fishType.get(fish) + ".iff";
			ManagedReference<TangibleObject*> lootFishObject = (TangibleObject*)zoneServer->createObject(lootFish.hashCode(), 0);
			lootFishObject->setCustomizationVariable(CustomizationVariableTypes::PRIVATE_INDEX_COLOR_1, color.get(zone->getZoneID()));
			lootFishObject->sendTo(player);

			if (marker->addObject(lootFishObject, -1, true)) {
				marker->openContainerTo(player);
				lootFishObject->getObjectName()->getFullPath(itemName);
				body.setTT(itemName);
				player->sendSystemMessage(body);
			}
		}

		stopFishing(player, boxID, false);
	} else {//CHEAT MODE!

		// TEST RARE OBJECT
		int newFish = getFish(player);
		String lootFish = "object/tangible/fishing/fish/shared_" + fishType.get(newFish) + ".iff";
		ManagedReference<TangibleObject*> lootFishObject;
		ManagedReference<SceneObject*> lootObject;

		int i = rareLoot.size();

		String loot = rareLoot.get(System::random(i - 1));
		lootObject=zoneServer->createObject(loot.hashCode(),0);
		lootObject->sendTo(player);
		marker->addObject(lootObject,-1,true);

		// TEST MISC OBJECT
		i = miscLoot.size();
		loot = miscLoot.get(System::random(i - 1));
		lootObject=zoneServer->createObject(loot.hashCode(),0);
		lootObject->sendTo(player);
		marker->addObject(lootObject,-1,true);

		// TEST COLOR VARIATIONS
		for (int i = 0; i < 10; ++i) {
			lootFishObject=(TangibleObject*)zoneServer->createObject(lootFish.hashCode(),0);
			lootFishObject->setCustomizationVariable(CustomizationVariableTypes::PRIVATE_INDEX_COLOR_1, color.get(i), true);
			lootFishObject->sendTo(player);

			marker->addObject(lootFishObject,-1,true);
		}

		marker->openContainerTo(player);
		stopFishing(player,boxID,false);
	}
}

uint32 FishingManagerImplementation::createWindow(PlayerCreature* player, uint32 boxID) {
	// clear old one
	closeMenu(player, boxID);

	int veg = vegetation(getFishMarker(player));
	int den = density(getFishMarker(player));
	int freshness = getBait(player)->getFreshness();

	if (freshness >= MUSH) {
		freshness = 2;
	} else if (freshness >= SOGGY) {
		freshness = 1;
	} else {
		freshness = 0;
	}

	String prompt = "STATUS     : " + state.get(getFishingState(player)) + "\nBAIT STATUS : "
			+ baitStatus.get(freshness) + "\nLINE RANGE : "
			+ String::valueOf(ceil(player->getDistanceTo(getFishMarker(player)) * 100) / 100)
	+ "\nFISH DENSITY: "+ property.get(den)
	+ "\nVEGETATION : " + property.get(veg)
	+ "\nNEXT ACTION : "
	+ action.get(getNextAction(player));

	// create new window
	ManagedReference<SuiListBox*> box = new SuiListBox(player, 90, 0);
	box->setPromptTitle("@fishing:sui_title");
	box->setPromptText(prompt);
	box->addMenuItem("@fishing:fa_tug_up", 0);
	box->addMenuItem("@fishing:fa_tug_right", 1);
	box->addMenuItem("@fishing:fa_tug_left", 2);
	box->addMenuItem("@fishing:fa_small_reel", 3);
	box->addMenuItem("@fishing:fa_stop", 4);
	player->addSuiBox(box);
	player->sendMessage(box->generateMessage());

	return box->getBoxID();
}

void FishingManagerImplementation::closeMenu(PlayerCreature* player, uint32 boxID) {
	if (player->hasSuiBox(boxID)) {
		player->sendMessage(player->getSuiBox(boxID)->generateCloseMessage());
		player->removeSuiBox(boxID);
	}
}

int FishingManagerImplementation::vegetation(SceneObject* marker) {
	return (int)ceil(fabs(marker->getPositionX() / 100)) % 6;
}

int FishingManagerImplementation::density(SceneObject* marker) {
	return (int)ceil(fabs(marker->getPositionY() / 100)) % 6;
}

int FishingManagerImplementation::getFish(PlayerCreature* player) {
	int chance = System::random(99)/*+(luck/10)*/;

	if (chance < 94) {
		chance = (int)((getPole(player)->getQuality() * 0.06) // ACCOUNT FOR POLE QUALITY
						+ (vegetation(player) * -0.75) // ACCOUNT FOR VEGETATION PENALTY
						+ (density(player) * 0.75) // ACCOUNT FOR FISH DENSITY
						+ ((3 - getBait(player)->getFreshness()) * 3.0) // ACCOUNT FOR BAIT STATUS
						//+ (luck / 100) // ACCOUNT FOR LUCK
						+ (System::random(20))) // RANDOM BIAS
						% 7; // MUX NUMBER TO FISH 0-6
	}

	return chance;
}

int FishingManagerImplementation::getNextAction(PlayerCreature* player) {
	Reference<FishingEvent*> fishingEvent = player->getFishingEvent();

	if (fishingEvent != NULL) {
		return fishingEvent->getNextAction();
	} else {
		return 0;
	}
}

void FishingManagerImplementation::setNextAction(PlayerCreature* player, int next) {
	Reference<FishingEvent*> fishingEvent = player->getFishingEvent();

	if (fishingEvent != NULL) {
		fishingEvent->setNextAction(next);
	}
}

FishingPoleObject* FishingManagerImplementation::getPole(PlayerCreature* player) {
	ManagedReference<FishingPoleObject*> pole = (FishingPoleObject*)player->getSlottedObject("hold_r");

	if (pole != NULL) {
		if(pole->isFishingPoleObject()) {
			return pole;
		}
	}

	return NULL;
}

FishingBaitObject* FishingManagerImplementation::getBait(PlayerCreature* player) {
	ManagedReference<FishingPoleObject*> pole = getPole(player);

	if (pole != NULL) {
		if (pole->isFishingPoleObject()&&pole->hasFullContainerObjects()) {
			ManagedReference<FishingBaitObject*> bait = (FishingBaitObject*)pole->getContainerObject(0);

			if (bait != NULL) {
				if (bait->isFishingBait()) {
					return bait;
				}
			}
		}
	}

	return NULL;
}

uint32 FishingManagerImplementation::getFishBoxID(PlayerCreature* player) {
	Reference<FishingEvent*> fishingEvent = player->getFishingEvent();

	if (fishingEvent != NULL) {
		return fishingEvent->getFishBoxID();
	}

	return 0;
}

void FishingManagerImplementation::setFishBoxID(PlayerCreature* player, uint32 boxID) {
	Reference<FishingEvent*> fishingEvent = player->getFishingEvent();

	if (fishingEvent != NULL) {
		fishingEvent->setFishBoxID(boxID);
	}
}

int FishingManagerImplementation::getFishingState(PlayerCreature* player) {
	Reference<FishingEvent*> fishingEvent = player->getFishingEvent();

	if (fishingEvent != NULL) {
		return fishingEvent->getFishingState();
	} else {
		return NOTFISHING;
	}
}

void FishingManagerImplementation::setFishingState(PlayerCreature* player, int state) {
	Reference<FishingEvent*> fishingEvent = player->getFishingEvent();

	if (fishingEvent != NULL) {
		fishingEvent->setFishingState(state);
	}
}

SceneObject* FishingManagerImplementation::getFishMarker(PlayerCreature* player) {
	Reference<FishingEvent*> fishingEvent = player->getFishingEvent();

	if (fishingEvent != NULL) {
		return fishingEvent->getMarker();
	} else {
		return player;
	}
}

void FishingManagerImplementation::setFishMarker(PlayerCreature* player, SceneObject* marker) {
	Reference<FishingEvent*> fishingEvent = player->getFishingEvent();

	if (fishingEvent != NULL) {
		fishingEvent->setMarker(marker);
	}
}

void FishingManagerImplementation::cheat(PlayerCreature* player, int value) {
	ManagedReference<Zone*> zone = player->getZone();
	float x = player->getPositionX();
	float y = player->getPositionY();
	float z = getFishMarker(player)->getPositionZ();

	removeMarker(player);

	ManagedReference<SceneObject*> newMarker = createMarker(x,y,z,zone);
	setFishMarker(player,newMarker);
	success(player,-1,newMarker,getFishBoxID(player));
}

void FishingManagerImplementation::freeBait(PlayerCreature* player) {
	String bait = "object/tangible/fishing/bait/shared_bait_worm.iff";
	ManagedReference<SceneObject*> baitObject = zoneServer->createObject(bait.hashCode(), 0);
	baitObject->sendTo(player);
	ManagedReference<FishingPoleObject*> pole = getPole(player);

	if ((pole != NULL) && (!pole->hasFullContainerObjects())) {
		pole->addObject(baitObject, -1, true);
	}
}

void FishingManagerImplementation::fishingProceed(PlayerCreature* player, int nextAction, SceneObject* marker, int fish, uint32 boxID, int newstate, bool notifyClient) {
	int oldstate = getFishingState(player);

	if ((newstate == CATCH) && (!notifyClient)) { // updated the marker!
		player->sendSystemMessage("@fishing:fish_fight_closer");
	}

	if (notifyClient) {

		switch (newstate) {
		case SNAGGED:
			player->sendSystemMessage("@fishing:fs_snag");
		case NIBBLE:
			if (oldstate == SNAGGED) { // line just got unsnagged
				player->sendSystemMessage("@fishing:line_free");
			}
			player->showFlyText("fishing","fly_nibble",20,200,20);
			createSplash(marker->getPositionX(),marker->getPositionY(),marker->getPositionZ(),player->getZone(),player);
			break;
		case BITE:
			player->showFlyText("fishing","fly_bite",200,20,20);
			createSplash(marker->getPositionX(),marker->getPositionY(),marker->getPositionZ(),player->getZone(),player);
			break;
		case CATCH:
			if (oldstate != BITE) { // fish is trying to get away
				player->sendSystemMessage("@fishing:fish_run");
			} else {
				player->showFlyText("fishing","fly_catch",20,20,200);
				createSplash(marker->getPositionX(),marker->getPositionY(),marker->getPositionZ(),player->getZone(),player);
			}
			break;
		default:
			break;
		}
	}

	if ((nextAction > DONOTHING) && (nextAction < REEL)) {
		ManagedReference<FishingBaitObject*> bait = getBait(player);
		bait->lessFresh();
	}

	createFishingEvent(player, DONOTHING, zoneServer, marker, fish, boxID, newstate);

	Reference<FishingEvent*> fishingEvent = player->getFishingEvent();
	if (fishingEvent != NULL) {
		fishingEvent->setFishBoxID(createWindow(player, boxID));
	}

}

void FishingManagerImplementation::mishapEvent(const String& text, PlayerCreature* player, uint32 boxID, bool losebait) {
	player->sendSystemMessage(text);
	stopFishing(player, boxID, true);

	if (losebait) {
		loseBait(player);
	}
}

bool FishingManagerImplementation::loseBait(PlayerCreature* player) {
	ManagedReference<SceneObject*> pole = player->getSlottedObject("hold_r");

	if (pole != NULL) {
		if (pole->isFishingPoleObject() && pole->hasFullContainerObjects()) {
			if (pole->getContainerObject(0) != NULL) {
				pole->removeObject(pole->getContainerObject(0),true);
				return true;
			}
		}
	}

	return false;
}

void FishingManagerImplementation::animate(PlayerCreature* player, int nextAction) {
	switch (nextAction) {
	case TUGUP:
		player->doAnimation("fishing_tug_back");
		break;
	case TUGRIGHT:
		player->doAnimation("fishing_tug_right");
		break;
	case TUGLEFT:
		player->doAnimation("fishing_tug_left");
		break;
	case REEL:
		player->doAnimation("fishing_reel");
		break;
	default:
		//player->doAnimation("fishing_idle");  NOTWORKING :( :(
		break;
	}
}

SceneObject* FishingManagerImplementation::createMarker(float x, float y, float z, Zone* zone) {
	String marker = "object/tangible/fishing/shared_marker.iff";
	ManagedReference<SceneObject*> markerObject = zoneServer->createObject(marker.hashCode(), 0);
	markerObject->initializePosition(x, z, y);
	markerObject->insertToZone(zone);
	return markerObject;
}

void FishingManagerImplementation::createSplash(float x, float y, float z, Zone* zone, PlayerCreature* player) {
	String splash = "object/tangible/fishing/shared_splash.iff";
	ManagedReference<SceneObject*> splashObject = zoneServer->createObject(splash.hashCode(), 0);
	splashObject->initializePosition(x,z+0.5,y);
	splashObject->insertToZone(zone);
	createFishingSplashEvent(player,zoneServer,splashObject);
}

void FishingManagerImplementation::updateMarker(PlayerCreature* player, int nextAction, SceneObject* marker) {

	// CALCULATING BOBBER POS
	Zone* zone = player->getZone();
	float x = (player->getPositionX()+marker->getPositionX())/2;
	float y = (player->getPositionY()+marker->getPositionY())/2;
	float z = marker->getPositionZ();

	removeMarker(player);

	ManagedReference<SceneObject*> newMarker = createMarker(x,y,z,zone);
	setFishMarker(player, newMarker);

}

void FishingManagerImplementation::removeMarker(PlayerCreature* player) {
	ManagedReference<SceneObject*> marker = getFishMarker(player);

	if (marker != NULL) {

		if (!marker->isPlayerCreature()) {

			setFishMarker(player, NULL);

			if (marker->isPersistent()) {
				marker->removeFromZone();
				marker->destroyObjectFromDatabase(true);
			} else {
				marker->removeFromZone();
			}
		}
	}
}

void FishingManagerImplementation::removeSplash(SceneObject* splash) {
	if (splash != NULL) {
		if (!splash->isPlayerCreature()) {
			if (splash->isPersistent()) {
				splash->removeFromZone();
				splash->destroyObjectFromDatabase(true);
			} else {
				splash->removeFromZone();
			}
		}
	}
}

void FishingManagerImplementation::createFishingSplashEvent(PlayerCreature* player, ZoneServer* zoneServer, SceneObject* splash) {
	Reference<FishingSplashEvent*> fishingSplashEvent = new FishingSplashEvent(player, zoneServer, splash);
	fishingSplashEvent->schedule(1000);
	player->setFishingSplashEvent(fishingSplashEvent);

	return;
}

void FishingManagerImplementation::createFishingEvent(PlayerCreature* player, int nextAction, ZoneServer* zoneServer, SceneObject* marker, int sum, uint32 boxID, int state) {
	Reference<FishingEvent*> fishingEvent = new FishingEvent(player, nextAction, zoneServer, marker, sum, boxID, state);
	fishingEvent->schedule(7000);
	player->setFishingEvent(fishingEvent);

	return;
}

void FishingManagerImplementation::stopFishingEvent(PlayerCreature* player) {
	Reference<FishingEvent*> fishingEvent = player->getFishingEvent();

	if (fishingEvent != NULL) {
		fishingEvent->cancel();
		player->setFishingEvent(NULL);
		fishingEvent = NULL;
	}
}

void FishingManagerImplementation::checkFishingOnPositionUpdate(PlayerCreature* player) {
	//info("running on pos update on manager", true);

	Reference<FishingEvent*> fishingEvent = player->getFishingEvent();
	int fishingState = getFishingState(player);

	if ((fishingState != FishingManager::NOTFISHING) && (fishingEvent != NULL)) {

		ManagedReference<SceneObject*> marker = fishingEvent->getMarker();

		if (((player->isSwimming()) || (!player->isInRange(marker, 10.0))) && (fishingState <= FishingManager::CATCH)) {
			//info("stopping fishing cause of movement?", true);
			stopFishing(player, 0, true);
		}

		if (player->isInRange(marker, 2.0)) {
			if (fishingState >= FishingManager::CATCH) {
				success(player, fishingEvent->getFish(), marker, 0);
			} else {
				//info("stopping fishing cause too far from marker?", true);
				stopFishing(player, 0, true);
			}
		}
	} else if ((fishingEvent == NULL) && (fishingState != FishingManager::NOTFISHING)) {
		setFishingState(player, FishingManager::NOTFISHING);
	}
}
