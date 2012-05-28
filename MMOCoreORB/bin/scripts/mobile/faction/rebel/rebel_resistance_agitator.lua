rebel_resistance_agitator = Creature:new {
	objectName = "@mob/creature_names:rebel_resistance_agitator",
	socialGroup = "rebel",
	pvpFaction = "rebel",
	faction = "rebel",
	level = 7,
	chanceHit = 0.260000,
	damageMin = 55,
	damageMax = 65,
	baseXp = 187,
	baseHAM = 270,
	baseHAMmax = 330,
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
	lootGroups = {},
	weapons = {"rebel_weapons_light"},
	attacks = merge(riflemanmaster,pistoleermaster,carbineermaster,brawlermaster)
}

CreatureTemplates:addCreatureTemplate(rebel_resistance_agitator, "rebel_resistance_agitator")