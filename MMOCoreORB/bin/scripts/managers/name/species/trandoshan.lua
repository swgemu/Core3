nameManagerTrandoshan = {
	-- Name Rules (First and last name)
	-- nameChance 				- Chance that the name generator will create the first or last name. Setting to 0 will prevent
	--					 				the name generator from generating the name. First name should always be 100.
	-- uniqueChance 			- Chance that the generator will make use of any unique patterns listed below.
	-- minSyllables 			- Minimum syllables that must be created by the name generator
	-- maxSyllables 			- Max syllables to be created by the name generator
	-- minChars     			- Minimum length of the name created
	-- maxChars		 			- Maximum length of the name created
	-- specialCharChance		- Chance of the name generator using one of the special characters listed in specialChars
	-- specialChars			- Special chars that can be used when generating the name
	-- maxSpecialChars		- Limit on how many special chars the generator can put into a name
	-- chanceBeginsSpecial	- Chance that the generator will use a special syllable at the beginning of the name
	-- chanceMiddleSpecial	- Chance that the generator will use a special syllable in the middle of the name
	-- chanceEndsSpecial		- Chance that the generator will use a special syllable at the end of the name
	-- maxSpecialSyllables	- Maximum number of special syllables that can be used in a name

	firstNameRules = {
		nameChance = 100,
		uniqueChance = 0,
		minSyllables = 2,
		maxSyllables = 3,
		minChars = 3,
		maxChars = 15,
		specialCharChance = 0,
		specialChars = "",
		maxSpecialChars = 0,
		chanceBeginsSpecial = 20,
		chanceMiddleSpecial = 20,
		chanceEndsSpecial = 20,
		maxSpecialSyllables = 1,
	},
	lastNameRules = {
		nameChance = 15,
		uniqueChance = 0,
		minSyllables = 2,
		maxSyllables = 3,
		minChars = 3,
		maxChars = 20,
		specialCharChance = 0,
		specialChars = "",
		maxSpecialChars = 0,
		chanceBeginsSpecial = 20,
		chanceMiddleSpecial = 20,
		chanceEndsSpecial = 20,
		maxSpecialSyllables = 1,
	},

	-- Consonants used in name generation
	-- { consonant, beginning, middle, end, odds }
	-- Odds field determines the likelihood of the consonant being picked
	-- Consonants can be multiple letters long
	consonants = {
		{ "b", true, true, true, 10 },
		{ "c", true, true, true, 10 },
		{ "d", true, true, true, 10 },
		{ "l", true, true, false, 10 },
		{ "m", true, true, true, 10 },
		{ "n", true, true, true, 10 },
		{ "p", true, true, true, 10 },
		{ "r", true, true, true, 10 },
		{ "rx", false, true, true, 10 },
		{ "rz", false, true, true, 10 },
		{ "s", true, true, true, 10 },
		{ "sc", true, true, true, 10 },
		{ "sh", true, true, true, 10 },
		{ "sk", true, true, true, 10 },
		{ "sl", true, true, false, 10 },
		{ "sr", true, true, false, 10 },
		{ "ss", true, true, true, 10 },
		{ "ssk", false, true, true, 10 },
		{ "st", true, true, true, 10 },
		{ "sv", true, true, false, 10 },
		{ "sx", false, true, true, 10 },
		{ "t", true, true, true, 10 },
		{ "tr", true, true, false, 10 },
		{ "ts", true, true, true, 10 },
		{ "tz", true, true, false, 10 },
		{ "v", true, true, true, 10 },
		{ "w", true, true, true, 10 },
		{ "x", true, true, true, 10 },
		{ "z", true, true, true, 10 },
		{ "zz", false, true, true, 10 },
	},

	-- Vowels used in name generation
	-- { consonant, odds }
	-- Odds field determines the likelihood of the vowel being picked
	-- Vowels can be multiple letters long and will be used throughout the name
	vowels = {
		{ "a", 10 },
		{ "i", 100 },
		{ "o", 100 },
		{ "u", 10 },
		{ "y", 10 },
	},

	-- List of special syllables that can be used by the name generator
	-- { syllable, odds }
	-- Odds determine the likelihood of the syllable being chosen
	-- rules table handles where in the name syllables can be inserted
	specials = {
		{ "ossk", 10 },
		{ "iss", 10 },
		{ "uss", 10 },
	},

	-- Unique patterns used by the name generator.
	-- { pattern, odds }
	-- The pattern handles how unique words are placed together to create a name.
	-- Each letter in a pattern must correspond to one or more types in the uniques table
	-- Using a * in the pattern will tell the name generator to generate a random name in that position
	-- Odds determine the likelihood of the pattern being used, and the rules table handles the chance of using a pattern.
	uniquePatterns = {},

	-- Uniques used by the name generator.
	-- { word, root, type }
	-- The word is the string that will be used in the name
	-- The root will be stored after using the word during generation to make sure that it is not used more than once
	-- This will prevent names like "Lightlighter"
	-- The type corresponds to a position in a pattern listed above.
	uniques = {}
}
