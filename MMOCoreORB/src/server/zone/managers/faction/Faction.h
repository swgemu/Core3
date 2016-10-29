/*
 * Faction.h
 *
 *  Created on: Mar 17, 2011
 *      Author: crush
 */

#ifndef FACTIONRELATIONSHIP_H_
#define FACTIONRELATIONSHIP_H_

#include "engine/engine.h"

class Faction : public Object {
	String factionName;
	bool playerAllowed;
	SortedVector<String> enemies;
	SortedVector<String> allies;
	float adjustFactor;

public:

	Faction() : Object() {
		playerAllowed = true;
		adjustFactor = 1.0;
	}

	Faction(const String& name) : Object() {
		factionName = name;
		playerAllowed = true;
		adjustFactor = 1.0;
	}

	Faction(const Faction& f) : Object() {
		factionName = f.factionName;
		playerAllowed = f.playerAllowed;
		enemies = f.enemies;
		allies = f.allies;
		adjustFactor = f.adjustFactor;
	}

	Faction& operator= (const Faction& f) {
		if (this == &f)
			return *this;

		factionName = f.factionName;
		playerAllowed = f.playerAllowed;
		enemies = f.enemies;
		allies = f.allies;
		adjustFactor = f.adjustFactor;

		return *this;
	}

	void parseEnemiesFromList(const String& list) {
		StringTokenizer tokenizer(list);
		tokenizer.setDelimeter(",");

		while (tokenizer.hasMoreTokens()) {
			String token;
			tokenizer.getStringToken(token);

			enemies.put(token);
		}
	}

	void parseAlliesFromList(const String& list) {
		StringTokenizer tokenizer(list);
		tokenizer.setDelimeter(",");

		while (tokenizer.hasMoreTokens()) {
			String token;
			tokenizer.getStringToken(token);

			allies.put(token);
		}
	}

	const String& getFactionName() const {
		return factionName;
	}

	void setPlayerAllowed(bool allowed) {
		playerAllowed = allowed;
	}

	void setAdjustFactor(float factor) {
		adjustFactor = factor;
	}

	const SortedVector<String>* getEnemies() const {
		return &enemies;
	}

	const SortedVector<String>* getAllies() const {
		return &allies;
	}

	bool isPlayerAllowed() const {
		return playerAllowed;
	}

	float getAdjustFactor() const {
		return adjustFactor;
	}
};


#endif /* FACTIONRELATIONSHIP_H_ */
