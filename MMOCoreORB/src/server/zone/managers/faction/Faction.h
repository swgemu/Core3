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
	SortedVector<String> enemies;
	SortedVector<String> allies;

public:
	Faction() : Object() {
	}

	Faction(const String& name) : Object() {
		factionName = name;
	}

	Faction(const Faction& f) : Object() {
		factionName = f.factionName;
		enemies = f.enemies;
		allies = f.allies;
	}

	Faction& operator= (const Faction& f) {
		if (this == &f)
			return *this;

		factionName = f.factionName;
		enemies = f.enemies;
		allies = f.allies;

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

	String getFactionName() const {
		return factionName;
	}

	SortedVector<String>* getEnemies() {
		return &enemies;
	}

	SortedVector<String>* getAllies() {
		return &allies;
	}
};


#endif /* FACTIONRELATIONSHIP_H_ */
