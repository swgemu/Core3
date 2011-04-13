flail_executioner = Creature:new {
	objectName = "@mob/creature_names:flail_executioner",
	socialGroup = "Flail",
	pvpFaction = "Flail",
	faction = "",
	level = 25,
	chanceHit = 0.360000,
	damageMin = 280,
	damageMax = 290,
	baseXp = 2637,
	baseHAM = 5900,
	baseHAMmax = 7200,
	armor = 0,
	resists = {25,0,0,-1,-1,60,-1,-1,-1},
	meatType = "",
	meatAmount = 0,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = ATTACKABLE + AGGRESSIVE,
	creatureBitmask = PACK + KILLER,
	diet = HERBIVORE,

	templates = {},
	lootgroups = {},
	weapons = {"pirate_weapons_medium"},
	attacks = {}
}

CreatureTemplates:addCreatureTemplate(flail_executioner, "flail_executioner")