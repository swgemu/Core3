sith_shadow_outlaw = Creature:new {
	objectName = "Sith Shadow outlaw",
	socialGroup = "Sith Shadow",
	pvpFaction = "s.s. non-aggro",
	faction = "",
	level = 68,
	chanceHit = 0.600000,
	damageMin = 445,
	damageMax = 600,
	baseXp = 628,
	baseHAM = 11000,
	baseHAMmax = 13500,
	armor = 0,
	resists = {65,65,55,60,60,80,80,80,-1},
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

CreatureTemplates:addCreatureTemplate(sith_shadow_outlaw, "sith_shadow_outlaw")