nameManagerReactiveGasResource = {
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

	-- Only first name is used by resources, last name values are all set to 0
	firstNameRules = {
		nameChance = 100,
		uniqueChance = 100,
		minSyllables = 2,
		maxSyllables = 3,
		minChars = 3,
		maxChars = 12,
		specialCharChance = 0,
		specialChars = "",
		maxSpecialChars = 0,
		chanceBeginsSpecial = 0,
		chanceMiddleSpecial = 0,
		chanceEndsSpecial = 0,
		maxSpecialSyllables = 0,
	},
	lastNameRules = {
		nameChance = 0,
		uniqueChance = 0,
		minSyllables = 0,
		maxSyllables = 0,
		minChars = 0,
		maxChars = 0,
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
		{ "b", true, true, true, 100 },
		{ "bl", true, true, false, 5 },
		{ "br", true, true, false, 10 },
		{ "c", true, true, true, 100 },
		{ "cc", false, false, true, 5 },
		{ "ch", true, true, true, 10 },
		{ "chr", true, true, false, 5 },
		{ "cht", false, false, true, 2 },
		{ "ck", false, true, true, 2 },
		{ "cl", true, true, false, 5 },
		{ "cr", true, true, false, 10 },
		{ "ct", false, true, true, 5 },
		{ "cz", true, true, false, 2 },
		{ "d", true, true, true, 100 },
		{ "dh", true, true, false, 2 },
		{ "dl", true, true, false, 5 },
		{ "dr", true, true, false, 10 },
		{ "dw", true, true, false, 5 },
		{ "f", true, true, true, 100 },
		{ "ff", true, true, true, 2 },
		{ "fl", true, true, false, 2 },
		{ "fr", true, true, false, 2 },
		{ "g", true, true, true, 100 },
		{ "gg", false, true, true, 2 },
		{ "gh", true, true, true, 2 },
		{ "ght", false, true, true, 2 },
		{ "gl", true, true, false, 10 },
		{ "gn", true, true, true, 2 },
		{ "gm", false, true, true, 2 },
		{ "gr", true, true, false, 10 },
		{ "gw", true, true, false, 2 },
		{ "h", true, true, true, 100 },
		{ "hn", false, true, true, 2 },
		{ "j", true, true, true, 10 },
		{ "jj", false, true, true, 2 },
		{ "k", true, true, true, 100 },
		{ "kh", true, true, false, 2 },
		{ "kk", false, true, true, 2 },
		{ "kl", true, true, false, 5 },
		{ "kr", true, true, false, 10 },
		{ "kt", false, true, true, 5 },
		{ "l", true, true, false, 100 },
		{ "lc", false, true, true, 5 },
		{ "lch", false, true, true, 2 },
		{ "ld", false, true, true, 5 },
		{ "lf", false, true, true, 2 },
		{ "lk", false, true, true, 5 },
		{ "ll", true, true, true, 10 },
		{ "lm", false, true, true, 2 },
		{ "lp", false, true, true, 2 },
		{ "lph", false, true, true, 2 },
		{ "lv", false, true, true, 2 },
		{ "m", true, true, true, 100 },
		{ "mm", false, true, true, 5 },
		{ "mn", true, true, true, 2 },
		{ "n", true, true, true, 100 },
		{ "ng", false, false, true, 2 },
		{ "nn", false, false, true, 10 },
		{ "nt", false, false, true, 10 },
		{ "p", true, true, true, 100 },
		{ "pf", true, true, false, 2 },
		{ "ph", true, true, false, 2 },
		{ "pl", true, true, false, 5 },
		{ "pp", false, true, true, 5 },
		{ "pr", true, true, false, 10 },
		{ "pt", false, true, true, 2 },
		{ "q", false, true, true, 5 },
		{ "qu", true, true, false, 5 },
		{ "r", true, true, true, 100 },
		{ "rb", false, true, true, 2 },
		{ "rc", false, true, true, 5 },
		{ "rck", false, true, true, 2 },
		{ "rch", false, true, true, 2 },
		{ "rcht", false, true, true, 2 },
		{ "rd", false, true, true, 5 },
		{ "rf", false, true, true, 5 },
		{ "rg", false, true, true, 5 },
		{ "rh", true, true, false, 5 },
		{ "rj", false, true, true, 2 },
		{ "rk", false, true, true, 5 },
		{ "rl", false, true, true, 5 },
		{ "rm", false, true, true, 2 },
		{ "rn", false, true, true, 2 },
		{ "rp", false, true, true, 2 },
		{ "rq", false, true, true, 2 },
		{ "rr", false, true, true, 5 },
		{ "rt", false, true, true, 2 },
		{ "rv", false, true, true, 2 },
		{ "rx", false, true, true, 2 },
		{ "rz", false, true, true, 2 },
		{ "s", true, true, true, 100 },
		{ "sc", true, true, true, 5 },
		{ "sch", true, true, false, 2 },
		{ "schl", true, true, false, 2 },
		{ "sh", true, true, true, 10 },
		{ "sk", true, true, true, 10 },
		{ "sl", true, true, false, 10 },
		{ "sm", true, true, false, 10 },
		{ "sn", true, true, false, 10 },
		{ "sp", true, true, true, 10 },
		{ "sq", false, true, true, 2 },
		{ "squ", true, true, false, 2 },
		{ "sr", true, true, false, 30 },
		{ "ss", true, true, true, 10 },
		{ "st", true, true, true, 30 },
		{ "sv", true, true, false, 2 },
		{ "sw", true, true, true, 2 },
		{ "sx", false, true, true, 2 },
		{ "t", true, true, true, 100 },
		{ "tch", false, true, true, 5 },
		{ "th", true, true, true, 30 },
		{ "thm", false, true, true, 5 },
		{ "tr", true, true, false, 10 },
		{ "ts", true, true, true, 2 },
		{ "tt", false, true, true, 10 },
		{ "tw", true, true, false, 5 },
		{ "tz", true, true, false, 2 },
		{ "v", true, true, true, 100 },
		{ "vv", false, true, true, 5 },
		{ "w", true, true, true, 100 },
		{ "wh", true, true, false, 10 },
		{ "wr", true, true, false, 10 },
		{ "ww", false, true, true, 5 },
		{ "x", true, true, true, 10 },
		{ "y", true, true, true, 10 },
		{ "z", true, true, true, 10 },
	},

	-- Vowels used in name generation
	-- { consonant, odds }
	-- Odds field determines the likelihood of the vowel being picked
	-- Vowels can be multiple letters long and will be used throughout the name
	vowels = {
		{ "a", 100 },
		{ "ae", 5 },
		{ "ai", 5 },
		{ "ao", 5 },
		{ "au", 5 },
		{ "e", 100 },
		{ "ea", 5 },
		{ "ee", 100 },
		{ "ei", 5 },
		{ "eo", 5 },
		{ "i", 100 },
		{ "ia", 5 },
		{ "ie", 5 },
		{ "io", 5 },
		{ "o", 100 },
		{ "oa", 5 },
		{ "oe", 5 },
		{ "oi", 5 },
		{ "oo", 100 },
		{ "ou", 5 },
		{ "u", 5 },
		{ "y", 5 },
	},

	-- List of special syllables that can be used by the name generator
	-- { syllable, odds }
	-- Odds determine the likelihood of the syllable being chosen
	-- rules table handles where in the name syllables can be inserted
	specials = {},

	-- Unique patterns used by the name generator.
	-- { pattern, odds }
	-- The pattern handles how unique words are placed together to create a name.
	-- Each letter in a pattern must correspond to one or more types in the uniques table
	-- Using a * in the pattern will tell the name generator to generate a random name in that position
	-- Odds determine the likelihood of the pattern being used, and the rules table handles the chance of using a pattern.
	uniquePatterns = {
		{ "*", 100 },
		{ "*u", 30 },
		{ "t*", 30 },
		{ "t*u", 40 },
	},

	-- Uniques used by the name generator.
	-- { word, root, type }
	-- The word is the string that will be used in the name
	-- The root will be stored after using the word during generation to make sure that it is not used more than once
	-- This will prevent names like "Lightlighter"
	-- The type corresponds to a position in a pattern listed above.
	uniques = {
		{ "meth", "", "t", 100 },
		{ "eth", "", "t", 100 },
		{ "prop", "", "t", 100 },
		{ "but", "", "t", 100 },
		{ "pent", "", "t", 100 },
		{ "hex", "", "t", 100 },
		{ "hept", "", "t", 100 },
		{ "oct", "", "t", 100 },
		{ "non", "", "t", 100 },
		{ "dec", "", "t", 100 },
		{ "gen", "", "t", 100 },
		{ "ate", "", "u", 100 },
		{ "ene", "", "u", 100 },
		{ "yl", "", "u", 100 },
	}
}
