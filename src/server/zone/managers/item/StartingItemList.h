/*
Copyright (C) 2007 <SWGEmu>

This File is part of Core3.

This program is free software; you can redistribute
it and/or modify it under the terms of the GNU Lesser
General Public License as published by the Free Software
Foundation; either version 2 of the License,
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

#ifndef STARTINGITEMLIST_H_
#define STARTINGITEMLIST_H_

#include "engine/engine.h"

#include "../../objects/tangible/TangibleObject.h"

class StartingProfession {
	Vector<TangibleObject*>* all;
	Vector<TangibleObject*>* humanoidMale;
	Vector<TangibleObject*>* humanoidFemale;
	Vector<TangibleObject*>* trandoMale;
	Vector<TangibleObject*>* trandoFemale;
	Vector<TangibleObject*>* ithoMale;
	Vector<TangibleObject*>* ithoFemale;
	Vector<TangibleObject*>* wookMale;
	Vector<TangibleObject*>* wookFemale;

public:
	StartingProfession() {
		all = new Vector<TangibleObject*>();
		humanoidMale = new Vector<TangibleObject*>();
		humanoidFemale = new Vector<TangibleObject*>();
		trandoMale = new Vector<TangibleObject*>();
		trandoFemale = new Vector<TangibleObject*>();
		ithoMale = new Vector<TangibleObject*>();
		ithoFemale = new Vector<TangibleObject*>();
		wookMale = new Vector<TangibleObject*>();
		wookFemale = new Vector<TangibleObject*>();
	}

	~StartingProfession() {
		while (all->size() > 0) {
			TangibleObject* obj = all->get(0);

			all->remove(0);

			obj->finalize();
		}

		delete all;
		all = NULL;

		while (humanoidMale->size() > 0) {
			TangibleObject* obj = humanoidMale->get(0);

			humanoidMale->remove(0);

			obj->finalize();
		}

		delete humanoidMale;
		humanoidMale = NULL;

		while (humanoidFemale->size() > 0) {
			TangibleObject* obj = humanoidFemale->get(0);

			humanoidFemale->remove(0);

			obj->finalize();
		}

		delete humanoidFemale;
		humanoidFemale = NULL;

		while (trandoMale->size() > 0) {
			TangibleObject* obj = trandoMale->get(0);

			trandoMale->remove(0);

			obj->finalize();
		}

		delete trandoMale;
		trandoMale = NULL;

		while (trandoFemale->size() > 0) {
			TangibleObject* obj = trandoFemale->get(0);

			trandoFemale->remove(0);

			obj->finalize();
		}

		delete trandoFemale;
		trandoFemale = NULL;

		while (ithoMale->size() > 0) {
			TangibleObject* obj = ithoMale->get(0);

			ithoMale->remove(0);

			obj->finalize();
		}

		delete ithoMale;
		ithoMale = NULL;

		while (ithoFemale->size() > 0) {
			TangibleObject* obj = ithoFemale->get(0);

			ithoFemale->remove(0);

			obj->finalize();
		}

		delete ithoFemale;
		ithoFemale = NULL;

		while (wookMale->size() > 0) {
			TangibleObject* obj = wookMale->get(0);

			wookMale->remove(0);

			obj->finalize();
		}

		delete wookMale;
		wookMale = NULL;

		while (wookFemale->size() > 0) {
			TangibleObject* obj = wookFemale->get(0);

			wookFemale->remove(0);

			obj->finalize();
		}

		delete wookFemale;
		wookFemale = NULL;
	}

	Vector<TangibleObject*>* get(string species, string sex) {
		if (species.compare("all") == 0) {
			return all;
		} else if (species.compare("ithorian") == 0) {
			if(sex.compare("male") == 0) {
				return ithoMale;
			} else {
				return ithoFemale;
			}
		} else if (species.compare("trandoshan") == 0) {
			if(sex.compare("male") == 0) {
				return trandoMale;
			} else {
				return trandoFemale;
			}
		} else if (species.compare("wookiee") == 0) {
			if(sex.compare("male") == 0) {
				return wookMale;
			} else {
				return wookFemale;
			}
		} else {
			if(sex.compare("male") == 0) {
				return humanoidMale;
			} else {
				return humanoidFemale;
			}
		}
	}
};

class StartingItemProfessionSet : public HashTable<string, StartingProfession *> {
public:
	StartingItemProfessionSet() {

	}

	int hash(const string& str) {
		return String::hashCode(str);
	}
};

class StartingItemList {
	StartingItemProfessionSet * professions;

public:
	StartingItemList() {
		professions = new StartingItemProfessionSet();
		init();
	}

	~StartingItemList() {
		HashTableIterator<string, StartingProfession*> iterator(professions);

		iterator.resetIterator();

		while (iterator.hasNext()) {
			StartingProfession* prof = iterator.next();

			delete prof;
		}

		delete professions;
		professions = NULL;
	}

	void addItemToProfession(string profession, string species, string sex, TangibleObject* item) {
		professions->get(profession)->get(species, sex)->add(item);
	}

	Vector<TangibleObject*>* getProfessionItems(string profession, string species, string sex) {
		return (professions->get(profession)->get(species, sex));
	}

	void init() {
		professions->put("general", new StartingProfession());
		professions->put("artisan", new StartingProfession());
		professions->put("brawler", new StartingProfession());
		professions->put("entertainer", new StartingProfession());
		professions->put("marksman", new StartingProfession());
		professions->put("medic", new StartingProfession());
		professions->put("scout", new StartingProfession());
	}
};

#endif /*STARTINGITEMLIST_H_*/
