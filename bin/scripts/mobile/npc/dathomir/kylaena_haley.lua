kylaena_haley = Creature:new {
	objectName = "@mob/creature_names:kylaena_haley",
	socialGroup = "Sith Shadow",
	pvpFaction = "Sith Shadow",
	faction = "",
	level = 103,
	chanceHit = 0.900000,
	damageMin = 720,
	damageMax = 1150,
	baseXp = 9801,
	baseHAM = 15900,
	baseHAMmax = 19400,
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
	lootgroups = {},
	weapons = {"mixed_force_weapons"},
	attacks = {}
}

CreatureTemplates:addCreatureTemplate(kylaena_haley, "kylaena_haley")