spice_collective_heavy_guard = Creature:new {
	objectName = "Spice Collective heavy guard",
	socialGroup = "Spice Collect.",
	pvpFaction = "Spice Collect.",
	faction = "",
	level = 22,
	chanceHit = 0.340000,
	damageMin = 200,
	damageMax = 210,
	baseXp = 2219,
	baseHAM = 5400,
	baseHAMmax = 6600,
	armor = 0,
	resists = {0,30,0,0,-1,0,-1,-1,-1},
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
	weapons = {"pirate_weapons_heavy"},
	attacks = {}
}

CreatureTemplates:addCreatureTemplate(spice_collective_heavy_guard, "spice_collective_heavy_guard")