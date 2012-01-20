/*
 * FactionStandingList.h
 *
 *  Created on: Mar 16, 2011
 *      Author: crush
 */

#ifndef FACTIONSTANDINGLIST_H_
#define FACTIONSTANDINGLIST_H_

#include "engine/engine.h"

class FactionStandingList : public Serializable {
	String factionRank;
	int rebelPoints;
	int imperialPoints;
	VectorMap<String, float> factions;
	//int huttPoints; //Disabled

public:
	FactionStandingList() {
		factions.setAllowOverwriteInsertPlan();
		factions.setNullValue(0.f);

		rebelPoints = 0;
		imperialPoints = 0;

		addSerializableVariables();
	}

	FactionStandingList(const FactionStandingList& f) : Serializable() {
		factions.setAllowOverwriteInsertPlan();
		factions.setNullValue(0.f);

		factionRank = f.factionRank;
		rebelPoints = f.rebelPoints;
		imperialPoints = f.imperialPoints;
		factions = f.factions;

		addSerializableVariables();
	}

	FactionStandingList& operator=(const FactionStandingList& f) {
		if (this == &f)
			return *this;

		factionRank = f.factionRank;
		rebelPoints = f.rebelPoints;
		imperialPoints = f.imperialPoints;
		factions = f.factions;

		return *this;
	}

	void addSerializableVariables() {
		addSerializableVariable("factionRank", &factionRank);
		addSerializableVariable("rebelPoints", &rebelPoints);
		addSerializableVariable("imperialPoints", &imperialPoints);
		addSerializableVariable("factions", &factions);
	}

	float get(const String& faction) {
		return getFactionStanding(faction);
	}

	int size() {
		return factions.size();
	}

	void put(const String& faction, float amount) {
		if (faction == "imperial")
			setImperialPoints(amount);
		else if (faction == "rebel")
			setRebelPoints(amount);
		else
			factions.put(faction, amount);
	}

	float getFactionStanding(const String& faction) {
		if (faction == "imperial")
			return getImperialPoints();
		else if (faction == "rebel")
			return getRebelPoints();
		else
			return factions.get(faction);
	}

	bool contains(const String& faction) {
		if (faction == "imperial" || faction == "rebel")
			return true;
		else
			return factions.contains(faction);
	}

	bool isPvpFaction(const String& faction) {
		return faction == "imperial" || faction == "rebel";
	}

	String& getFactionRank() {
		return factionRank;
	}

	void setRebelPoints(int amount) {
		rebelPoints = amount;
	}

	void setImperialPoints(int amount) {
		imperialPoints = amount;
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

		int listSize = factions.size();

		message->insertInt(listSize);

		for (int i = 0; i < listSize; ++i) {
			VectorMapEntry<String, float>* entry = &factions.elementAt(i);

			message->insertAscii(entry->getKey());
		}

		message->insertInt(listSize);

		for (int i = 0; i < listSize; ++i)
			message->insertFloat(factions.get(i));
	}
};

#endif /* FACTIONSTANDINGLIST_H_ */
