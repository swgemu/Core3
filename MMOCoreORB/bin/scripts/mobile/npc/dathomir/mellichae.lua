mellichae = Creature:new {
	objectName = "@mob/creature_names:mellichae",
	socialGroup = "Sith Shadow",
	pvpFaction = "Sith Shadow",
	faction = "",
	level = 140,
	chanceHit = 4.750000,
	damageMin = 945,
	damageMax = 1600,
	baseXp = 13273,
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
	pvpBitmask = ATTACKABLE,
	creatureBitmask = KILLER,
	diet = HERBIVORE,

	templates = {},
	lootGroups = {},
	weapons = {"dark_jedi_weapons"},
	attacks = {}
}

CreatureTemplates:addCreatureTemplate(mellichae, "mellichae")