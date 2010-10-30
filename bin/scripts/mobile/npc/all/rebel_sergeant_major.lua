rebel_sergeant_major = Creature:new {
	objectName = "@mob/creature_names:rebel_sergeant_major",
	socialGroup = "Rebel",
	pvpFaction = "Rebel",
	faction = "",
	level = 17,
	chanceHit = 0.320000,
	damageMin = 160,
	damageMax = 170,
	baseXp = 1102,
	baseHAM = 2500,
	baseHAMmax = 4300,
	armor = 0,
	resists = {0,0,0,0,0,0,0,-1,-1},
	meatType = "",
	meatAmount = 0,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK,
	diet = HERBIVORE,

	templates = {},
	lootgroups = {},
	weapons = {"rebel_weapons_medium"},
	attacks = {}
}

CreatureTemplates:addCreatureTemplate(rebel_sergeant_major, "rebel_sergeant_major")