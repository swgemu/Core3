crackdown_scout_trooper = Creature:new {
	objectName = "@mob/creature_names:crackdown_scout_trooper",
	socialGroup = "Imperial",
	pvpFaction = "Imperial",
	faction = "",
	level = 1,
	chanceHit = 0.350000,
	damageMin = 220,
	damageMax = 230,
	baseXp = 30,
	baseHAM = 6300,
	baseHAMmax = 7700,
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
	creatureBitmask = NONE,
	diet = HERBIVORE,

	templates = {},
	lootgroups = {},
	weapons = {"imperial_weapons_heavy"},
	attacks = {}
}

CreatureTemplates:addCreatureTemplate(crackdown_scout_trooper, "crackdown_scout_trooper")