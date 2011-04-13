blood_razor_elite_pirate = Creature:new {
	objectName = "Blood Razor elite pirate",
	socialGroup = "Bloodrazor",
	pvpFaction = "Bloodrazor",
	faction = "",
	level = 33,
	chanceHit = 0.390000,
	damageMin = 325,
	damageMax = 360,
	baseXp = 3370,
	baseHAM = 8100,
	baseHAMmax = 9900,
	armor = 0,
	resists = {0,60,0,0,-1,0,0,-1,-1},
	meatType = "",
	meatAmount = 0,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = ATTACKABLE + AGGRESSIVE,
	creatureBitmask = PACK + KILLER,
	diet = HERBIVORE,

	templates = {},
	lootgroups = {},
	weapons = {"pirate_weapons_heavy"},
	attacks = {}
}

CreatureTemplates:addCreatureTemplate(blood_razor_elite_pirate, "blood_razor_elite_pirate")