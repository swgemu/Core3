plasma_thieving_swamp_trooper_captain = Creature:new {
	objectName = "plasma-thieving Swamp Trooper Captain",
	socialGroup = "Plasma Thief",
	pvpFaction = "Plasma Thief",
	faction = "",
	level = 30,
	chanceHit = 0.390000,
	damageMin = 290,
	damageMax = 300,
	baseXp = 3097,
	baseHAM = 8400,
	baseHAMmax = 10200,
	armor = 0,
	resists = {30,30,0,-1,-1,-1,50,-1,-1},
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

CreatureTemplates:addCreatureTemplate(plasma_thieving_swamp_trooper_captain, "plasma_thieving_swamp_trooper_captain")