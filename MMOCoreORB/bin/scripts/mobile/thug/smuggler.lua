smuggler = Creature:new {
	objectName = "@mob/creature_names:smuggler",
	socialGroup = "Thug",
	pvpFaction = "Thug",
	faction = "",
	level = 14,
	chanceHit = 0.300000,
	damageMin = 150,
	damageMax = 160,
	baseXp = 714,
	baseHAM = 2000,
	baseHAMmax = 3000,
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
	creatureBitmask = KILLER,
	diet = HERBIVORE,

	templates = {"object/mobile/dressed_criminal_slicer_human_male_01.iff"},
	lootGroups = {},
	weapons = {"pirate_weapons_medium"},
	attacks = merge(riflemanmaster,pistoleermaster,carbineermaster,brawlermaster)
}

CreatureTemplates:addCreatureTemplate(smuggler, "smuggler")