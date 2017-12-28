/*
 * FactionMap.h
 *
 *  Created on: Mar 17, 2011
 *      Author: crush
 */

#ifndef FACTIONRELATIONSHIPMAP_H_
#define FACTIONRELATIONSHIPMAP_H_

#include <algorithm>

#include "Faction.h"
#include "system/lang/String.h"
#include "system/util/VectorMap.h"

class FactionMap : public VectorMap<String, Faction> {
public:
	FactionMap() : VectorMap<String, Faction>() {
	}

	void addFaction(const Faction& faction);

	Faction* getFaction(const String& factionName);
};

#endif /* FACTIONRELATIONSHIPMAP_H_ */
