nameManagerIthorian = {
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
		chanceBeginsSpecial = 0,
		chanceMiddleSpecial = 0,
		chanceEndsSpecial = 0,
		maxSpecialSyllables = 0,
	},
	lastNameRules = {
		nameChance = 85,
		uniqueChance = 0,
		minSyllables = 2,
		maxSyllables = 3,
		minChars = 3,
		maxChars = 20,
		specialCharChance = 0,
		specialChars = "",
		maxSpecialChars = 0,
		chanceBeginsSpecial = 0,
		chanceMiddleSpecial = 0,
		chanceEndsSpecial = 0,
		maxSpecialSyllables = 0,
	},

	-- Consonants used in name generation
	-- { consonant, beginning, middle, end, odds }
	-- Odds field determines the likelihood of the consonant being picked
	-- Consonants can be multiple letters long
	consonants = {
		{ "b", true, true, true, 50 },
		{ "bl", true, true, false, 2 },
		{ "br", true, true, false, 2 },
		{ "c", true, true, true, 100 },
		{ "cc", false, false, true, 2 },
		{ "ch", true, true, true, 2 },
		{ "cl", true, true, false, 2 },
		{ "cr", true, true, false, 2 },
		{ "d", true, true, true, 50 },
		{ "dh", true, true, false, 2 },
		{ "dl", true, true, false, 2 },
		{ "dr", true, true, false, 2 },
		{ "dw", true, true, false, 2 },
		{ "f", true, true, true, 100 },
		{ "fl", true, true, false, 2 },
		{ "fr", true, true, false, 2 },
		{ "g", true, true, true, 100 },
		{ "gg", false, true, true, 2 },
		{ "gl", true, true, false, 2 },
		{ "gr", true, true, false, 2 },
		{ "gw", true, true, false, 2 },
		{ "h", true, true, true, 50 },
		{ "j", true, true, true, 10 },
		{ "k", true, true, true, 100 },
		{ "kh", true, true, false, 2 },
		{ "kk", false, true, true, 2 },
		{ "kl", true, true, false, 2 },
		{ "kr", true, true, false, 2 },
		{ "l", true, true, false, 100 },
		{ "ll", true, true, true, 2 },
		{ "lm", false, true, true, 2 },
		{ "lp", false, true, true, 2 },
		{ "m", true, true, true, 100 },
		{ "n", true, true, true, 100 },
		{ "ng", false, false, true, 2 },
		{ "nn", false, false, true, 2 },
		{ "p", true, true, true, 100 },
		{ "pl", true, true, false, 2 },
		{ "pr", true, true, false, 2 },
		{ "pt", false, true, true, 2 },
		{ "r", true, true, true, 100 },
		{ "rb", false, true, true, 2 },
		{ "rd", false, true, true, 2 },
		{ "rf", false, true, true, 2 },
		{ "rg", false, true, true, 2 },
		{ "rh", true, true, false, 2 },
		{ "rj", false, true, true, 2 },
		{ "rk", false, true, true, 2 },
		{ "rl", false, true, true, 2 },
		{ "rm", false, true, true, 2 },
		{ "rn", false, true, true, 2 },
		{ "rp", false, true, true, 2 },
		{ "rq", false, true, true, 2 },
		{ "rr", false, true, true, 2 },
		{ "rt", false, true, true, 2 },
		{ "rv", false, true, true, 2 },
		{ "rx", false, true, true, 2 },
		{ "rz", false, true, true, 2 },
		{ "s", true, true, true, 100 },
		{ "sc", true, true, true, 2 },
		{ "sh", true, true, true, 2 },
		{ "sk", true, true, true, 2 },
		{ "sl", true, true, false, 2 },
		{ "sm", true, true, false, 2 },
		{ "sn", true, true, false, 2 },
		{ "sp", true, true, true, 2 },
		{ "sr", true, true, false, 2 },
		{ "ss", true, true, true, 2 },
		{ "st", true, true, true, 10 },
		{ "sv", true, true, false, 2 },
		{ "sw", true, true, true, 2 },
		{ "sx", false, true, true, 2 },
		{ "t", true, true, true, 100 },
		{ "tch", false, true, true, 2 },
		{ "th", true, true, true, 2 },
		{ "tr", true, true, false, 2 },
		{ "tt", false, true, true, 2 },
		{ "tw", true, true, false, 2 },
		{ "v", true, true, true, 100 },
		{ "vv", false, true, true, 2 },
		{ "w", true, true, true, 100 },
		{ "wh", true, true, false, 2 },
		{ "wr", true, true, false, 2 },
		{ "x", true, true, true, 2 },
		{ "y", true, true, true, 2 },
		{ "z", true, true, true, 2 },
	},

	-- Vowels used in name generation
	-- { consonant, odds }
	-- Odds field determines the likelihood of the vowel being picked
	-- Vowels can be multiple letters long and will be used throughout the name
	vowels = {
		{ "a", 100 },
		{ "ae", 50 },
		{ "ai", 50 },
		{ "aie", 1 },
		{ "ao", 10 },
		{ "au", 10 },
		{ "e", 100 },
		{ "ea", 50 },
		{ "ee", 50 },
		{ "ei", 50 },
		{ "eia", 1 },
		{ "eo", 10 },
		{ "eu", 10 },
		{ "i", 100 },
		{ "ia", 50 },
		{ "ie", 50 },
		{ "io", 10 },
		{ "o", 100 },
		{ "oa", 10 },
		{ "oe", 10 },
		{ "oi", 10 },
		{ "oo", 10 },
		{ "ou", 10 },
		{ "u", 10 },
		{ "y", 50 },
	},

	-- List of special syllables that can be used by the name generator
	-- { syllable, odds }
	-- Odds determine the likelihood of the syllable being chosen
	-- rules table handles where in the name syllables can be inserted
	specials = {
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