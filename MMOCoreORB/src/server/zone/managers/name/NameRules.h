#ifndef NAMERULES_H_
#define NAMERULES_H_

class NameRules: public Object {
	int nameChance;
	int minSyllables, maxSyllables;
	int minChars, maxChars;
	int specialCharChance;
	int maxSpecialChars;
	int chanceBeginsSpecial, chanceMiddleSpecial, chanceEndsSpecial;
	int maxSpecialSyllables;
	int uniqueChance;

	String specialChars;

public:
	NameRules() {
		nameChance = 0;
		minSyllables = 0;
		maxSyllables = 0;
		minChars = 0;
		maxChars = 0;
		specialCharChance = 0;
		maxSpecialChars = 0;
		chanceBeginsSpecial = 0;
		chanceMiddleSpecial = 0;
		chanceEndsSpecial = 0;
		maxSpecialSyllables = 0;
		uniqueChance = 0;

		specialChars = "";
	}

	NameRules(const NameRules& rules) : Object() {
		nameChance = rules.nameChance;
		minSyllables = rules.minSyllables;
		maxSyllables = rules.maxSyllables;
		minChars = rules.minChars;
		maxChars = rules.maxChars;
		specialCharChance = rules.specialCharChance;
		maxSpecialChars = rules.maxSpecialChars;
		chanceBeginsSpecial = rules.chanceBeginsSpecial;
		chanceMiddleSpecial = rules.chanceMiddleSpecial;
		chanceEndsSpecial = rules.chanceEndsSpecial;
		maxSpecialSyllables = rules.maxSpecialSyllables;
		uniqueChance = rules.uniqueChance;

		specialChars = rules.specialChars;
	}

	NameRules& operator=(const NameRules& rules) {
		if (this == &rules)
			return *this;

		nameChance = rules.nameChance;
		minSyllables = rules.minSyllables;
		maxSyllables = rules.maxSyllables;
		minChars = rules.minChars;
		maxChars = rules.maxChars;
		specialCharChance = rules.specialCharChance;
		maxSpecialChars = rules.maxSpecialChars;
		chanceBeginsSpecial = rules.chanceBeginsSpecial;
		chanceMiddleSpecial = rules.chanceMiddleSpecial;
		chanceEndsSpecial = rules.chanceEndsSpecial;
		maxSpecialSyllables = rules.maxSpecialSyllables;
		uniqueChance = rules.uniqueChance;

		specialChars = rules.specialChars;

		return *this;
	}

	void readObject(LuaObject* luaObject) {
		if (!luaObject->isValidTable())
			return;

		nameChance = luaObject->getIntField("nameChance");
		minSyllables = luaObject->getIntField("minSyllables");
		maxSyllables = luaObject->getIntField("maxSyllables");
		minChars = luaObject->getIntField("minChars");
		maxChars = luaObject->getIntField("maxChars");
		specialCharChance = luaObject->getIntField("specialCharChance");
		maxSpecialChars = luaObject->getIntField("maxSpecialChars");
		chanceBeginsSpecial = luaObject->getIntField("chanceBeginsSpecial");
		chanceMiddleSpecial = luaObject->getIntField("chanceMiddleSpecial");
		chanceEndsSpecial = luaObject->getIntField("chanceEndsSpecial");
		maxSpecialSyllables = luaObject->getIntField("maxSpecialSyllables");
		uniqueChance = luaObject->getIntField("uniqueChance");

		specialChars = luaObject->getStringField("specialChars");
	}

	int getNameChance() {
		return nameChance;
	}

	int getUniqueChance() {
		return uniqueChance;
	}

	int getMinSyllables() {
		return minSyllables;
	}

	int getMaxSyllables() {
		return maxSyllables;
	}

	int getMinChars() {
		return minChars;
	}

	int getMaxChars() {
		return maxChars;
	}

	int getSpecialCharChance() {
		return specialCharChance;
	}

	int getMaxSpecialChars() {
		return maxSpecialChars;
	}

	int getChanceBeginsSpecial() {
		return chanceBeginsSpecial;
	}

	int getChanceMiddleSpecial() {
		return chanceMiddleSpecial;
	}

	int getChanceEndsSpecial() {
		return chanceEndsSpecial;
	}

	int getMaxSpecialSyllables() {
		return maxSpecialSyllables;
	}

	String getRandomSpecialChar() {
		int strLen = specialChars.length() - 1;
		int randIndex = System::random(strLen);
		String randChar = specialChars.subString(randIndex, randIndex + 1);
		return randChar;
	}

	String getSpecialChars() {
		return specialChars;
	}
};

#endif /*NAMERULES_H_*/
