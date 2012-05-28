blood_razor_berzerker = Creature:new {
	objectName = "@mob/creature_names:blood_razor_berzerker",
	socialGroup = "bloodrazor",
	pvpFaction = "bloodrazor",
	faction = "bloodrazor",
	level = 36,
	chanceHit = 0.43,
	damageMin = 395,
	damageMax = 500,
	baseXp = 3642,
	baseHAM = 8300,
	baseHAMmax = 10100,
	armor = 0,
	resists = {-1,60,25,25,-1,25,25,-1,-1},
	meatType = "",
	meatAmount = 0,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = PACK + KILLER,
	optionsBitmask = 128,
	diet = HERBIVORE,

	templates = {
		"object/mobile/dressed_blood_razor_pirate_berzerker_hum_f.iff",
		"object/mobile/dressed_blood_razor_pirate_berzerker_hum_m.iff",
		"object/mobile/dressed_blood_razor_pirate_berzerker_rod_m.iff",
		"object/mobile/dressed_blood_razor_pirate_berzerker_tran_m.iff"
		},
	lootGroups = {},
	weapons = {"pirate_weapons_heavy"},
	conversationTemplate = "",
	attacks = merge(riflemanmaster,pistoleermaster,carbineermaster,brawlermaster)
}

CreatureTemplates:addCreatureTemplate(blood_razor_berzerker, "blood_razor_berzerker")