/*
 * FactionRelationship.h
 *
 *  Created on: Mar 17, 2011
 *      Author: crush
 */

#ifndef FACTIONRELATIONSHIP_H_
#define FACTIONRELATIONSHIP_H_

#include "engine/engine.h"

class FactionRelationship : public Object {
	String factionName;
	SortedVector<String> enemies;
	SortedVector<String> allies;

public:
	FactionRelationship() : Object() {
	}

	FactionRelationship(const String& name) : Object() {
		factionName = name;
	}

	FactionRelationship(const FactionRelationship& fe) : Object() {
		factionName = fe.factionName;
		enemies = fe.enemies;
		allies = fe.allies;
	}

	FactionRelationship& operator= (const FactionRelationship& fe) {
		if (this == &fe)
			return *this;

		factionName = fe.factionName;
		enemies = fe.enemies;
		allies = fe.allies;

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

	String& getFactionName() {
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
