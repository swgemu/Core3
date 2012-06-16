marooned_pirate_captain = Creature:new {
	objectName = "@mob/creature_names:marooned_pirate_captain",
	socialGroup = "pirate",
	pvpFaction = "pirate",
	faction = "pirate",
	level = 24,
	chanceHit = 0.35,
	damageMin = 210,
	damageMax = 220,
	baseXp = 2543,
	baseHAM = 5900,
	baseHAMmax = 7200,
	armor = 0,
	resists = {20,20,10,40,-1,40,10,-1,-1},
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

	aiTemplate = "default",

	templates = {
		"object/mobile/dressed_marooned_pirate_captain_hum_m.iff",
		"object/mobile/dressed_marooned_pirate_captain_nikto_m.iff",
		"object/mobile/dressed_marooned_pirate_captain_tran_m.iff",
		"object/mobile/dressed_marooned_pirate_captain_wee_m.iff"
		},
	lootGroups = {},
	weapons = {"pirate_weapons_heavy"},
	conversationTemplate = "",
	attacks = merge(riflemanmaster,pistoleermaster,carbineermaster,brawlermaster)
}

CreatureTemplates:addCreatureTemplate(marooned_pirate_captain, "marooned_pirate_captain")