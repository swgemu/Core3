specforce_procurement_specialist = Creature:new {
	objectName = "@mob/creature_names:specforce_procurement_specialist",
	socialGroup = "Rebel",
	pvpFaction = "Rebel",
	faction = "",
	level = 13,
	chanceHit = 0.300000,
	damageMin = 140,
	damageMax = 150,
	baseXp = 609,
	baseHAM = 1500,
	baseHAMmax = 1900,
	armor = 0,
	resists = {0,0,0,0,0,0,0,0,-1},
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
	weapons = {"imperial_weapons_light"},
	attacks = {}
}

CreatureTemplates:addCreatureTemplate(specforce_procurement_specialist, "specforce_procurement_specialist")