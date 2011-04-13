imperial_research_captain_coa3 = Creature:new {
	objectName = "Imperial research captain (COA3)",
	socialGroup = "Rebel",
	pvpFaction = "Rebel",
	faction = "",
	level = 45,
	chanceHit = 0.460000,
	damageMin = 365,
	damageMax = 440,
	baseXp = 4461,
	baseHAM = 9600,
	baseHAMmax = 11800,
	armor = 0,
	resists = {0,35,0,0,0,0,0,0,-1},
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
	creatureBitmask = PACK + KILLER + HERD,
	diet = HERBIVORE,

	templates = {},
	lootgroups = {},
	weapons = {"rebel_weapons_heavy"},
	attacks = {}
}

CreatureTemplates:addCreatureTemplate(imperial_research_captain_coa3, "imperial_research_captain_coa3")