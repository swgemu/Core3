
#include "server/zone/objects/tangible/deed/eventperk/EventPerkDeed.h"
#include "server/zone/objects/tangible/tasks/RemoveEventPerkDeedTask.h"
#include "server/zone/objects/tangible/components/EventPerkDataComponent.h"
#include "server/zone/Zone.h"
#include "server/zone/ZoneProcessServer.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/objects/region/CityRegion.h"
#include "server/zone/objects/area/ActiveArea.h"
#include "server/zone/objects/structure/StructureObject.h"
#include "templates/tangible/EventPerkDeedTemplate.h"
#include "server/zone/packets/object/ObjectMenuResponse.h"
#include "server/zone/managers/planet/PlanetManager.h"
#include "server/zone/managers/structure/StructureManager.h"
#include "terrain/manager/TerrainManager.h"
#include "server/zone/managers/name/NameManager.h"
#include "server/zone/objects/player/sessions/NpcActorCreationSession.h"

void EventPerkDeedImplementation::initializeTransientMembers() {
	DeedImplementation::initializeTransientMembers();

	activateRemoveEvent();
}

void EventPerkDeedImplementation::loadTemplateData(SharedObjectTemplate* templateData) {
	DeedImplementation::loadTemplateData(templateData);
	EventPerkDeedTemplate* deedData = dynamic_cast<EventPerkDeedTemplate*>(templateData);

	if (deedData == nullptr)
		return;

	generatedTimeToLive = deedData->getGeneratedTimeToLive();
	perkType = deedData->getPerkType();
}

void EventPerkDeedImplementation::fillAttributeList(AttributeListMessage* alm, CreatureObject* object) {
	DeedImplementation::fillAttributeList(alm, object);

	alm->insertAttribute("duration", getDurationString()); // Duration
}

void EventPerkDeedImplementation::fillObjectMenuResponse(ObjectMenuResponse* menuResponse, CreatureObject* player) {
	DeedImplementation::fillObjectMenuResponse(menuResponse, player);

	if (isASubChildOf(player)) {
		menuResponse->addRadialMenuItem(20, 3, "@event_perk:use_event_perk"); // Deploy Rental
	}
}

int EventPerkDeedImplementation::handleObjectMenuSelect(CreatureObject* player, byte selectedID) {
	if (!isASubChildOf(player)) {
		return 1;
	}

	if (selectedID == 20) {
		if (generated) {
			return 1;
		}

		auto zone = player->getZone();

		if (zone == nullptr) {
			return 1;
		}

		PlanetManager* planetManager = zone->getPlanetManager();

		if (planetManager == nullptr) {
			return 1;
		}

		EventPerkDeedTemplate* deedTemplate = cast<EventPerkDeedTemplate*>(getObjectTemplate());

		if (deedTemplate == nullptr) {
			return 1;
		}

		if (zone->isSpaceZone()) {
			player->sendSystemMessage("@event_perk:not_in_space"); // You may not deploy a Rental in space. Return to the ground first.
			return 1;
		}

		if (!deedTemplate->isAllowedZone(zone->getZoneName())) {
			player->sendSystemMessage("@event_perk:not_on_this_planet"); // You cannot deploy this rental on this planet. Examine the deed to determine the intended planet for this rental.
			return 1;
		}

		if (!isASubChildOf(player)) {
			player->sendSystemMessage("@event_perk:from_inventory_only"); // This rental must be in your inventory in order to be deployed.
			return 1;
		}

		ManagedReference<SceneObject*> parent = player->getParent().get();

		if (parent != nullptr && parent->isCellObject()) {
			player->sendSystemMessage("@event_perk:not_inside"); // You cannot deploy a Rental indoors. You must move outside.
			return 1;
		}

		if (player->isInCombat()) {
			player->sendSystemMessage("@event_perk:not_in_combat"); // You cannot deploy a Rental while in combat.
			return 1;
		}

		if (player->isSwimming()) {
			player->sendSystemMessage("@event_perk:not_while_swimming"); // You cannot deploy a Rental while swimming.
			return 1;
		}

		auto ghost = player->getPlayerObject();
		bool bypassChecks = (ghost != nullptr && ghost->isPrivileged());

		// Skip checks if prop is being placed by a privileged player
		if (!bypassChecks) {
			ManagedReference<CityRegion*> city = player->getCityRegion().get();

			if (city != nullptr) {
				if (city->isClientRegion()) {
					player->sendSystemMessage("@event_perk:not_in_municipal_zone"); // You may not place a Rental in a municipal zone.
					return 1;
				}

				if (city->isZoningEnabled() && !city->hasZoningRights(player->getObjectID())) {
					player->sendSystemMessage("@event_perk:no_zoning_rights"); // You must have zoning rights to place a Rental in this city.
					return 1;
				}
			}

			int x = player->getWorldPositionX();
			int y = player->getWorldPositionY();
			int nearbyPerks = 0;

			TerrainManager* terrainManager = planetManager->getTerrainManager();
			if ( terrainManager == nullptr || terrainManager->getHighestHeightDifference(x - 10, y - 10, x + 10, y + 10) > 15.0) {
				player->sendSystemMessage("@event_perk:bad_area"); // This rental could not be deployed due to the surrounding terrain. Please move to another area and try again.
				return 1;
			}

			CloseObjectsVector* vec = (CloseObjectsVector*) player->getCloseObjects();

			if (vec == nullptr) {
#ifdef COV_DEBUG
				error("Player has nullptr closeObjectsVector in EventPerkDeedImplementation::handleObjectMenuSelect");
#endif
				return 1;
			}

			SortedVector<TreeEntry*> closeObjects;
			vec->safeCopyTo(closeObjects);

			for (int i = 0; i < closeObjects.size(); ++i) {
				SceneObject* obj = cast<SceneObject*>(closeObjects.get(i));

				if (obj == nullptr) {
					continue;
				}

				SharedObjectTemplate* objectTemplate = obj->getObjectTemplate();
				if (objectTemplate == nullptr) {
					continue;
				}

				float radius = objectTemplate->getNoBuildRadius();

				if (obj->isLairObject() && player->isInRange(obj, radius)) {
					player->sendSystemMessage("@event_perk:too_close_lair"); // You cannot place a Rental this close to a lair.
					return 1;
				}

				if (obj->isCampStructure() && player->isInRange(obj, radius)) {
					player->sendSystemMessage("@event_perk:too_close_camp"); // You cannot place a Rental this close to a camp.
					return 1;
				}

				if (radius > 0 && player->isInRange(obj, radius)) {
					player->sendSystemMessage("@event_perk:too_close_something"); // You are too close to an object to deploy your Rental here. Move away from it.
					return 1;
				}

				if (objectTemplate->isSharedStructureObjectTemplate()) {
					if (StructureManager::instance()->isInStructureFootprint(cast<StructureObject*>(obj), x, y, 0)) {
						player->sendSystemMessage("@event_perk:too_close_building"); // You may not place a Rental this close to a building.
						return 1;
					}
				}

				if (obj->isEventPerk() && player->isInRange(obj, 32) && ++nearbyPerks > 2) {
					player->sendSystemMessage("@event_perk:too_many_perks"); // There are too many Rentals already deployed in this area. Please move to another location.
					return 1;
				}
			}

			SortedVector<ManagedReference<ActiveArea* > > activeAreas;
			zone->getInRangeActiveAreas(x, 0, y, &activeAreas, true);

			for (int i = 0; i < activeAreas.size(); ++i) {
				ActiveArea* area = activeAreas.get(i);

				if (area->isNoBuildZone()) {
					player->sendSystemMessage("@event_perk:too_close_something"); // You are too close to an object to deploy your Rental here. Move away from it.
					return 1;
				}
			}

			if (planetManager->isInRangeWithPoi(x, y, 150)) {
				player->sendSystemMessage("@event_perk:too_close_something"); // You are too close to an object to deploy your Rental here. Move away from it.
				return 1;
			}
		}

		// Handle UI for NPC Actor, where player will select their chosen NPC type
		if (perkType == EventPerkDeedTemplate::NPCACTOR) {
			// Call placement UI
			createNpcActorPerk(player);

			return DeedImplementation::handleObjectMenuSelect(player, selectedID);
		}

		// All other event perk deeds spawn their objects
		ManagedReference<TangibleObject*> object = generatedObject.get();

		if (object == nullptr) {
			object = (server->getZoneServer()->createObject(generatedObjectTemplate.hashCode(), "playerstructures", 1)).castTo<TangibleObject*>();

			if (object == nullptr) {
				player->sendSystemMessage("Error generating object. Wrong generatedObjectTemplate or is not a tangible object.");
				return 1;
			}

			generatedObject = object;
		}

		auto thisEventDeed = _this.getReferenceUnsafeStaticCast();

		Locker locker(object, thisEventDeed);

		EventPerkDataComponent* data = cast<EventPerkDataComponent*>(object->getDataObjectComponent()->get());

		if (data == nullptr) {
			player->sendSystemMessage("Error: no dataObjectComponent.");
			object->destroyObjectFromDatabase(true);
			return 1;
		}

		data->setDeed(thisEventDeed);

		object->initializePosition(player->getPositionX(), player->getPositionZ(), player->getPositionY());
		object->setDirection(Math::deg2rad(player->getDirectionAngle()));

		zone->transferObject(object, -1, true);

		object->createChildObjects();
		parseChildObjects(object);

		// object/tangible/event_perk/race_droid.iff
		// Values stored using setLuaStringData because the perk is handled from lua
		if (object->getServerObjectCRC() == 0x785C60BF) {
			object->setLuaStringData("ownerID", String::valueOf(player->getObjectID()));
		}

		generated = true;

		if (removeEventPerkDeedTask != nullptr && generatedTimeToLive > 0) {
			Time currentTime;
			uint64 timeDelta = currentTime.getMiliTime() - purchaseTime.getMiliTime();

			if (timeDelta >= generatedTimeToLive)
				removeEventPerkDeedTask->execute();
			else
				removeEventPerkDeedTask->reschedule(generatedTimeToLive - timeDelta);
		}

		destroyObjectFromWorld(true);

		return 0;
	}

	return DeedImplementation::handleObjectMenuSelect(player, selectedID);
}

void EventPerkDeedImplementation::parseChildObjects(SceneObject* parent) {
	EventPerkDataComponent* data = cast<EventPerkDataComponent*>(parent->getDataObjectComponent()->get());

	if (data == nullptr)
		return;

	EventPerkDeed* deed = data->getDeed();

	if (deed == nullptr)
		return;

	int perkType = getPerkType();

	SortedVector<ManagedReference<SceneObject*> >* children = parent->getChildObjects();

	for (int j = 0; j < children->size(); j++) {
		SceneObject* child = children->get(j);

		if (child != nullptr)	{
			Locker cLock(child, parent);

			ContainerPermissions* permissions = child->getContainerPermissionsForUpdate();
			permissions->setOwner(parent->getObjectID());
			permissions->setInheritPermissionsFromParent(false);
			permissions->setDefaultDenyPermission(ContainerPermissions::MOVECONTAINER);
			permissions->setDenyPermission("owner", ContainerPermissions::MOVECONTAINER);

			if (perkType == EventPerkDeedTemplate::HONORGUARD || perkType == EventPerkDeedTemplate::RECRUITER)
				child->setObjectMenuComponent("EventPerkMenuComponent");

			if (child->getServerObjectCRC() == 0xB2EC90B2) { // object/mobile/dressed_stormtrooper_m.iff
				int randNum = 100 + System::random(899);
				child->setCustomObjectName("TK-" + String::valueOf(randNum), true);
			} else if (child->getServerObjectCRC() == 0x3AADC9C4) { // object/mobile/dressed_tie_fighter_m.iff
				int randNum = 100 + System::random(899);
				child->setCustomObjectName("DS-" + String::valueOf(randNum), true);
			} else if (child->getServerObjectCRC() == 0xD5985A18) { // object/mobile/atat.iff
				child->setCustomObjectName("AT-AT", true);
			} else if (child->getServerObjectCRC() == 0x55898ADF) { // object/mobile/atst.iff
				child->setCustomObjectName("AT-ST", true);
			} else if (child->getServerObjectCRC() == 0xCF9AC86C) { // object/mobile/bantha_saddle.iff
				child->setCustomObjectName("a bantha mount", true);
			} else if (child->getObjectTemplate()->getFullTemplateString().indexOf("object/mobile") != -1 && perkType != EventPerkDeedTemplate::RECRUITER) {
				ZoneProcessServer* zps = parent->getZoneProcessServer();
				NameManager* nameManager = zps->getNameManager();
				String name = "";

				if (child->getServerObjectCRC() == 0xA87E2035) { // object/mobile/cll8_binary_load_lifter.iff
					name = "a CLL-8 binary load lifter";
				} else if (child->getServerObjectCRC() == 0xF1DED7AD) { // object/mobile/eg6_power_droid.iff
					name = nameManager->makeDroidName(NameManagerType::DROID_EG6);
				} else if (child->getServerObjectCRC() == 0x6C1D79FD) { // object/mobile/r2.iff
					name = nameManager->makeDroidName(NameManagerType::R2);
				} else if (child->getServerObjectCRC() == 0x25101E70) { // object/mobile/r3.iff
					name = nameManager->makeDroidName(NameManagerType::R3);
				} else if (child->getServerObjectCRC() == 0xDEF33564) { // object/mobile/r4.iff
					name = nameManager->makeDroidName(NameManagerType::R4);
				} else if (child->getServerObjectCRC() == 0x97FE52E9) { // object/mobile/r5.iff
					name = nameManager->makeDroidName(NameManagerType::R5);
				} else if (child->getServerObjectCRC() == 0x905BB76C) { // object/mobile/ra7_bug_droid.iff
					name = nameManager->makeDroidName(NameManagerType::DROID_RA7);
				} else if (perkType == EventPerkDeedTemplate::NPCACTOR) {
					String currentName = child->getCustomObjectName().toString();

					if (currentName.isEmpty() || !currentName.contains("(an NPC actor)")) {
						name = currentName + " (an NPC actor)"; // ("title_append", " (an NPC actor)");
					} else {
						name = currentName;
					}

					// Set the menu component for the actor
					child->setObjectMenuComponent("EventPerkActorMenuComponent");

					// Set the container component for the actor
					child->setContainerComponent("EventPerkActorContainerComponent");
				} else {
					name = nameManager->makeCreatureName();

					if (child->getServerObjectCRC() == 0x63371470) // object/mobile/dressed_corsec_officer_human_male_01.iff
						name = name + " (a CorSec trooper)";
					else if (child->getServerObjectCRC() == 0x86752E27) // object/mobile/dressed_fed_dub_patrolman_human_male_01.iff
						name = name + " (a Fed-Dub patrolman)";
					else if (child->getServerObjectCRC() == 0x450C04C9) // object/mobile/dressed_rebel_crewman_human_male_01.iff
						name = name + " (a Rebel crewman)";
					else if (child->getServerObjectCRC() == 0xF171DF10) // object/mobile/dressed_rsf_security_guard.iff
						name = name + " (an RSF security guard)";
					else if (child->getServerObjectCRC() == 0x7BD5CF73) // object/mobile/jawa.iff
						name = name + " (a jawa)";
				}

				child->setCustomObjectName(name, true);
			}
		}
	}
}

void EventPerkDeedImplementation::createNpcActorPerk(CreatureObject* player) {
	if (player == nullptr) {
		return;
	}

	auto zone = player->getZone();

	if (zone == nullptr) {
		return;
	}

	String zoneName = zone->getZoneName();

	//Create Session
	ManagedReference<NpcActorCreationSession*> session = new NpcActorCreationSession(player, _this.getReferenceUnsafeStaticCast(), zoneName);

	if (session == nullptr) {
		return;
	}

	session->initializeSession();
}

void EventPerkDeedImplementation::destroyObjectFromDatabase(bool destroyContainedObjects) {
	ManagedReference<CreatureObject*> strongOwner = owner.get();

	if (strongOwner != nullptr) {
		Locker clocker(strongOwner, _this.getReferenceUnsafeStaticCast());

		PlayerObject* ghost = strongOwner->getPlayerObject();

		if (ghost != nullptr) {
			ghost->removeEventPerk(_this.getReferenceUnsafeStaticCast());
		}
	}

	DeedImplementation::destroyObjectFromDatabase(destroyContainedObjects);
}

void EventPerkDeedImplementation::activateRemoveEvent(bool immediate) {
	uint64 timeToLive = EventPerkDeedTemplate::TIME_TO_LIVE;

	if (generated && generatedTimeToLive > 0) {
		timeToLive = generatedTimeToLive;
	}

	if (removeEventPerkDeedTask == nullptr) {
		removeEventPerkDeedTask = new RemoveEventPerkDeedTask(_this.getReferenceUnsafeStaticCast());

		if (removeEventPerkDeedTask == nullptr) {
			error() << "RemoveEventPerkDeedTask is null for Event Perk Deed -- " << getDisplayedName() << " ID: " << getObjectID();
			return;
		}

		// Get our current time in miliseconds
		Time currentTime;
		uint64 currentMili = currentTime.getMiliTime();

		// Expiration mili is the sum of the purchase time and the time to live
		uint64 expirationMili = purchaseTime.getMiliTime() + timeToLive;

		// Expiration time is in the past
		if (currentMili >= expirationMili || immediate) {
			// Schedule removal 5 minutes out to account for server loading
			removeEventPerkDeedTask->schedule(5 * 60 * 1000);
		} else {
			// Expiration time is in the future, schedule the task
			uint64 timeDelta = expirationMili - currentMili;

			removeEventPerkDeedTask->schedule(timeDelta);
		}
	} else if (immediate) {
		if (removeEventPerkDeedTask->isScheduled()) {
			removeEventPerkDeedTask->cancel();
		}

		removeEventPerkDeedTask->schedule(1000);
	}
}

String EventPerkDeedImplementation::getDurationString() {
	uint64 timeToLive = EventPerkDeedTemplate::TIME_TO_LIVE;

	// Get our current time in miliseconds
	Time currentTime;
	uint64 currentMili = currentTime.getMiliTime();

	// Expiration mili is the sum of the purchase time and the time to live
	uint64 expirationMili = purchaseTime.getMiliTime() + timeToLive;

	if (currentMili >= expirationMili) {
		return "";
	}

	uint32 timeDelta = expirationMili - currentMili;
	uint32 timestamp = timeDelta / 1000;

	String abbrvs[3] = {"seconds", "minutes", "hours"};

	int intervals[3] = {1, 60, 3600};
	int values[3] = {0, 0, 0};

	StringBuffer str;

	for (int i = 2; i > -1; --i) {
		values[i] = floor((float)timestamp / intervals[i]);
		timestamp -= values[i] * intervals[i];

		if (values[i] > 0) {
			if (str.length() > 0) {
				str << ", ";
			}

			str << values[i] << " " << abbrvs[i];
		}
	}

	return str.toString();
}
