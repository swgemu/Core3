sith_shadow_mercenary = Creature:new {
	objectName = "Sith Shadow mercenary",
	socialGroup = "Sith Shadow",
	pvpFaction = "s.s. non-aggro",
	faction = "",
	level = 148,
	chanceHit = 7.000000,
	damageMin = 895,
	damageMax = 1500,
	baseXp = 3327,
	baseHAM = 679000,
	baseHAMmax = 83000,
	armor = 0,
	resists = {80,90,85,85,70,85,85,85,-1},
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

CreatureTemplates:addCreatureTemplate(sith_shadow_mercenary, "sith_shadow_mercenary")