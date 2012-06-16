canyon_corsair_strong_pirate = Creature:new {
	objectName = "@mob/creature_names:canyon_corsair_pirate_strong",
	socialGroup = "canyon_corsair",
	pvpFaction = "canyon_corsair",
	faction = "canyon_corsair",
	level = 36,
	chanceHit = 0.41,
	damageMin = 320,
	damageMax = 350,
	baseXp = 3642,
	baseHAM = 8800,
	baseHAMmax = 10800,
	armor = 0,
	resists = {25,60,25,25,-1,-1,25,-1,-1},
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
		"object/mobile/dressed_corsair_pirate_strong_hum_f.iff",
		"object/mobile/dressed_corsair_pirate_strong_hum_m.iff",
		"object/mobile/dressed_corsair_pirate_strong_nikto_m.iff",
		"object/mobile/dressed_corsair_pirate_strong_zab_m.iff"
		},
	lootGroups = {},
	weapons = {"pirate_weapons_heavy"},
	conversationTemplate = "",
	attacks = merge(riflemanmaster,pistoleermaster,carbineermaster,brawlermaster)
}

CreatureTemplates:addCreatureTemplate(canyon_corsair_strong_pirate, "canyon_corsair_strong_pirate")