/*
 * FactionStandingList.h
 *
 *  Created on: Mar 16, 2011
 *      Author: crush
 */

#ifndef FACTIONSTANDINGLIST_H_
#define FACTIONSTANDINGLIST_H_

#include "engine/engine.h"

class FactionStandingList : public VectorMap<String, float> {
	String factionRank;
	int rebelPoints;
	int imperialPoints;
	//int huttPoints; //Disabled

public:
	FactionStandingList() : VectorMap<String, float>() {
		setNoDuplicateInsertPlan();
		setNullValue(0.f);

		rebelPoints = 0;
		imperialPoints = 0;
	}

	float getFactionStanding(const String& faction) {
		return get(faction);
	}

	String& getFactionRank() {
		return factionRank;
	}

	void increaseRebelPoints(int amount) {
		rebelPoints += amount;
	}

	void decreaseRebelPoints(int amount) {
		rebelPoints -= amount;
	}

	void increaseImperialPoints(int amount) {
		imperialPoints += amount;
	}

	void decreaseImperialPoints(int amount) {
		imperialPoints -= amount;
	}

	void setFactionRank(const String& rank) {
		factionRank = rank;
	}

	int getImperialPoints() {
		return imperialPoints;
	}

	int getRebelPoints() {
		return rebelPoints;
	}

	int getHuttPoints() {
		return 0;
	}

	void insertToMessage(BaseMessage* message) {
		message->insertAscii(factionRank);
		message->insertInt(rebelPoints);
		message->insertInt(imperialPoints);
		message->insertInt(0); //Hutt Points;

		int listSize = size();

		message->insertInt(listSize);

		for (int i = 0; i < listSize; ++i) {
			VectorMapEntry<String, float>* entry = &elementAt(i);

			message->insertAscii(entry->getKey());
		}

		message->insertInt(listSize);

		for (int i = 0; i < listSize; ++i)
			message->insertFloat(get(i));
	}
};

#endif /* FACTIONSTANDINGLIST_H_ */
