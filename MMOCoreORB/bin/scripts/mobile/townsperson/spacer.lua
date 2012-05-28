spacer = Creature:new {
	objectName = "@mob/creature_names:spacer",
	socialGroup = "townsperson",
	pvpFaction = "townsperson",
	faction = "townsperson",
	level = 4,
	chanceHit = 0.240000,
	damageMin = 40,
	damageMax = 45,
	baseXp = 62,
	baseHAM = 113,
	baseHAMmax = 138,
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
	pvpBitmask = NONE,
	creatureBitmask = NONE,
	diet = HERBIVORE,

	templates = {
		"object/mobile/dressed_criminal_pirate_human_female_01.iff"
	},
	lootGroups = {},
	weapons = {},
	attacks = {}
}

CreatureTemplates:addCreatureTemplate(spacer, "spacer")