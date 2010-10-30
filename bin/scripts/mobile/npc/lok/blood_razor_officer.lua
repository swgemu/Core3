blood_razor_officer = Creature:new {
	objectName = "@mob/creature_names:blood_razor_officer",
	socialGroup = "Bloodrazor",
	pvpFaction = "Bloodrazor",
	faction = "",
	level = 40,
	chanceHit = 0.430000,
	damageMin = 335,
	damageMax = 380,
	baseXp = 4006,
	baseHAM = 9100,
	baseHAMmax = 11100,
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

CreatureTemplates:addCreatureTemplate(blood_razor_officer, "blood_razor_officer")