/*
 * FactionRelationshipMap.h
 *
 *  Created on: Mar 17, 2011
 *      Author: crush
 */

#ifndef FACTIONRELATIONSHIPMAP_H_
#define FACTIONRELATIONSHIPMAP_H_

#include "engine/engine.h"
#include "FactionRelationship.h"

class FactionRelationshipMap : public VectorMap<String, FactionRelationship> {
public:
	FactionRelationshipMap() : VectorMap<String, FactionRelationship>() {
	}

	void addFactionRelationship(const String& faction, const String& enemyList, const String& allyList);

	FactionRelationship* getFactionRelationship(const String& faction);
};


#endif /* FACTIONRELATIONSHIPMAP_H_ */
