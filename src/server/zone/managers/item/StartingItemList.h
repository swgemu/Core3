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
#include "../../objects/tangible/TangibleObjectImplementation.h"

class TangibleObjectImplementation;

class StartingProfession {
	Vector<TangibleObjectImplementation *> * all;
	Vector<TangibleObjectImplementation *> * humanoidMale;
	Vector<TangibleObjectImplementation *> * humanoidFemale;
	Vector<TangibleObjectImplementation *> * trandoMale;
	Vector<TangibleObjectImplementation *> * trandoFemale;
	Vector<TangibleObjectImplementation *> * ithoMale;
	Vector<TangibleObjectImplementation *> * ithoFemale;
	Vector<TangibleObjectImplementation *> * wookMale;
	Vector<TangibleObjectImplementation *> * wookFemale;
	
public:	
	StartingProfession() {
		all = new Vector<TangibleObjectImplementation *>();
		humanoidMale = new Vector<TangibleObjectImplementation *>();
		humanoidFemale = new Vector<TangibleObjectImplementation *>();
		trandoMale = new Vector<TangibleObjectImplementation *>();
		trandoFemale = new Vector<TangibleObjectImplementation *>();
		ithoMale = new Vector<TangibleObjectImplementation *>();
		ithoFemale = new Vector<TangibleObjectImplementation *>();
		wookMale = new Vector<TangibleObjectImplementation *>();
		wookFemale = new Vector<TangibleObjectImplementation *>();
	}
	
	Vector<TangibleObjectImplementation *> * get(string species, string sex) {
		if(species.compare("all") == 0) {
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
		int h = 0;
		for (int i = 0; i < str.length(); i++) {
		    h = 31*h + str.at(i);
		}
		
		return h;
	}
};

class StartingItemList {
	StartingItemProfessionSet * professions;
public:
	StartingItemList() {
		professions = new StartingItemProfessionSet();
		init();
	}
	void addItemToProfession(string profession, string species, string sex, TangibleObjectImplementation * item) {
		professions->get(profession)->get(species, sex)->add(item);
	}
	
	Vector<TangibleObjectImplementation *> * getProfessionItems(string profession, string species, string sex) {
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
