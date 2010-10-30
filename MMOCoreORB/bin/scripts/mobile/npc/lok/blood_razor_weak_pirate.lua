blood_razor_weak_pirate = Creature:new {
	objectName = "Blood Razor weak pirate",
	socialGroup = "Bloodrazor",
	pvpFaction = "Bloodrazor",
	faction = "",
	level = 21,
	chanceHit = 0.330000,
	damageMin = 230,
	damageMax = 240,
	baseXp = 2006,
	baseHAM = 2900,
	baseHAMmax = 3500,
	armor = 0,
	resists = {0,25,0,0,-1,-1,0,-1,-1},
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

CreatureTemplates:addCreatureTemplate(blood_razor_weak_pirate, "blood_razor_weak_pirate")