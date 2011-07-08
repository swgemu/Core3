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

#include <iostream>
#include <fstream>

#include "NameManager.h"

#include "../../ZoneServer.h"
#include "../../ZoneClientSession.h"
#include "../../objects/player/Races.h"
#include "server/zone/objects/creature/CreatureObject.h"

NameManager::NameManager(ZoneProcessServer* serv) : Logger("NameManager") {
	server = serv;

	profaneNames = new Vector<String>(55, 5); //based on the original number of banned words
	developerNames = new BannedNameSet();
	reservedNames = new BannedNameSet();
	fictionNames = new BannedNameSet();

	fillNames();

	setLogging(false);
}

NameManager::~NameManager() {
	delete(profaneNames);
	delete(developerNames);
	delete(reservedNames);
	delete(fictionNames);
}

void NameManager::fillNames() {
	File* restrictedFile = new File("conf/restrictednames.lst");

	try {
		FileReader restrictedReader(restrictedFile);

		info("parsing restricted names list: restrictednames.lst", true);

		BannedNameSet* setp;

		String line;
		bool isset = false;

		while (restrictedReader.readLine(line)) {
			String name = line.trim().toLowerCase();

			if ((name.length() >= 2 && name.subString(0, 2).compareTo("--") == 0)
					|| name == "") {
				continue; //skip it
			} else if (name.indexOf("[profane]") != -1) {
				isset = false;
				continue;
			} else if (name.indexOf("[developer]") != -1) {
				isset = true;
				setp = developerNames;
				continue;
			} else if (name.indexOf("[fiction]") != -1) {
				isset = true;
				setp = fictionNames;
				continue;
			} else if (name.indexOf("[reserved]") != -1) {
				isset = true;
				setp = reservedNames;
				continue;
			} else if (isset) {
				setp->add(name);
				continue;
			} else {
				profaneNames->add(name);
				continue;
			}
		}
	} catch (FileNotFoundException&e ) {
	}

	delete restrictedFile;
}


inline bool NameManager::isProfane(String name) {
	uint16 i;

	name = name.toLowerCase();

	for (i = 0; i < profaneNames->size(); i++) {
		if (name.indexOf(profaneNames->get(i)) != -1)
			return true;
	}

	return false;
}

inline bool NameManager::isDeveloper(String name) {
	return developerNames->contains(name.toLowerCase());
}

inline bool NameManager::isFiction(String name) {
	return fictionNames->contains(name.toLowerCase());
}

inline bool NameManager::isReserved(String name) {
	return reservedNames->contains(name.toLowerCase());
}

int NameManager::validateName(CreatureObject* obj) {
	StringId* objectName = obj->getObjectName();
	UnicodeString name = objectName->getCustomString();
	int species = obj->getSpecies();

	return validateName(name.toString(), species);
}

int NameManager::validateName(const String& name, int species) {
	if (name.isEmpty())
		return NameManagerResult::DECLINED_EMPTY;

	if (name.length() < 3)
		return NameManagerResult::DECLINED_RACE_INAPP;

	if (isProfane(name))
		return NameManagerResult::DECLINED_PROFANE;

	if (isDeveloper(name))
		return NameManagerResult::DECLINED_DEVELOPER;

	if (isFiction(name))
		return NameManagerResult::DECLINED_FICT_RESERVED;

	if (isReserved(name))
		return NameManagerResult::DECLINED_RESERVED;

	//Make sure that only valid characters are allowed in the name.
	if (strspn(name.toCharArray(), "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz'- ") != name.length())
		return NameManagerResult::DECLINED_SYNTAX;

	String fname, lname;

	//Split the name into first and last
	int spc = name.indexOf(" ");
	if (spc != -1) {
		fname = name.subString(0, spc);
		lname = name.subString(spc + 1, name.length());
	} else {
		fname = name;
		lname = "";
	}

	if (fname.length() < 3 || fname.length() > 15 || lname.length() > 20)
		return NameManagerResult::DECLINED_RACE_INAPP;

	//Wookies are not allowed to have last names.
	if (!lname.isEmpty() && species == CreatureObjectImplementation::WOOKIE)
		return NameManagerResult::DECLINED_RACE_INAPP;

	//If the name has a hyphen or apostrophe, make sure they are the proper species.
	if (name.indexOf("'") != -1 || name.indexOf("-") != -1) {
		//Must be a human, twilek, or moncal to have a hyphen or apostrophe.
		if (species != CreatureObjectImplementation::HUMAN && species != CreatureObjectImplementation::TWILEK && species != CreatureObjectImplementation::MONCAL)
			return NameManagerResult::DECLINED_RACE_INAPP;

		//Moncal's aren't allowed to have apostrophes.
		if (species == CreatureObjectImplementation::MONCAL && name.indexOf("'") != -1)
			return NameManagerResult::DECLINED_RACE_INAPP;

		//Make sure they only have one hyphen and apostrophe in firstname.
		if (fname.indexOf('\'') != fname.lastIndexOf('\'') || fname.indexOf('-') != fname.lastIndexOf('-'))
			return NameManagerResult::DECLINED_RACE_INAPP;

		//Make sure they only have one hyphen and apostrophe in lastname.
		if (lname.indexOf('\'') != lname.lastIndexOf('\'') || lname.indexOf('-') != lname.lastIndexOf('-'))
			return NameManagerResult::DECLINED_RACE_INAPP;
	}

	return NameManagerResult::ACCEPTED;
}

const String NameManager::makeCreatureName(bool surname) {
	bool lastName = surname;
	bool inLastName = false;
	int nameLength = 3 + System::random(3);
	char* name = (char*) malloc(sizeof(char) * (nameLength + 1));//new char[nameLength + 1];

	while (true) {
		int x = 0;

		name[0] = chooseNextLetter(' ', ' ');
		name[1] = chooseNextLetter(name[0], ' ');

		x = 2;

		for (; x < nameLength + 1; x++) {
			if (x < nameLength) {
				if (inLastName) {
					name[x] = Character::toUpperCase(chooseNextLetter(name[x-1], name[x-2]));
					inLastName = false;
				} else
					name[x] = chooseNextLetter(name[x-1], name[x-2]);
			} else {
				if (lastName && x == nameLength) {
					name[x] = ' ';
					nameLength += 4 + System::random(3);

					name = (char*) realloc(name, nameLength + 1);

					lastName = false;
					inLastName = true;
				} else {
					name[x] = '\0';
					break;
				}
			}
		}

		name[0] = toupper(name[0]);

		if (!isProfane(name))
			break;
	}
	
	String ret(name);

	//delete [] name;
	free(name);

	return ret;
}

const String NameManager::makeResourceName(bool isOrganic) {
	int nameLength = 4 + System::random(6);
	char* name = new char[nameLength + 1];

	int x = 0;

	while (true) {
		if (System::random(2) == 1 && nameLength > 5 && !isOrganic) {
			x = addPrefix(name);
		} else {
			name[0] = chooseNextLetter(' ', ' ');
			name[1] = chooseNextLetter(name[0], ' ');

			x = 2;
		}

		for (; x < nameLength + 1; x++) {
			if (x < nameLength) {
				name[x] = chooseNextLetter(name[x-1], name[x-2]);
			} else {
				if (System::random(1) == 1 && !isOrganic && !isVowel(name[x-1])	&& name[x-1] != 'q' && x < nameLength - 4)
					addSuffix(name, x);
				else
					name[x] = '\0';

				break;
			}
		}

		name[0] = toupper(name[0]);

		if (!isProfane(name))
			break;
	}

	String ret(name);

	delete [] name;

	return ret;
}

char NameManager::chooseNextLetter(const char lastLetter, const char letterBeforeLast) {
	if (letterBeforeLast == ' ' && lastLetter == ' ')
		return 97 + System::random(25);

	if ((!isVowel(lastLetter) && !isVowel(letterBeforeLast) && letterBeforeLast	!= ' ')
			|| (lastLetter == 'u' && letterBeforeLast == 'q')) {
		char exclusion[] = { 'b', 'c', 'd', 'f', 'g', 'h', 'j', 'k', 'l', 'm',
				'n', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
				'\0' };

		return chooseLetterExcluding(exclusion);
	}

	if ((isVowel(lastLetter) && isVowel(letterBeforeLast) && letterBeforeLast != ' ')) {
		char exclusion[] = { 'a', 'e', 'i', 'o', 'u', 'y', '\0' };

		return chooseLetterExcluding(exclusion);
	} else {
		switch (tolower(lastLetter)) {
		case 'a': {
			char exclusion[] = { 'a', 'e', '\0' };
			return chooseLetterExcluding(exclusion);
		}
		case 'b': {
			char exclusion[] = { 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'j', 'k',
					'm', 'n', 'p', 'q', 's', 't', 'v', 'w', 'x', 'z', '\0' };
			return chooseLetterExcluding(exclusion);
		}
		case 'c': {
			char exclusion[] = { 'b', 'c', 'd', 'f', 'g', 'j', 'k', 'm', 'n',
					'p', 'q', 's', 't', 'v', 'w', 'x', 'z', '\0' };
			return chooseLetterExcluding(exclusion);
		}
		case 'd': {
			char exclusion[] = { 'b', 'c', 'd', 'f', 'g', 'h', 'j', 'k', 'l', 'm',
					'n', 'p', 'q', 's', 't', 'v', 'w', 'x', 'y', 'z', '\0' };
			return chooseLetterExcluding(exclusion);
		}
		case 'f': {
			char exclusion[] = { 'b', 'c', 'd', 'f', 'g', 'h', 'j', 'k', 'm',
					'n', 'p', 'q', 's', 't', 'v', 'w', 'x', 'z', '\0' };
			return chooseLetterExcluding(exclusion);
		}
		case 'g': {
			char exclusion[] = { 'b', 'c', 'd', 'f', 'g', 'j', 'k', 'm', 'n',
					'p', 'q', 's', 't', 'v', 'w', 'x', 'z', '\0' };
			return chooseLetterExcluding(exclusion);
		}
		case 'h': {
			char exclusion[] = { 'b', 'c', 'd', 'f', 'g', 'h', 'j', 'k',
					'l', 'm', 'n', 'p', 'q', 'r', 's', 't', 'v', 'w',
					'x', 'z', '\0' };
			return chooseLetterExcluding(exclusion);
		}
		case 'i': {
			char exclusion[] = { 'i', 'j', 'u', '\0' };
			return chooseLetterExcluding(exclusion);
		}
		case 'j': {
			char exclusion[] = { 'b', 'c', 'd', 'f', 'g', 'h', 'j', 'k', 'l',
					'm', 'n', 'p', 'q', 'r', 's', 't', 'v', 'w', 'x', 'y', 'z',
					'\0' };
			return chooseLetterExcluding(exclusion);
		}
		case 'k': {
			char exclusion[] = { 'b', 'c', 'd', 'f', 'g', 'h', 'j', 'k', 'm',
					'n', 'p', 'q', 's', 't', 'v', 'w', 'x', 'z', '\0' };
			return chooseLetterExcluding(exclusion);
		}
		case 'l': {
			char exclusion[] = { 'b', 'c', 'd', 'f', 'g', 'h', 'j', 'k',
					'l', 'm', 'n', 'p', 'q', 'r', 's', 'v', 'w',
					'x', 'z', '\0' };
			return chooseLetterExcluding(exclusion);
		}
		case 'm': {
			char exclusion[] = { 'b', 'c', 'd', 'f', 'g', 'h', 'j', 'k', 'l',
					'm', 'n', 'p', 'q', 'r', 's', 't', 'v', 'w', 'x', 'y', 'z',
					'\0' };
			return chooseLetterExcluding(exclusion);
		}
		case 'n': {
			char exclusion[] = { 'b', 'c', 'd', 'f', 'g', 'h', 'j', 'k', 'l',
					'm', 'n', 'p', 'q', 'r', 's', 't', 'v', 'w', 'x', 'y', 'z',
					'\0' };
			return chooseLetterExcluding(exclusion);
		}
		case 'p': {
			char exclusion[] = { 'b', 'c', 'd', 'f', 'g', 'j', 'k', 'm', 'n',
					'p', 'q', 's', 't', 'v', 'w', 'x', 'y', 'z', '\0' };
			return chooseLetterExcluding(exclusion);
		}
		case 'q':
			return 'u';
		case 'r': {
			char exclusion[] = { 'b', 'c', 'd', 'f', 'g', 'h', 'j', 'k',
					'l', 'm', 'n', 'p', 'q', 'r', 's', 't', 'v', 'w',
					'x', 'z', '\0' };
			return chooseLetterExcluding(exclusion);
		}
		case 's': {
			char exclusion[] = { 'b', 'd', 'f', 'g', 'j', 'v', 'x', 'y', 'z',
					'\0' };
			return chooseLetterExcluding(exclusion);
		}
		case 't': {
			char exclusion[] = { 'b', 'c', 'd', 'f', 'g', 'j', 'k', 'l', 'm',
					'n', 'p', 'q', 't', 'v', 'x', 'y', 'z', '\0' };
			return chooseLetterExcluding(exclusion);
		}
		case 'u': {
			char exclusion[] = { 'a', 'b', 'd', 'e', 'h', 'j', 'i', 'm', 'o', 'r',
					'u', 'v', 'x', 'y', 'z', '\0' };
			return chooseLetterExcluding(exclusion);
		}
		case 'v': {
			char exclusion[] = { 'b', 'c', 'd', 'f', 'g', 'h', 'j', 'k',
					'l', 'm', 'n', 'p', 'q', 'r', 's', 't', 'v', 'w',
					'x', 'z', '\0' };
			return chooseLetterExcluding(exclusion);
		}
		case 'w': {
			char exclusion[] = { 'b', 'c', 'd', 'f', 'g', 'j', 'k', 'l', 'm',
					'n', 'p', 'q', 's', 't', 'v', 'w', 'x', 'z', '\0' };
			return chooseLetterExcluding(exclusion);
		}
		case 'x': {
			char exclusion[] = { 'b', 'c', 'd', 'f', 'g', 'h', 'j', 'k',
					'l', 'm', 'n', 'p', 'q', 'r', 's', 't', 'v', 'w',
					'x', 'y', 'z', '\0' };
			return chooseLetterExcluding(exclusion);
		}
		case 'y': {
			char exclusion[] = { 'b', 'c', 'd', 'f', 'g', 'h', 'j', 'k', 'l',
					'm', 'n', 'p', 'q', 'r', 's', 't', 'v', 'w', 'x', 'y', 'z',
					'\0' };
			return chooseLetterExcluding(exclusion);
		}
		case 'z': {
			char exclusion[] = { 'b', 'c', 'd', 'f', 'g', 'h', 'j', 'k', 'l',
					'm', 'n', 'p', 'q', 'r', 's', 't', 'v', 'w', 'x', 'y', 'z',
					'\0' };
			return chooseLetterExcluding(exclusion);
		}
		default:
			return 97 + System::random(25);
		}
	}
}

inline bool NameManager::isVowel(const char inChar) {
	if (inChar == 'a' || inChar == 'e' || inChar == 'i' || inChar == 'o'
		|| inChar == 'u' || inChar == 'y')
		return true;
	else
		return false;
}

char NameManager::chooseLetterExcluding(const char exclude[]) {
	char x = 97 + System::random(25);

	for (int i = 0; i < 25 && exclude[i] != '\0'; i++) {
		if (x == exclude[i]) {
			x = 97 + System::random(25);

			i = -1;
		}
	}

	return x;
}

inline int NameManager::addPrefix(char* name) {
	int x = 1 + System::random(4);

	switch (x) {
	case 1:
		name[0] = 'c';
		name[1] = 'a';
		name[2] = 'r';
		name[3] = 'b';
		return 4;
	case 2:
		name[0] = 'd';
		name[1] = 'u';
		name[2] = 'r';
		return 3;
	case 3:
		name[0] = 'o';
		name[1] = 'm';
		name[2] = 'n';
		name[3] = 'i';
		return 4;
	case 4:
		name[0] = 'q';
		name[1] = 'u';
		name[2] = 'a';
		name[3] = 'd';
		return 4;
	case 5:
		name[0] = 't';
		name[1] = 'r';
		name[2] = 'i';
		return 3;
	default:
		return 0;
	}
}

inline void NameManager::addSuffix(char* name, int location) {
	int x = 1 + System::random(7);

	switch (x) {
	case 1:
		name[location] = 'i';
		name[location+1] = 'u';
		name[location+2] = 'm';
		name[location+3] = '\0';
		break;
	case 2:
		name[location] = 'i';
		name[location+1] = 'a';
		name[location+2] = 'n';
		name[location+3] = '\0';
		break;
	case 3:
		name[location] = 'i';
		name[location+1] = 's';
		name[location+2] = 'm';
		name[location+3] = '\0';
		break;
	case 4:
		name[location] = 'i';
		name[location+1] = 't';
		name[location+2] = 'e';
		name[location+3] = '\0';
		break;
	case 5:
		name[location] = 's';
		name[location+1] = 'i';
		name[location+2] = 's';
		name[location+3] = '\0';
		break;
	case 6:
		name[location] = 'i';
		name[location+1] = 'n';
		name[location+2] = 'e';
		name[location+3] = '\0';
		break;
	case 7:
		name[location] = 'i';
		name[location+1] = 'c';
		name[location+2] = '\0';
		break;
	case 8:
		name[location] = 'i';
		name[location+1] = 'd';
		name[location+2] = 'e';
		name[location+3] = '\0';
		break;
	default:
		break;
	}
}

