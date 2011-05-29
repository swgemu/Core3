/*
 Copyright (C) 2010 <SWGEmu>

 This File is part of Core3.

 This program is free software; you can redistribute
 it and/or modify it under the terms of the GNU Lesser
 General Public License as published by the Free Software
 Foundation; either version 3 of the License,
 or (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 See the GNU Lesser General Public License for
 more details.

 You should have received a copy of the GNU Lesser General
 Public License along with this program; if not, write to
 the Free Software Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA

 Linking Engine3 statically or dynamically with other modules
 is making a combined work based on Engine3.
 Thus, the terms and conditions of the GNU Lesser General Public License
 cover the whole combination.

 In addition, as a special exception, the copyright holders of Engine3
 give you permission to combine Engine3 program with free software
 programs or libraries that are released under the GNU LGPL and with
 code included in the standard release of Core3 under the GNU LGPL
 license (or modified versions of such code, with unchanged license).
 You may copy and distribute such a system following the terms of the
 GNU LGPL for Engine3 and the licenses of the other code concerned,
 provided that you include the source code of that other code when
 and as the GNU LGPL requires distribution of source code.

 Note that people who make modified versions of Engine3 are not obligated
 to grant this special exception for their modified versions;
 it is their choice whether to do so. The GNU Lesser General Public License
 gives permission to release a modified version without this exception;
 this exception also makes it possible to release a modified version
 which carries forward this exception.
 */

#include "ResourceSpawn.h"
#include "server/zone/ZoneProcessServer.h"
#include "server/zone/Zone.h"
#include "server/zone/objects/resource/ResourceContainer.h"
#include "server/zone/managers/object/ObjectManager.h"
#include "server/zone/managers/crafting/CraftingManager.h"

#include "server/zone/objects/player/sui/listbox/SuiListBox.h"

void ResourceSpawnImplementation::initializeTransientMembers() {

}

void ResourceSpawnImplementation::fillAttributeList(AttributeListMessage* alm,
		PlayerCreature* object) {

		alm->insertAttribute("resource_class", getFinalClass());

		for (int i = 0; i < spawnAttributes.size(); ++i) {
			String attrib;
			int value = getAttributeAndValue(attrib, i);
			alm->insertAttribute(attrib, value);
		}

		alm->insertInt(0);
}

bool ResourceSpawnImplementation::inShift() {
	return despawned > time(0);
}

void ResourceSpawnImplementation::addAttribute(const String& attribute, int value) {
	spawnAttributes.put(attribute, value);
}

int ResourceSpawnImplementation::getAttributeAndValue(String& attribute,
		int index) {

	if (index < spawnAttributes.size()) {
		attribute = spawnAttributes.elementAt(index).getKey();
		return spawnAttributes.get(index);
	} else {
		return 0;
	}
}

int ResourceSpawnImplementation::getValueOf(int stat) {

	String attribute = "";

	switch(stat) {
	case CraftingManager::CR:
		attribute = "res_cold_resist";
		break;
	case CraftingManager::CD:
		attribute = "res_conductivity";
		break;
	case CraftingManager::DR:
		attribute = "res_decay_resist";
		break;
	case CraftingManager::HR:
		attribute = "res_heat_resist";
		break;
	case CraftingManager::FL:
		attribute = "res_flavor";
		break;
	case CraftingManager::MA:
		attribute = "res_malleability";
		break;
	case CraftingManager::PE:
		attribute = "res_potential_energy";
		break;
	case CraftingManager::OQ:
		attribute = "res_quality";
		break;
	case CraftingManager::SR:
		attribute = "res_shock_resistance";
		break;
	case CraftingManager::UT:
		attribute = "res_toughness";
		break;
	default:
		return 0;
		break;
	}

	if(spawnAttributes.contains(attribute))
		return spawnAttributes.get(attribute);

	return 0;
}

bool ResourceSpawnImplementation::isUnknownType() {
	for (int i = 0; i < stfSpawnClasses.size(); ++i) {
		if (stfSpawnClasses.get(i).indexOf("unknown") != -1)
			return true;
	}
	return false;
}

String ResourceSpawnImplementation::getFamilyName() {
   	int offset = 2;

   	if(isUnknownType())
   		offset = 1;

   	if(spawnClasses.size() > offset)
   		return spawnClasses.get(spawnClasses.size() - offset);
   	else
   		return "";
}

void ResourceSpawnImplementation::createSpawnMaps(bool jtl, int minpool, int maxpool,
		const String& zonerestriction, Vector<String>& activeZones) {

	int concentration = getConcentration(jtl);
	Vector<String> zonenames = getSpawnZones(minpool, maxpool, zonerestriction, activeZones);

	for (int i = 0; i < zonenames.size(); ++i) {

		Zone* zone = server->getZoneServer()->getZone(zonenames.get(i));
		if (zone == NULL)
			continue;

		SpawnDensityMap newMap(isType("ore"), concentration, zone->getMinX(),
				zone->getMaxX(), zone->getMinY(), zone->getMaxY());

		spawnMaps.put(zonenames.get(i), newMap);
	}
}

int ResourceSpawnImplementation::getConcentration(bool jtl) {
	/**
	 * Here we are using defined rules to set the max
	 * density of this specific spawn
	 */

	if (jtl || isType("chemical") || isType("gas_inert"))
		return SpawnDensityMap::HIGHDENSITY;

	else if (isType("ore") || isType("water") || isType("energy_renewable_unlimited_solar") || isType("energy_renewable_unlimited_wind"))
		return SpawnDensityMap::LOWDENSITY;

	else
		return SpawnDensityMap::MEDIUMDENSITY;
}

Vector<String> ResourceSpawnImplementation::getSpawnZones(int minpool, int maxpool,
		const String& zonerestriction, Vector<String>& activeZones) {

	/**
	 * Here we are using defined rules to set the number
	 * of zones and specific zones of this specific spawn
	 */
	Vector<String> zonenames;
	int zonecount = 0;

	if(minpool == maxpool)
		zonecount = maxpool;
	else
		zonecount = System::random(maxpool - minpool) + minpool;

	if(zonecount > activeZones.size())
		zonecount = activeZones.size();

	/// If resource is zone restricted, add only the restricted zone
	if (zonerestriction != "") {
		zonenames.add(zonerestriction);
		return zonenames;
	}

	/// Randomly remove entries until the Vector contains
	/// a number of elements equal to zonecount
	while (activeZones.size() > zonecount)
		activeZones.remove(System::random(activeZones.size() - 1));

	return activeZones;
}

float ResourceSpawnImplementation::getDensityAt(const String& zoneName, float x, float y) {
	if (!spawnMaps.contains(zoneName))
		return 0;

	SpawnDensityMap map = spawnMaps.get(zoneName);

	return map.getDensityAt(x, y);
}

String ResourceSpawnImplementation::getSpawnMapZone(int i) {
	if (spawnMaps.size() > i)
		return spawnMaps.elementAt(i).getKey();
	else
		return "";
}

uint32 ResourceSpawnImplementation::getPlanetCRC() {
	String zoneName = getSpawnMapZone(0);

	if (zoneName == "")
		return 0;

	Zone* zone = server->getZoneServer()->getZone(zoneName);

	return zone->getZoneCRC();
}

void ResourceSpawnImplementation::extractResource(const String& zoneName, int units) {
	unitsInCirculation += units;

}

ResourceContainer* ResourceSpawnImplementation::createResource(int units) {
   	ResourceContainer* newResource = NULL;

   	newResource = dynamic_cast<ResourceContainer*>(getZoneServer()->createObject(containerCRC, 2));

   	if(newResource == NULL) {
   		error("Unable to create resource container, using generic.  CRC attempted was: " + String::valueOf(containerCRC));
   		print();
   		String genericContainer = "object/resource_container/organic_food.iff";
   		newResource = dynamic_cast<ResourceContainer*>(getZoneServer()->createObject(genericContainer.hashCode(), 2));
   	}

   	newResource->setSpawnObject(_this);

   	if (units != 0)
   		newResource->setQuantity(units);

   	StringId customString;
   	customString.setCustomString(getFamilyName());
   	newResource->setObjectName(customString);
   	newResource->updateToDatabase();

   	++containerReferenceCount;

   	return newResource;
}

void ResourceSpawnImplementation::decreaseContainerReferenceCount() {
	/*if (--containerReferenceCount < 1 && !inShift()) {
		destroyObjectFromDatabase(true);

		dbDestroyed = true;
	}*/
}
void ResourceSpawnImplementation::addStatsToDeedListBox(SuiListBox* suil) {

	String tempname = "Name = " + spawnName;
	suil->addMenuItem(tempname);

	for (int i = 0; i < spawnAttributes.size(); ++i) {
		String attrib;
		int value = getAttributeAndValue(attrib, i);

		String tempstat = "@obj_attr_n:" + attrib + " = " + value;
		suil->addMenuItem(tempstat);
	}
}

void ResourceSpawnImplementation::print() {
	info("**** Resource Data ****\n", true);
	info("Class: " + getFinalClass(), true);
	info("Name: " + spawnName, true);
	info("--------Classes--------", true);
	for (int i = 0; i < spawnClasses.size(); ++i)
		info(spawnClasses.get(i) + "(" + stfSpawnClasses.get(i) + ")", true);
	info("------Attributes-------", true);

	for (int i = 0; i < spawnAttributes.size(); ++i) {
		String attrib;
		int value = getAttributeAndValue(attrib, i);
		info(attrib + " " + value, true);
	}

	for (int i = 0; i < spawnMaps.size(); ++i) {
		info(spawnMaps.elementAt(i).getKey());
		spawnMaps.get(i).print();
	}

	info("***********************", true);
}
