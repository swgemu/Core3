blood_razor_destroyer = Creature:new {
	objectName = "@mob/creature_names:blood_razor_destroyer",
	socialGroup = "Bloodrazor",
	pvpFaction = "Bloodrazor",
	faction = "",
	level = 38,
	chanceHit = 0.420000,
	damageMin = 385,
	damageMax = 480,
	baseXp = 3824,
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

CreatureTemplates:addCreatureTemplate(blood_razor_destroyer, "blood_razor_destroyer")