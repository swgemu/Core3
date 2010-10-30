frenzied_korga = Creature:new {
	objectName = "@mob/creature_names:frenzied_korga",
	socialGroup = "Korga Tribe",
	pvpFaction = "Korga Tribe",
	faction = "",
	level = 35,
	chanceHit = 0.410000,
	damageMin = 355,
	damageMax = 420,
	baseXp = 3551,
	baseHAM = 8500,
	baseHAMmax = 10300,
	armor = 0,
	resists = {0,0,0,60,60,-1,0,-1,-1},
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
	weapons = {""},
	attacks = {}
}

CreatureTemplates:addCreatureTemplate(frenzied_korga, "frenzied_korga")