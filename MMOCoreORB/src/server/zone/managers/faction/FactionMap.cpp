/*
 * FactionMap.cpp
 *
 *  Created on: Mar 17, 2011
 *      Author: crush
 */

#include "Faction.h"
#include "FactionMap.h"

void FactionMap::addFaction(const Faction& faction) {
	String factionName = faction.getFactionName();

	if (contains(factionName))
		drop(factionName);

	put(factionName, faction);
}

Faction* FactionMap::getFaction(const String& factionName) {
	if (!contains(factionName))
		return NULL;

	return &get(factionName);
}
