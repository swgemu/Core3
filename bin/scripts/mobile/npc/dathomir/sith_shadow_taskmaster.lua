sith_shadow_taskmaster = Creature:new {
	objectName = "Sith Shadow taskmaster",
	socialGroup = "Sith Shadow",
	pvpFaction = "Sith Shadow",
	faction = "",
	level = 87,
	chanceHit = 0.750000,
	damageMin = 620,
	damageMax = 950,
	baseXp = 8315,
	baseHAM = 12400,
	baseHAMmax = 15200,
	armor = 0,
	resists = {70,70,70,70,70,70,70,70,-1},
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
	weapons = {"pirate_weapons_heavy"},
	attacks = {}
}

CreatureTemplates:addCreatureTemplate(sith_shadow_taskmaster, "sith_shadow_taskmaster")