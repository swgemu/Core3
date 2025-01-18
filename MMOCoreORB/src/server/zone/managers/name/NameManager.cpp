/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions. */


#include "NameManager.h"
#include "engine/lua/Lua.h"
#include <regex>

#include "server/zone/ZoneProcessServer.h"
#include "server/zone/objects/creature/CreatureObject.h"

//#define DEBUG_NAMING
//#define DEBUG_NAMING_VERBOSE

NameManager::NameManager() {
	setLoggingName("NameManager");

	initialize();

	setLogging(false);
}

NameManager::NameManager(ZoneProcessServer* serv) : Logger("NameManager") {
	server = serv;

	initialize();

	setLogging(false);
}

NameManager::~NameManager() {
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

	regexFilters.removeAll();
}

void NameManager::initialize() {
	loadConfigData();
}

void NameManager::loadConfigData(bool reload) {
	Lua* lua = new Lua();
	lua->init();

	if (!lua->runFile("scripts/managers/name/name_manager.lua")) {
		error("Unable to load NameManager data.");
		delete lua;
		return;
	}

	if (reload) {
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

		stormtrooperPrefixes.removeAll();
		scouttrooperPrefixes.removeAll();
		darktrooperPrefixes.removeAll();
		swamptrooperPrefixes.removeAll();
		regexFilters.removeAll();
	}

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

	luaObject = lua->getGlobalObject("stormtrooperPrefixes");
	for (int i = 1; i <= luaObject.getTableSize(); ++i)
		stormtrooperPrefixes.add(luaObject.getStringAt(i));

	luaObject.pop();

	luaObject = lua->getGlobalObject("scouttrooperPrefixes");
	for (int i = 1; i <= luaObject.getTableSize(); ++i)
		scouttrooperPrefixes.add(luaObject.getStringAt(i));

	luaObject.pop();

	luaObject = lua->getGlobalObject("darktrooperPrefixes");
	for (int i = 1; i <= luaObject.getTableSize(); ++i)
		darktrooperPrefixes.add(luaObject.getStringAt(i));

	luaObject.pop();

	luaObject = lua->getGlobalObject("swamptrooperPrefixes");
	for (int i = 1; i <= luaObject.getTableSize(); ++i)
		swamptrooperPrefixes.add(luaObject.getStringAt(i));

	luaObject.pop();

	auto filterTable = ConfigManager::instance()->getString("Core3.NameManager.FilterTable", "oldFilterWords");

	luaObject = lua->getGlobalObject(filterTable);

#ifdef DEBUG_NAMING
	info(true) << "Loading filter words for Name Manager:";
#endif

	if (luaObject.isValidTable()) {
		for(int i = 1; i <= luaObject.getTableSize(); ++i) {
			LuaObject entry = luaObject.getObjectAt(i);

			const String regexString = entry.getStringAt(1);
			int reason = entry.getIntAt(2);

#ifdef DEBUG_NAMING
			info(true) << "Loading Entry #" << i << " Regex Entry: " << regexString;
#endif

			Reference<RegexData*> regexCheck = new RegexData(regexString, reason);

			regexFilters.add(regexCheck);

			entry.pop();
		}
	}

	info(true) << "Loaded " << regexFilters.size() << " regex filter patterns.";

	luaObject.pop();

	delete lua;
	lua = nullptr;
}

bool NameManager::isProfane(const String& name) const {
	return checkNamingFilter(name, NameManagerResult::DECLINED_PROFANE) != NameManagerResult::ACCEPTED;
}

bool NameManager::isDeveloper(const String& name) const {
	return checkNamingFilter(name, NameManagerResult::DECLINED_DEVELOPER) != NameManagerResult::ACCEPTED;
}

bool NameManager::isFiction(const String& name) const {
	return checkNamingFilter(name, NameManagerResult::DECLINED_FICT_RESERVED) != NameManagerResult::ACCEPTED;
}

bool NameManager::isReserved(const String& name) const {
	return checkNamingFilter(name, NameManagerResult::DECLINED_RESERVED) != NameManagerResult::ACCEPTED;
}

int NameManager::checkNamingFilter(const String& name, int resultType) const {
#ifdef DEBUG_NAMING
	StringBuffer debugMsg;
	debugMsg << "checkNamingFilter -- Checking: " << name << " for Type: " << resultType << "\n";
#endif

	int result = NameManagerResult::ACCEPTED;

	for (int i = 0; i < regexFilters.size(); i++) {
		Reference<RegexData*> regexData = regexFilters.get(i);

		if (regexData == nullptr)
			continue;

#ifdef DEBUG_NAMING
		const String regexPhrase = regexData->getRegexPhrase();
#endif

		const std::regex* regexCheck = regexData->getRegexEntry();
		const int reservedReason = regexData->getFilterType();

#ifdef DEBUG_NAMING_VEBOSE
		debugMsg << "Using Regex Entry: " << regexData->getRegexPhrase() << " with Reserved Reason: " << reservedReason << "\n";
#endif

		if (resultType > 0 && resultType != reservedReason) {
#ifdef DEBUG_NAMING_VEBOSE
			debugMsg << "Skipping Entry: " << regexData->getRegexPhrase() << "\n";

			info(true) << debugMsg.toString();
#endif
			continue;
		}

		if (std::regex_search(name.toCharArray(), *regexCheck)) {
#ifdef DEBUG_NAMING
			debugMsg << "Name: " << name << " failed check against regex " << regexPhrase << " , reason: " << reservedReason << "\n";
#endif

			result = reservedReason;
			break;
		}
	}

#ifdef DEBUG_NAMING
	if (result == NameManagerResult::ACCEPTED)
		debugMsg << "Name: " << name << " passed regex checks and NameManagerResult::ACCEPTED";

	info(true) << debugMsg.toString();
#endif

	return result;
}

int NameManager::validateName(const CreatureObject* obj) const {
	const StringId* objectName = obj->getObjectName();
	UnicodeString name = obj->getCustomObjectName();
	int species = obj->getSpecies();

	return validateName(name.toString(), species);
}

const NameData* NameManager::getSpeciesData(int species) const {
	switch (species) {
	case CreatureObject::HUMAN: return humanData;
	case CreatureObject::RODIAN: return rodianData;
	case CreatureObject::TRANDOSHAN: return trandoshanData;
	case CreatureObject::MONCAL: return monCalData;
	case CreatureObject::WOOKIEE: return wookieeData;
	case CreatureObject::BOTHAN: return bothanData;
	case CreatureObject::TWILEK: return twilekData;
	case CreatureObject::ZABRAK: return zabrakData;
	case CreatureObject::ITHORIAN: return ithorianData;
	case CreatureObject::SULLUSTAN: return sullustanData;
	default: return humanData;
	}
}

int NameManager::validateName(const String& name, int species) const {
	auto data = getSpeciesData(species);
	auto firstNameRules = data->getFirstNameRules();
	auto lastNameRules = data->getLastNameRules();

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

	return checkNamingFilter(name);
}

int NameManager::validateGuildName(const String& name, int type) const {
	if (name.isEmpty())
		return NameManagerResult::DECLINED_EMPTY;

	if ((type == NameManagerType::GUILD_NAME || type == NameManagerType::GUILD_TITLE) && name.length() > 25)
		return NameManagerResult::DECLINED_GUILD_LENGTH;

	if (type == NameManagerType::GUILD_ABBREV && name.length() > 5)
		return NameManagerResult::DECLINED_GUILD_LENGTH;

	// Guilds allowed multiple spaces
	if (strspn(name.toCharArray(), "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz'- ") != name.length())
		return NameManagerResult::DECLINED_SYNTAX;

	// Multiple consecutive spaces not allowed
	if (name.indexOf("  ") != -1)
		return NameManagerResult::DECLINED_SYNTAX;

	if (name.contains("\\") || name.contains("\n") || name.contains("\r") || name.contains("#"))
		return NameManagerResult::DECLINED_SYNTAX;

	return checkNamingFilter(name);
}

int NameManager::validateCityName(const String& name) const {
	if (name.isEmpty())
		return NameManagerResult::DECLINED_EMPTY;

	if (name.length() > 40)
		return NameManagerResult::DECLINED_SYNTAX;

	// Cities allowed multiple spaces
	if (strspn(name.toCharArray(), "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz'- ") != name.length())
		return NameManagerResult::DECLINED_SYNTAX;

	// Multiple consecutive spaces not allowed
	if (name.indexOf("  ") != -1)
		return NameManagerResult::DECLINED_SYNTAX;

	return checkNamingFilter(name);
}

int NameManager::validateVendorName(const String& name) const {
	if (name.isEmpty())
		return NameManagerResult::DECLINED_EMPTY;

	if (name.length() > 40)
		return NameManagerResult::DECLINED_SYNTAX;

	// Vendors allowed to have spaces
	if (strspn(name.toCharArray(), "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz'- ") != name.length())
		return NameManagerResult::DECLINED_SYNTAX;

	// Multiple consecutive spaces not allowed
	if (name.indexOf("  ") != -1)
		return NameManagerResult::DECLINED_SYNTAX;

	return checkNamingFilter(name);
}

int NameManager::validateChatRoomName(const String& name) const {
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

int NameManager::validateShipName(const String& name) const {
	if (name.isEmpty())
		return NameManagerResult::DECLINED_EMPTY;

	if (isProfane(name))
		return NameManagerResult::DECLINED_PROFANE;
	if (isDeveloper(name))
		return NameManagerResult::DECLINED_DEVELOPER;
	if (isFiction(name))
		return NameManagerResult::DECLINED_FICT_RESERVED;

	int digitCount = 0;

	// Char digits here
	for (char c : name) {
		if (isdigit(c)) {
			digitCount++;
		} else {
			digitCount = 0;
		}

		 if (digitCount > 3) {
			return NameManagerResult::DECLINED_FICT_RESERVED;
		 }
	}

	return NameManagerResult::ACCEPTED;
}

const String NameManager::makeCreatureName(int type, int species) const {
	String name;
	auto data = getSpeciesData(species);

	// Generated imperial trooper names do not need to be checked. Covers all Imperial Trooper types
	if (type >= NameManagerType::STORMTROOPER && type <= NameManagerType::SWAMPTROOPER) {
		name = makeImperialTrooperName(type);
	// R-Droid names do not need to be checked
	} else if (type >= NameManagerType::R2 && type <= NameManagerType::DROID_RA7) {
		name = makeDroidName(type);
	} else {
		uint32 count = 0;
		int result = NameManagerResult::DECLINED_EMPTY;

		// Fail loop when result is accepted
		while (result != NameManagerResult::ACCEPTED) {
			name = generateRandomName(data);

			result = validateName(name, species);

			count++;

			if (count >= 10) {
				error() << " Failed to create suitable creature name -- Count: " << count << " Species: " <<  species << " Ending Name: " << name;
				break;
			}
		}
	}

	return name;
}

String NameManager::makeImperialTrooperName(int type) const {
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

String NameManager::makeDroidName(int type) const {
	const static char alphabet[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
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

String NameManager::generateResourceName(const String& randomNameClass) const {
	const NameData* data;

	if (randomNameClass == "energy_resource")
		data = energyResourceData;
	else if (randomNameClass == "mineral_resource")
		data = mineralResourceData;
	else if (randomNameClass == "reactive_gas_resource")
		data = reactiveGasResourceData;
	else
		data = plainResourceData;

	String name;
	uint32 count = 0;
	int result = NameManagerResult::DECLINED_EMPTY;

	while (name.isEmpty() || isProfane(name)) {
		name = generateRandomName(data);

		count++;

		if (count >= 10) {
			error() << " Failed to create suitable resource name -- Count: " << count << " Final Name: " << name;
			break;
		}
	}

	return name;
}

String NameManager::generateRandomName(const NameData* nameData) const {
	String result = "";
	auto lastNameRules = nameData->getLastNameRules();

	result += generateSingleName(nameData, nameData->getFirstNameRules());

	int lastNameChance = lastNameRules->getNameChance();

	if (System::random(100) < lastNameChance)
		result = result + " " + generateSingleName(nameData, lastNameRules);

	return capitalizeName(result);
}

String NameManager::generateUniqueName(const NameData* nameData, const NameRules* rules) const {
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

String NameManager::capitalizeName(const String& name) const {
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

String NameManager::generateSingleName(const NameData* nameData, const NameRules* rules) const {
	if (System::random(100) < rules->getUniqueChance())
		return generateUniqueName(nameData, rules);
	else
		return generateRandomizedName(nameData, rules);
}

String NameManager::generateRandomizedName(const NameData* nameData, const NameRules* rules) const {
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

String NameManager::appendSyllable(const String& left, const String& right, const NameData* data) const {
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

int NameManager::getFragmentType(const String& frag, const NameData* data) const {
	if (data->beginningConsonantContains(frag) || data->middeConsonantContains(frag)|| data->endingConsonantContains(frag))
		return NameManagerType::FRAG_CONSONANT;
	else if (data->vowelsContains(frag))
		return NameManagerType::FRAG_VOWEL;
	else if (data->specialSyllablesContains(frag))
		return NameManagerType::FRAG_SPECIAL;

	return NameManagerType::FRAG_MIXED;
}
