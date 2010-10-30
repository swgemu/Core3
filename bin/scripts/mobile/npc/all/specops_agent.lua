specops_agent = Creature:new {
	objectName = "@mob/creature_names:specops_agent",
	socialGroup = "Rebel",
	pvpFaction = "Rebel",
	faction = "",
	level = 24,
	chanceHit = 0.350000,
	damageMin = 230,
	damageMax = 240,
	baseXp = 2543,
	baseHAM = 6800,
	baseHAMmax = 8300,
	armor = 0,
	resists = {15,15,0,0,0,-1,0,-1,-1},
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
	creatureBitmask = PACK + KILLER,
	diet = HERBIVORE,

	templates = {},
	lootgroups = {},
	weapons = {"imperial_weapons_heavy"},
	attacks = {}
}

CreatureTemplates:addCreatureTemplate(specops_agent, "specops_agent")