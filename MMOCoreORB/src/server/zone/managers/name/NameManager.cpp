/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions. */


#include "NameManager.h"

#include "server/zone/ZoneProcessServer.h"
#include "server/zone/objects/creature/CreatureObject.h"

NameManager::NameManager() {
	setLoggingName("NameManager");

	initialize();

	profaneNames = new Vector<String>(55, 5); //based on the original number of banned words
	developerNames = new BannedNameSet();
	reservedNames = new BannedNameSet();
	fictionNames = new BannedNameSet();

	fillNames();

	setLogging(false);
}

NameManager::NameManager(ZoneProcessServer* serv) : Logger("NameManager") {
	server = serv;

	initialize();

	profaneNames = new Vector<String>(55, 5); //based on the original number of banned words
	developerNames = new BannedNameSet();
	reservedNames = new BannedNameSet();
	fictionNames = new BannedNameSet();

	fillNames();

	setLogging(false);

}

NameManager::~NameManager() {
	delete lua;

	delete(profaneNames);
	delete(developerNames);
	delete(reservedNames);
	delete(fictionNames);

	delete bothanData;
	delete humanData;
	delete ithorianData;
	delete monCalData;
	delete rodianData;
	delete sullustanData;
	delete trandoshanData;
	delete twilekData;
	delete wookieeData;
	delete zabrakData;

	delete energyResourceData;
	delete mineralResourceData;
	delete plainResourceData;
	delete reactiveGasResourceData;
}

void NameManager::initialize() {
	lua = new Lua();
	lua->init();

	info("loading configuration");
	if(!loadConfigData()) {

		loadDefaultConfig();

		error("Configuration error(s), using defaults");
	}

	info("initialized");

}

bool NameManager::loadConfigFile() {
	return lua->runFile("scripts/managers/name/name_manager.lua");
}

bool NameManager::loadConfigData() {
	if (!loadConfigFile())
		return false;

	LuaObject luaObject = lua->getGlobalObject("nameManagerBothan");
	bothanData = new NameData();
	bothanData->readObject(&luaObject);
	luaObject.pop();

	luaObject = lua->getGlobalObject("nameManagerHuman");
	humanData = new NameData();
	humanData->readObject(&luaObject);
	luaObject.pop();

	luaObject = lua->getGlobalObject("nameManagerIthorian");
	ithorianData = new NameData();
	ithorianData->readObject(&luaObject);
	luaObject.pop();

	luaObject = lua->getGlobalObject("nameManagerMonCal");
	monCalData = new NameData();
	monCalData->readObject(&luaObject);
	luaObject.pop();

	luaObject = lua->getGlobalObject("nameManagerRodian");
	rodianData = new NameData();
	rodianData->readObject(&luaObject);
	luaObject.pop();

	luaObject = lua->getGlobalObject("nameManagerSullustan");
	sullustanData = new NameData();
	sullustanData->readObject(&luaObject);
	luaObject.pop();

	luaObject = lua->getGlobalObject("nameManagerTrandoshan");
	trandoshanData = new NameData();
	trandoshanData->readObject(&luaObject);
	luaObject.pop();

	luaObject = lua->getGlobalObject("nameManagerTwilek");
	twilekData = new NameData();
	twilekData->readObject(&luaObject);
	luaObject.pop();

	luaObject = lua->getGlobalObject("nameManagerWookiee");
	wookieeData = new NameData();
	wookieeData->readObject(&luaObject);
	luaObject.pop();

	luaObject = lua->getGlobalObject("nameManagerZabrak");
	zabrakData = new NameData();
	zabrakData->readObject(&luaObject);
	luaObject.pop();

	luaObject = lua->getGlobalObject("nameManagerEnergyResource");
	energyResourceData = new NameData();
	energyResourceData->readObject(&luaObject);
	luaObject.pop();

	luaObject = lua->getGlobalObject("nameManagerMineralResource");
	mineralResourceData = new NameData();
	mineralResourceData->readObject(&luaObject);
	luaObject.pop();

	luaObject = lua->getGlobalObject("nameManagerPlainResource");
	plainResourceData = new NameData();
	plainResourceData->readObject(&luaObject);
	luaObject.pop();

	luaObject = lua->getGlobalObject("nameManagerReactiveGasResource");
	reactiveGasResourceData = new NameData();
	reactiveGasResourceData->readObject(&luaObject);
	luaObject.pop();

	LuaObject stormtrooperPrefixesObject = lua->getGlobalObject("stormtrooperPrefixes");
	for (int i = 1; i <= stormtrooperPrefixesObject.getTableSize(); ++i)
		stormtrooperPrefixes.add(stormtrooperPrefixesObject.getStringAt(i));

	stormtrooperPrefixesObject.pop();

	LuaObject scouttrooperPrefixesObject = lua->getGlobalObject("scouttrooperPrefixes");
	for (int i = 1; i <= scouttrooperPrefixesObject.getTableSize(); ++i)
		scouttrooperPrefixes.add(scouttrooperPrefixesObject.getStringAt(i));

	scouttrooperPrefixesObject.pop();

	LuaObject darktrooperPrefixesObject = lua->getGlobalObject("darktrooperPrefixes");
	for (int i = 1; i <= darktrooperPrefixesObject.getTableSize(); ++i)
		darktrooperPrefixes.add(darktrooperPrefixesObject.getStringAt(i));

	darktrooperPrefixesObject.pop();

	LuaObject swamptrooperPrefixesObject = lua->getGlobalObject("swamptrooperPrefixes");
	for (int i = 1; i <= swamptrooperPrefixesObject.getTableSize(); ++i)
		swamptrooperPrefixes.add(swamptrooperPrefixesObject.getStringAt(i));

	swamptrooperPrefixesObject.pop();

	//test();

	return true;
}

void NameManager::loadDefaultConfig() {


}

void NameManager::fillNames() {
	File* restrictedFile = new File("conf/restrictednames.lst");

	try {
		FileReader restrictedReader(restrictedFile);

		info("parsing restricted names list: restrictednames.lst", true);

		BannedNameSet* setp = NULL;

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

		restrictedReader.close();

	} catch (FileNotFoundException&e ) {
	}

	delete restrictedFile;
}


bool NameManager::isProfane(String name) {
	uint16 i;

	name = name.toLowerCase();

	for (i = 0; i < profaneNames->size(); i++) {
		if (name.indexOf(profaneNames->get(i)) != -1)
			return true;
	}

	return false;
}

inline bool NameManager::isDeveloper(String name) {
	name = name.toLowerCase();

	HashSetIterator<String> iter = developerNames->iterator();
	while (iter.hasNext()) {
		if (name.indexOf(iter.next()) != -1)
			return true;
	}

	return false;
}

inline bool NameManager::isFiction(String name) {
	name = name.toLowerCase();

	HashSetIterator<String> iter = fictionNames->iterator();
	while (iter.hasNext()) {
		if (name.indexOf(iter.next()) != -1)
			return true;
	}

	return false;
}

inline bool NameManager::isReserved(String name) {
	name = name.toLowerCase();

	HashSetIterator<String> iter = reservedNames->iterator();
	while (iter.hasNext()) {
		if (name.indexOf(iter.next()) != -1)
			return true;
	}

	return false;
}

int NameManager::validateName(CreatureObject* obj) {
	StringId* objectName = obj->getObjectName();
	UnicodeString name = obj->getCustomObjectName();
	int species = obj->getSpecies();

	return validateName(name.toString(), species);
}

NameData* NameManager::getSpeciesData(int species) {
	switch (species) {
	case CreatureObject::HUMAN: return humanData;
	case CreatureObject::RODIAN: return rodianData;
	case CreatureObject::TRANDOSHAN: return trandoshanData;
	case CreatureObject::MONCAL: return monCalData;
	case CreatureObject::WOOKIE: return wookieeData;
	case CreatureObject::BOTHAN: return bothanData;
	case CreatureObject::TWILEK: return twilekData;
	case CreatureObject::ZABRAK: return zabrakData;
	case CreatureObject::ITHORIAN: return ithorianData;
	case CreatureObject::SULLUSTAN: return sullustanData;
	default: return humanData;
	}
}

int NameManager::validateName(const String& name, int species) {
	NameData* data = getSpeciesData(species);
	NameRules* firstNameRules = data->getFirstNameRules();
	NameRules* lastNameRules = data->getLastNameRules();

	if (name.isEmpty())
		return NameManagerResult::DECLINED_EMPTY;

	int fullMaxLength = firstNameRules->getMaxChars() + lastNameRules->getMaxChars() + 1;

	if (name.length() > fullMaxLength)
		return NameManagerResult::DECLINED_RACE_INAPP;

	String firstName, lastName;

	//Split the name into first and last
	int spc = name.indexOf(" ");
	if (spc != -1) {
		firstName = name.subString(0, spc);
		lastName = name.subString(spc + 1, name.length());
	} else {
		firstName = name;
		lastName = "";
	}

	if (isProfane(name))
		return NameManagerResult::DECLINED_PROFANE;

	if (isDeveloper(name))
		return NameManagerResult::DECLINED_DEVELOPER;

	if (isFiction(name))
		return NameManagerResult::DECLINED_FICT_RESERVED;

	if (isReserved(name) || isReserved(firstName) )
		return NameManagerResult::DECLINED_RESERVED;

	if (firstName.length() < firstNameRules->getMinChars() || firstName.length() > firstNameRules->getMaxChars())
		return NameManagerResult::DECLINED_RACE_INAPP;

	// This will handle species not allowed surnames (Wookiees) if the rules have min/max set to 0
	if (lastName != "" && (lastName.length() < lastNameRules->getMinChars() || lastName.length() > lastNameRules->getMaxChars()))
		return NameManagerResult::DECLINED_RACE_INAPP;

	// Iterates through the name, looking for non alphabetic characters and comparing it to the allowed
	// special characters in the rules, also counting total characters and comparing to the max
	int specialCount = 0;
	for (int i = 0; i < firstName.length(); i++) {
		String singleChar = firstName.subString(i, i + 1);
		if (isalpha(firstName.charAt(i)) == 0) {
			if (!firstNameRules->getSpecialChars().contains(singleChar))
				return NameManagerResult::DECLINED_RACE_INAPP;
			else
				specialCount++;
		}
	}

	if (specialCount > firstNameRules->getMaxSpecialChars())
		return NameManagerResult::DECLINED_RACE_INAPP;

	if (lastName != "") {
		specialCount = 0;
		for (int i = 0; i < lastName.length(); i++) {
			String singleChar = lastName.subString(i, i + 1);
			if (isalpha(lastName.charAt(i)) == 0) {
				if (!lastNameRules->getSpecialChars().contains(singleChar))
					return NameManagerResult::DECLINED_RACE_INAPP;
				else
					specialCount++;
			}
		}

		if (specialCount > lastNameRules->getMaxSpecialChars())
			return NameManagerResult::DECLINED_RACE_INAPP;
	}

	return NameManagerResult::ACCEPTED;
}

int NameManager::validateGuildName(const String& name, int type) {
	if (name.isEmpty())
		return NameManagerResult::DECLINED_EMPTY;

	if ((type == NameManagerType::GUILD_NAME || type == NameManagerType::GUILD_TITLE) && name.length() > 25)
		return NameManagerResult::DECLINED_GUILD_LENGTH;

	if (type == NameManagerType::GUILD_ABBREV && name.length() > 5)
		return NameManagerResult::DECLINED_GUILD_LENGTH;

	if (isProfane(name))
		return NameManagerResult::DECLINED_PROFANE;

	if (isDeveloper(name))
		return NameManagerResult::DECLINED_DEVELOPER;

	if (isFiction(name))
		return NameManagerResult::DECLINED_FICT_RESERVED;

	if (isReserved(name))
		return NameManagerResult::DECLINED_RESERVED;

	// Guilds allowed multiple spaces
	if (strspn(name.toCharArray(), "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz'- ") != name.length())
		return NameManagerResult::DECLINED_SYNTAX;

	// Multiple consecutive spaces not allowed
	if (name.indexOf("  ") != -1)
		return NameManagerResult::DECLINED_SYNTAX;

	if (name.contains("\\") || name.contains("\n") || name.contains("\r") || name.contains("#"))
		return NameManagerResult::DECLINED_SYNTAX;

	return NameManagerResult::ACCEPTED;
}

int NameManager::validateCityName(const String& name) {
	if (name.isEmpty())
		return NameManagerResult::DECLINED_EMPTY;

	if (name.length() > 40)
		return NameManagerResult::DECLINED_SYNTAX;

	if (isProfane(name))
		return NameManagerResult::DECLINED_PROFANE;

	if (isDeveloper(name))
		return NameManagerResult::DECLINED_DEVELOPER;

	if (isFiction(name))
		return NameManagerResult::DECLINED_FICT_RESERVED;

	if (isReserved(name))
		return NameManagerResult::DECLINED_RESERVED;

	// Cities allowed multiple spaces
	if (strspn(name.toCharArray(), "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz'- ") != name.length())
		return NameManagerResult::DECLINED_SYNTAX;

	// Multiple consecutive spaces not allowed
	if (name.indexOf("  ") != -1)
		return NameManagerResult::DECLINED_SYNTAX;

	return NameManagerResult::ACCEPTED;
}

int NameManager::validateVendorName(const String& name) {
	if (name.isEmpty())
		return NameManagerResult::DECLINED_EMPTY;

	if (name.length() > 40)
		return NameManagerResult::DECLINED_SYNTAX;

	if (isProfane(name))
		return NameManagerResult::DECLINED_PROFANE;

	if (isDeveloper(name))
		return NameManagerResult::DECLINED_DEVELOPER;

	if (isFiction(name))
		return NameManagerResult::DECLINED_FICT_RESERVED;

	if (isReserved(name))
		return NameManagerResult::DECLINED_RESERVED;

	// Vendors allowed to have spaces
	if (strspn(name.toCharArray(), "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz'- ") != name.length())
		return NameManagerResult::DECLINED_SYNTAX;

	// Multiple consecutive spaces not allowed
	if (name.indexOf("  ") != -1)
		return NameManagerResult::DECLINED_SYNTAX;

	return NameManagerResult::ACCEPTED;
}

int NameManager::validateChatRoomName(const String& name) {
	if (name.isEmpty())
		return NameManagerResult::DECLINED_EMPTY;

	if (isProfane(name))
		return NameManagerResult::DECLINED_PROFANE;

	//Chat rooms can only have letters and numbers in the name, no special characters or spaces.
	if (strspn(name.toCharArray(), "1234567890ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz") != name.length())
		return NameManagerResult::DECLINED_SYNTAX;

	uint32 hash = name.hashCode();

	//The following are special names in the game client and should not be used by players.
	if (hash == STRING_HASHCODE("Planet") || hash == STRING_HASHCODE("Quest"))
		return NameManagerResult::DECLINED_RESERVED;

	if (hash == STRING_HASHCODE("system") || hash == STRING_HASHCODE("named"))
		return NameManagerResult::DECLINED_RESERVED;

	if (hash == STRING_HASHCODE("GuildChat") || hash == STRING_HASHCODE("GroupChat"))
		return NameManagerResult::DECLINED_RESERVED;

	if (hash == STRING_HASHCODE("Auction") || hash == STRING_HASHCODE("Combat"))
		return NameManagerResult::DECLINED_RESERVED;

	return NameManagerResult::ACCEPTED;
}

const String NameManager::makeCreatureName(int type, int species) {
	String name;
	NameData* data = getSpeciesData(species);

	// Covers all Imperial Trooper types
	if (type >= NameManagerType::STORMTROOPER && type <= NameManagerType::SWAMPTROOPER) {
		name = makeImperialTrooperName(type);
	} else if (type >= NameManagerType::R2 && type <= NameManagerType::DROID_RA7) {
		name = makeDroidName(type);
	} else {
		name = generateRandomName(data);
	}

	return name;
}

String NameManager::makeImperialTrooperName(int type) {
	String name;

	if (type == NameManagerType::STORMTROOPER)
		name += stormtrooperPrefixes.get(System::random(stormtrooperPrefixes.size() - 1));
	else if (type == NameManagerType::SCOUTTROOPER)
		name += scouttrooperPrefixes.get(System::random(scouttrooperPrefixes.size() - 1));
	else if (type == NameManagerType::DARKTROOPER)
		name += darktrooperPrefixes.get(System::random(darktrooperPrefixes.size() - 1));
	else if (type == NameManagerType::SWAMPTROOPER)
		name += swamptrooperPrefixes.get(System::random(swamptrooperPrefixes.size() - 1));

	name += "-";
	name += String::valueOf(1 + System::random(898));

	return name;
}

String NameManager::makeDroidName(int type) {
	char alphabet[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	String name = "";

	if (type >= NameManagerType::R2 && type <= NameManagerType::R5) {
		name = "R" + String::valueOf(type) + "-";
		name += alphabet[System::random(25)];
		name += String::valueOf(System::random(9));
	} else if (type == NameManagerType::DROID_3P0) {
		name += alphabet[System::random(25)];
		name += String::valueOf(System::random(9)) + "-P0";
	} else if (type == NameManagerType::DROID_EG6) {
		name = "E";
		name += alphabet[System::random(25)];
		name += "-" + String::valueOf(System::random(9));
	} else if (type == NameManagerType::DROID_WED) {
		name = "WED-";
		name += alphabet[System::random(25)];
		name += String::valueOf(System::random(9));
	} else if (type == NameManagerType::DROID_LE) {
		name = "LE-";
		name += alphabet[System::random(25)];
		name += alphabet[System::random(25)];
		name += String::valueOf(System::random(9));
	} else if (type == NameManagerType::DROID_RA7) {
		name = "RA7-";
		name += alphabet[System::random(25)];
		name += String::valueOf(System::random(9));
	}

	return name;
}

void NameManager::test() {
	uint64 start = Time::currentNanoTime();

	int iterations = 1000000;

	for(int i = 0;i < iterations; ++i)
		//System::out << makeCreatureName(true) << endl;
		makeCreatureName(1);

	uint64 end = Time::currentNanoTime();

	float nano = (end - start);
	float milli = nano * .000001;
	float seconds = milli / 1000;
	System::out << "Old name generator:" << endl;
	System::out << "Average: " << nano / iterations  << " nanoseconds / " << milli / iterations << " milliseconds" << seconds / iterations  << " seconds" << endl;
	System::out << "Total: " << nano << " nanoseconds / " << milli << " milliseconds" << seconds << " seconds" << endl;

	start = Time::currentNanoTime();

	for(int i = 0;i < iterations; ++i)
		generateResourceName("plain_resource");

	end = Time::currentNanoTime();

	nano = (end - start);
	milli = nano * .000001;
	seconds = milli / 1000;
	System::out << "New name generator:" << endl;
	System::out << "Average: " << nano / iterations  << " nanoseconds / " << milli / iterations << " milliseconds" << seconds / iterations  << " seconds" << endl;
	System::out << "Total: " << nano << " nanoseconds / " << milli << " milliseconds" << seconds << " seconds" << endl;
}

String NameManager::generateResourceName(const String& randomNameClass) {
	NameData* data;

	if (randomNameClass == "energy_resource")
		data = energyResourceData;
	else if (randomNameClass == "mineral_resource")
		data = mineralResourceData;
	else if (randomNameClass == "reactive_gas_resource")
		data = reactiveGasResourceData;
	else
		data = plainResourceData;

	return generateRandomName(data);
}

String NameManager::generateRandomName(NameData* nameData) {
	String result = "";
	NameRules* lastNameRules = nameData->getLastNameRules();

	result += generateSingleName(nameData, nameData->getFirstNameRules());

	int lastNameChance = lastNameRules->getNameChance();

	if (System::random(100) < lastNameChance)
		result = result + " " + generateSingleName(nameData, lastNameRules);

	return capitalizeName(result);
}

String NameManager::generateUniqueName(NameData* nameData, NameRules* rules) {
	String pattern = nameData->getRandomUniquePattern();
	String result = "";
	Vector<String> usedRoots;

	for (int i = 0; i < pattern.length(); i++) {
		String patType = pattern.subString(i, i + 1);

		if (patType == "*") {
			result = appendSyllable(result, generateRandomizedName(nameData, rules), nameData);
		} else {
			for (;;) {
				String root = "";
				String unique = nameData->getRandomUnique(patType, root);

				if (root != "" && usedRoots.contains(root))
					continue;

				result += unique;

				if (root != "")
					usedRoots.add(root);

				break;
			}
		}
	}

	return result;
}

String NameManager::capitalizeName(String& name) {
	String result = "";
	bool capNext = true;
	for (int i = 0; i < name.length(); ++i) {
		if (capNext)
			result += name.subString(i, i + 1).toUpperCase();
		else
			result += name.subString(i, i + 1);

		if (name.subString(i, i + 1) == " ")
			capNext = true;
		else if (name.subString(i, i + 1) == "'" || name.subString(i, i + 1) == "-")
			// Letter after a ' or - is not always capitalized
			capNext = System::random(100) > 50;
		else
			capNext = false;
	}

	return result;
}

String NameManager::generateSingleName(NameData* nameData, NameRules* rules) {
	if (System::random(100) < rules->getUniqueChance())
		return generateUniqueName(nameData, rules);
	else
		return generateRandomizedName(nameData, rules);
}

String NameManager::generateRandomizedName(NameData* nameData, NameRules* rules) {

	int syllables = rules->getMinSyllables();

	for (;;) {
		while (syllables < rules->getMaxSyllables()) {
			float syllableChance = 0.6f - (syllables / (rules->getMaxSyllables() * 2.0f));
			if (System::random(100) > syllableChance * 100)
				break;

			++syllables;
		}

		bool nextSyllableIsFirst = true;
		String result = "";
		int specialCharCount = 0;

		Vector<String> selectedSpecialSyllables;

		for (int i = 0; i < syllables; ++i) {
			String oldResult = result;
			bool firstSyllable = nextSyllableIsFirst;
			nextSyllableIsFirst = false;

			bool finalSyllable = (i == (syllables - 1));
			bool appendSpecial = false;

			if (!finalSyllable) {
				if (specialCharCount < rules->getMaxSpecialChars() && System::random(100) < rules->getSpecialCharChance()) {
					appendSpecial = true;
					finalSyllable = true;
					nextSyllableIsFirst = true;
				}
			}

			int specialSyllableChance = rules->getChanceMiddleSpecial();

			if (firstSyllable)
				specialSyllableChance = rules->getChanceBeginsSpecial();
			else if (finalSyllable)
				specialSyllableChance = rules->getChanceEndsSpecial();

			if (System::random(100) < specialSyllableChance && selectedSpecialSyllables.size() < rules->getMaxSpecialSyllables()) {
				for (;;) {
					String specialSyllable = nameData->getRandomSpecialSyllable();
					if (selectedSpecialSyllables.contains(specialSyllable))
						continue;

					result = appendSyllable(result, specialSyllable, nameData);
					selectedSpecialSyllables.add(specialSyllable);
					break;
				}
			} else {
				int syllableSelect = System::random(100);
				String syllable = "";

				if (syllableSelect < 40) {
					if (firstSyllable) {
						syllable += nameData->getRandomBeginningConsonant();
					} else {
						syllable += nameData->getRandomMiddleConsonant();
					}
					syllable += nameData->getRandomVowel();
				} else if (syllableSelect < 80) {
					if (finalSyllable) {
						syllable += nameData->getRandomEndingConsonant();
					} else {
						syllable += nameData->getRandomMiddleConsonant();
					}
					syllable += nameData->getRandomVowel();
				} else {
					syllable += nameData->getRandomVowel();
				}

				result = appendSyllable(result, syllable, nameData);
			}

			if (result == oldResult)
				--i;

			if (appendSpecial && result != "") {
				String randSpecial = rules->getRandomSpecialChar();
				result = appendSyllable(result, randSpecial, nameData);
				++specialCharCount;
			}
		}

		if (result.length() < rules->getMinChars())
			continue;
		else if (result.length() > rules->getMaxChars())
			continue;

		return result;
	}
}

String NameManager::appendSyllable(const String& left, const String& right, NameData* data) {
	if (left == "")
		return right;

	int leftLen = left.length();
	int leftFragType = NameManagerType::FRAG_MIXED;
	int i = leftLen;
	String leftFragment = "";

	while (i > 0) {
		--i;
		String leftFrag = left.subString(i, leftLen);
		int fragType = getFragmentType(leftFrag, data);

		if (fragType == NameManagerType::FRAG_MIXED || fragType == NameManagerType::FRAG_SPECIAL)
			break;

		leftFragment = leftFrag;
		leftFragType = fragType;
	}

	int rightFragType = NameManagerType::FRAG_MIXED;
	String rightFragment = "";

	int r = 0;

	while (r < right.length()) {
		++r;
		String rightFrag = right.subString(0, r);
		int fragType = getFragmentType(rightFrag, data);

		if (fragType == NameManagerType::FRAG_MIXED || fragType == NameManagerType::FRAG_SPECIAL)
			break;

		rightFragment = rightFrag;
		rightFragType = fragType;
	}

	if (rightFragType != leftFragType)
		return left + right;

	if (leftFragment == rightFragment)
		return left;

	if (leftFragType == NameManagerType::FRAG_CONSONANT)
		return left + data->getRandomVowel() + right;
	else
		return left + data->getRandomMiddleConsonant() + right;
}

int NameManager::getFragmentType(const String& frag, NameData* data) {
	if (data->beginningConsonantContains(frag) || data->middeConsonantContains(frag)|| data->endingConsonantContains(frag))
		return NameManagerType::FRAG_CONSONANT;
	else if (data->vowelsContains(frag))
		return NameManagerType::FRAG_VOWEL;
	else if (data->specialSyllablesContains(frag))
		return NameManagerType::FRAG_SPECIAL;

	return NameManagerType::FRAG_MIXED;
}
