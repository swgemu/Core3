#ifndef NAMEDATA_H_
#define NAMEDATA_H_

#include "server/zone/managers/name/NameRules.h"
#include "server/zone/managers/name/NameUnique.h"

class NameData: public Object {
	NameRules* firstNameRules;
	NameRules* lastNameRules;

	VectorMap<String, int> beginningConsonants;
	VectorMap<String, int> middleConsonants;
	VectorMap<String, int> endingConsonants;
	VectorMap<String, int> vowels;
	VectorMap<String, int> specialSyllables;

	Vector<Reference<NameUnique*> > uniques;
	VectorMap<String, int> uniquePatterns;

	int beginningConsonantOdds, middleConsonantOdds, endingConsonantOdds;
	int vowelOdds, specialSyllableOdds, uniquePatternOdds;

public:
	NameData() {
		firstNameRules = NULL;
		lastNameRules = NULL;

		beginningConsonantOdds = 0;
		middleConsonantOdds = 0;
		endingConsonantOdds = 0;
		vowelOdds = 0;
		specialSyllableOdds = 0;
		uniquePatternOdds = 0;

		beginningConsonants.setNoDuplicateInsertPlan();
		beginningConsonants.setNullValue(0);

		middleConsonants.setNoDuplicateInsertPlan();
		middleConsonants.setNullValue(0);

		endingConsonants.setNoDuplicateInsertPlan();
		endingConsonants.setNullValue(0);

		specialSyllables.setNoDuplicateInsertPlan();
		specialSyllables.setNullValue(0);

		vowels.setNoDuplicateInsertPlan();
		vowels.setNullValue(0);

		uniquePatterns.setNoDuplicateInsertPlan();
		uniquePatterns.setNullValue(0);
	}

	~NameData() {
		delete firstNameRules;
		delete lastNameRules;
	}

	NameData(const NameData& data) : Object() {
		firstNameRules = data.firstNameRules;
		lastNameRules = data.lastNameRules;

		beginningConsonants = data.beginningConsonants;
		middleConsonants = data.middleConsonants;
		endingConsonants = data.endingConsonants;
		vowels = data.vowels;
		specialSyllables = data.specialSyllables;

		beginningConsonantOdds = data.beginningConsonantOdds;
		middleConsonantOdds = data.middleConsonantOdds;
		endingConsonantOdds = data.endingConsonantOdds;
		vowelOdds = data.vowelOdds;
		specialSyllableOdds = data.specialSyllableOdds;
		uniquePatternOdds = data.uniquePatternOdds;

		uniquePatterns = data.uniquePatterns;
		uniques = data.uniques;
	}

	NameData& operator=(const NameData& data) {
		if (this == &data)
			return *this;

		firstNameRules = data.firstNameRules;
		lastNameRules = data.lastNameRules;

		beginningConsonants = data.beginningConsonants;
		middleConsonants = data.middleConsonants;
		endingConsonants = data.endingConsonants;
		vowels = data.vowels;
		specialSyllables = data.specialSyllables;

		beginningConsonantOdds = data.beginningConsonantOdds;
		middleConsonantOdds = data.middleConsonantOdds;
		endingConsonantOdds = data.endingConsonantOdds;
		vowelOdds = data.vowelOdds;
		specialSyllableOdds = data.specialSyllableOdds;
		uniquePatternOdds = data.uniquePatternOdds;

		uniquePatterns = data.uniquePatterns;
		uniques = data.uniques;

		return *this;
	}

	void readObject(LuaObject* luaObject) {
		if (!luaObject->isValidTable())
			return;

		LuaObject fName = luaObject->getObjectField("firstNameRules");

		if (!fName.isValidTable()) {
			printf("Error loading name manager first name rule table.\n");
			return;
		}

		firstNameRules = new NameRules();
		firstNameRules->readObject(&fName);

		fName.pop();

		LuaObject lName = luaObject->getObjectField("lastNameRules");

		if (!lName.isValidTable()) {
			printf("Error loading name manager last name rule table.\n");
			return;
		}

		lastNameRules = new NameRules();
		lastNameRules->readObject(&lName);

		lName.pop();

		LuaObject consonantTable = luaObject->getObjectField("consonants");

		if (!consonantTable.isValidTable()) {
			printf("Error loading name manager consonant table.\n");
			return;
		}

		for (int i = 1; i <= consonantTable.getTableSize(); ++i) {
			LuaObject obj = consonantTable.getObjectAt(i);

			if (obj.isValidTable()) {
				String cons = obj.getStringAt(1);
				bool begin = obj.getBooleanAt(2);
				bool mid = obj.getBooleanAt(3);
				bool end = obj.getBooleanAt(4);
				int odds = obj.getIntAt(5);

				if (begin) {
					beginningConsonants.put(cons, odds);
					beginningConsonantOdds += odds;
				}
				if (mid) {
					middleConsonants.put(cons, odds);
					middleConsonantOdds += odds;
				}
				if (end) {
					endingConsonants.put(cons, odds);
					endingConsonantOdds += odds;
				}
			}

			obj.pop();
		}

		consonantTable.pop();

		LuaObject vowelTable = luaObject->getObjectField("vowels");

		if (!vowelTable.isValidTable()) {
			printf("Error loading name manager vowel table.\n");
			return;
		}

		for (int i = 1; i <= vowelTable.getTableSize(); ++i) {
			LuaObject obj = vowelTable.getObjectAt(i);

			if (obj.isValidTable()) {
				String vowel = obj.getStringAt(1);
				int odds = obj.getIntAt(2);

				vowels.put(vowel, odds);
				vowelOdds += odds;
			}

			obj.pop();
		}

		vowelTable.pop();

		LuaObject specialSyllableTable = luaObject->getObjectField("specials");

		if (!specialSyllableTable.isValidTable()) {
			printf("Error loading name manager special syllable table.\n");
			return;
		}

		for (int i = 1; i <= specialSyllableTable.getTableSize(); ++i) {
			LuaObject obj = specialSyllableTable.getObjectAt(i);

			if (obj.isValidTable()) {
				String special = obj.getStringAt(1);
				int odds = obj.getIntAt(2);

				specialSyllables.put(special, odds);
				specialSyllableOdds += odds;
			}

			obj.pop();
		}

		specialSyllableTable.pop();

		LuaObject uniqueTable = luaObject->getObjectField("uniques");

		if (!uniqueTable.isValidTable()) {
			printf("Error loading name manager unique table.\n");
			return;
		}

		for (int i = 1; i <= uniqueTable.getTableSize(); ++i) {
			LuaObject obj = uniqueTable.getObjectAt(i);

			if (obj.isValidTable()) {
				String word = obj.getStringAt(1);
				String root = obj.getStringAt(2);
				String type = obj.getStringAt(3);

				Reference<NameUnique*> unique = new NameUnique(word, root, type);

				uniques.add(unique);
			}

			obj.pop();
		}

		uniqueTable.pop();

		LuaObject patternTable = luaObject->getObjectField("uniquePatterns");

		if (!patternTable.isValidTable()) {
			printf("Error loading name manager unique pattern table.\n");
			return;
		}

		for (int i = 1; i <= patternTable.getTableSize(); ++i) {
			LuaObject obj = patternTable.getObjectAt(i);

			if (obj.isValidTable()) {
				String pattern = obj.getStringAt(1);
				int odds = obj.getIntAt(2);

				uniquePatterns.put(pattern, odds);
				uniquePatternOdds += odds;
			}

			obj.pop();
		}

		patternTable.pop();
	}

	NameRules* getFirstNameRules() {
		return firstNameRules;
	}

	NameRules* getLastNameRules() {
		return lastNameRules;
	}

	String getRandomBeginningConsonant() {
		int randOdd = System::random(beginningConsonantOdds);
		int tempTotal = 0;
		String consonant = "";

		for (int i = 0; i < beginningConsonants.size(); i++) {
			int tempValue = beginningConsonants.elementAt(i).getValue();
			tempTotal += tempValue;

			if (randOdd <= tempTotal) {
				consonant = beginningConsonants.elementAt(i).getKey();
				break;
			}
		}

		return consonant;
	}

	bool beginningConsonantContains(String fragment) {
		return beginningConsonants.contains(fragment);
	}

	String getRandomMiddleConsonant() {
		int randOdd = System::random(middleConsonantOdds);
		int tempTotal = 0;
		String consonant = "";

		for (int i = 0; i < middleConsonants.size(); i++) {
			int tempValue = middleConsonants.elementAt(i).getValue();
			tempTotal += tempValue;

			if (randOdd <= tempTotal) {
				consonant = middleConsonants.elementAt(i).getKey();
				break;
			}
		}

		return consonant;
	}

	bool middeConsonantContains(String fragment) {
		return middleConsonants.contains(fragment);
	}

	String getRandomEndingConsonant() {
		int randOdd = System::random(endingConsonantOdds);
		int tempTotal = 0;
		String consonant = "";

		for (int i = 0; i < endingConsonants.size(); i++) {
			int tempValue = endingConsonants.elementAt(i).getValue();
			tempTotal += tempValue;

			if (randOdd <= tempTotal) {
				consonant = endingConsonants.elementAt(i).getKey();
				break;
			}
		}

		return consonant;
	}

	bool endingConsonantContains(String fragment) {
		return endingConsonants.contains(fragment);
	}

	String getRandomVowel() {
		int randOdd = System::random(vowelOdds);
		int tempTotal = 0;
		String vowel = "";

		for (int i = 0; i < vowels.size(); i++) {
			int tempValue = vowels.elementAt(i).getValue();
			tempTotal += tempValue;

			if (randOdd <= tempTotal) {
				vowel = vowels.elementAt(i).getKey();
				break;
			}
		}

		return vowel;
	}

	bool vowelsContains(String fragment) {
		return vowels.contains(fragment);
	}

	String getRandomSpecialSyllable() {
		int randOdd = System::random(specialSyllableOdds);
		int tempTotal = 0;
		String special = "";

		for (int i = 0; i < specialSyllables.size(); i++) {
			int tempValue = specialSyllables.elementAt(i).getValue();
			tempTotal += tempValue;

			if (randOdd <= tempTotal) {
				special = specialSyllables.elementAt(i).getKey();
				break;
			}
		}

		return special;
	}

	String getRandomUniquePattern() {
		int randOdd = System::random(uniquePatternOdds);
		int tempTotal = 0;
		String pattern = "";

		for (int i = 0; i < uniquePatterns.size(); i++) {
			int tempValue = uniquePatterns.elementAt(i).getValue();
			tempTotal += tempValue;

			if (randOdd <= tempTotal) {
				pattern = uniquePatterns.elementAt(i).getKey();
				break;
			}

			tempTotal += tempValue;
		}

		return pattern;
	}

	String getRandomUnique(String type, String &root) {
		Vector<Reference<NameUnique*> > uniqueList;

		for (int i = 0; i < uniques.size(); i++) {
			Reference<NameUnique*> unique = uniques.get(i);
			String uType = unique->getType();

			if (uType.contains(type))
				uniqueList.add(unique);
		}

		int randFinal = System::random(uniqueList.size() - 1);
		NameUnique* final = uniqueList.elementAt(randFinal);
		root = final->getRoot();
		return final->getWord();
	}

	bool specialSyllablesContains(String fragment) {
		return specialSyllables.contains(fragment);
	}
};

#endif /*NAMEDATA_H_*/
