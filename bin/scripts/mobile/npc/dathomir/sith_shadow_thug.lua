sith_shadow_thug = Creature:new {
	objectName = "Sith Shadow thug",
	socialGroup = "Sith Shadow",
	pvpFaction = "s.s. non-aggro",
	faction = "",
	level = 127,
	chanceHit = 4.000000,
	damageMin = 770,
	damageMax = 1250,
	baseXp = 2503,
	baseHAM = 44300,
	baseHAMmax = 54300,
	armor = 0,
	resists = {75,85,80,65,80,80,80,80,-1},
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
	weapons = {"pirate_weapons_heavy"},
	attacks = {}
}

CreatureTemplates:addCreatureTemplate(sith_shadow_thug, "sith_shadow_thug")