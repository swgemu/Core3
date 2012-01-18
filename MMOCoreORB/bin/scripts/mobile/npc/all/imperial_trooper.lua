imperial_trooper = Creature:new {
	objectName = "@mob/creature_names:imperial_trooper",
	socialGroup = "Imperial",
	pvpFaction = "Imperial",
	faction = "",
	level = 35,
	chanceHit = 0.40,
	damageMin = 305,
	damageMax = 320,
	baseXp = 2256,
	baseHAM = 9500,
	baseHAMmax = 12000,
	armor = 0,
	resists = {40,20,20,50,50,50,50,-1,-1},
	meatType = "",
	meatAmount = 0,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK,
	optionsBitmask = 128,
	diet = HERBIVORE,
	lootChance = 5500000,

	templates = {"object/mobile/dark_trooper.iff"},
	lootgroups = {
		{group = "holocron_light", chance = 1000000},
		{group = "holocron_dark", chance = 500000},
		{group = "pistols", chance = 4250000},
		{group = "rifles", chance = 4250000}
	},
	weapons = {"imperial_weapons_light"},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(imperial_trooper, "imperial_trooper")