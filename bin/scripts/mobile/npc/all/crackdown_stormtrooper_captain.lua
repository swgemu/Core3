crackdown_stormtrooper_captain = Creature:new {
	objectName = "@mob/creature_names:crackdown_stormtrooper_captain",
	socialGroup = "Imperial",
	pvpFaction = "Imperial",
	faction = "",
	level = 1,
	chanceHit = 0.380000,
	damageMin = 280,
	damageMax = 290,
	baseXp = 45,
	baseHAM = 8300,
	baseHAMmax = 10100,
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

CreatureTemplates:addCreatureTemplate(crackdown_stormtrooper_captain, "crackdown_stormtrooper_captain")