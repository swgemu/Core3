dark_adept = Creature:new {
	objectName = "@mob/creature_names:dark_adept",
	socialGroup = "Dark Jedi",
	pvpFaction = "",
	faction = "",
	level = 140,
	chanceHit = 4.750000,
	damageMin = 945,
	damageMax = 1600,
	baseXp = 13178,
	baseHAM = 50000,
	baseHAMmax = 61000,
	armor = 0,
	resists = {80,80,80,80,80,80,80,80,-1},
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
	creatureBitmask = KILLER + STALKER,
	diet = HERBIVORE,

	templates = {},
	lootgroups = {},
	weapons = {""},
	attacks = {}
}

CreatureTemplates:addCreatureTemplate(dark_adept, "dark_adept")