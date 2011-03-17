/*
 * FactionRelationshipMap.cpp
 *
 *  Created on: Mar 17, 2011
 *      Author: crush
 */

#include "FactionRelationship.h"
#include "FactionRelationshipMap.h"

void FactionRelationshipMap::addFactionRelationship(const String& faction, const String& enemyList, const String& allyList) {
	if (contains(faction))
		drop(faction);

	FactionRelationship factionRelationship(faction);
	factionRelationship.parseEnemiesFromList(enemyList);
	factionRelationship.parseAlliesFromList(allyList);

	put(faction, factionRelationship);
}

FactionRelationship* FactionRelationshipMap::getFactionRelationship(const String& faction) {
	if (!contains(faction))
		return NULL;

	return &get(faction);
}
