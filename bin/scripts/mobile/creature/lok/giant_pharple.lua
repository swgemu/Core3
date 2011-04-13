giant_pharple = Creature:new {
	objectName = "@mob/creature_names:giant_pharple",
	socialGroup = "Pharple",
	pvpFaction = "",
	faction = "",
	level = 7,
	chanceHit = 0.260000,
	damageMin = 55,
	damageMax = 65,
	baseXp = 187,
	baseHAM = 300,
	baseHAMmax = 300,
	armor = 0,
	resists = {0,0,0,0,0,0,0,-1,-1},
	meatType = "meat_avian",
	meatAmount = 21,
	hideType = "hide_bristley",
	hideAmount = 12,
	boneType = "bone_avian",
	boneAmount = 9,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK + HERD,
	diet = CARNIVORE,

	templates = {"object/mobile/giant_pharple.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {}
}

CreatureTemplates:addCreatureTemplate(giant_pharple, "giant_pharple")