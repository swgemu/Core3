crackdown_stormtrooper_rifleman = Creature:new {
	objectName = "@mob/creature_names:crackdown_stormtrooper_rifleman",
	socialGroup = "Imperial",
	pvpFaction = "Imperial",
	faction = "",
	level = 1,
	chanceHit = 0.360000,
	damageMin = 240,
	damageMax = 250,
	baseXp = 45,
	baseHAM = 7200,
	baseHAMmax = 8800,
	armor = 0,
	resists = {0,0,40,0,0,0,0,-1,-1},
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
	weapons = {"st_rifleman_weapons"},
	attacks = {}
}

CreatureTemplates:addCreatureTemplate(crackdown_stormtrooper_rifleman, "crackdown_stormtrooper_rifleman")