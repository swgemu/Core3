stormtrooper_black_hole_squad_leader = Creature:new {
	objectName = "Stormtrooper Black Hole Squad Leader",
	socialGroup = "Imperial",
	pvpFaction = "Imperial",
	faction = "",
	level = 29,
	chanceHit = 3.080000,
	damageMin = 280,
	damageMax = 290,
	baseXp = 3005,
	baseHAM = 8300,
	baseHAMmax = 10000,
	armor = 0,
	resists = {0,0,0,-1,30,-1,30,-1,-1},
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
	weapons = {"stormtrooper_weapons"},
	attacks = {}
}

CreatureTemplates:addCreatureTemplate(stormtrooper_black_hole_squad_leader, "stormtrooper_black_hole_squad_leader")