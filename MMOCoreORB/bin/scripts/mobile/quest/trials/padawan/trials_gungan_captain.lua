trials_gungan_captain = Creature:new {
	objectName = "",
	customName = "a Gungan Captain",
	socialGroup = "gungan",
	faction = "gungan",
	level = 10,
	chanceHit = 0.28,
	damageMin = 90,
	damageMax = 110,
	baseXp = 356,
	baseHAM = 810,
	baseHAMmax = 990,
	armor = 0,
	resists = {0,0,0,0,0,0,0,-1,-1},
	meatType = "",
	meatAmount = 0,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = NONE,
	creatureBitmask = PACK,
	optionsBitmask = 128,
	diet = HERBIVORE,

	templates = {"object/mobile/gungan_s04_male.iff", "object/mobile/gungan_male.iff"},
	lootGroups = {},
	weapons = {},
	conversationTemplate = "trialsPadawanArchitect02ConvoTemplate",
	attacks = {}
	
}

CreatureTemplates:addCreatureTemplate(trials_gungan_captain, "trials_gungan_captain")
