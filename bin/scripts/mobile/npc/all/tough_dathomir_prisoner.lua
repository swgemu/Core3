tough_dathomir_prisoner = Creature:new {
	objectName = "tough Dathomir prisoner",
	socialGroup = "Prisoner",
	pvpFaction = "",
	faction = "",
	level = 27,
	chanceHit = 0.270000,
	damageMin = 260,
	damageMax = 270,
	baseXp = 2637,
	baseHAM = 8100,
	baseHAMmax = 9900,
	armor = 0,
	resists = {0,0,0,0,0,0,0,-1,-1},
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
	weapons = {""},
	attacks = {}
}

CreatureTemplates:addCreatureTemplate(tough_dathomir_prisoner, "tough_dathomir_prisoner")