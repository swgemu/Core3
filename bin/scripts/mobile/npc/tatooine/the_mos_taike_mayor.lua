the_mos_taike_mayor = Creature:new {
	objectName = "the Mos Taike mayor",
	socialGroup = "Townsperson",
	pvpFaction = "Townsperson",
	faction = "",
	level = 21,
	chanceHit = 0.330000,
	damageMin = 190,
	damageMax = 200,
	baseXp = 2006,
	baseHAM = 5900,
	baseHAMmax = 7200,
	armor = 0,
	resists = {20,20,-1,0,0,-1,0,-1,-1},
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
	weapons = {"pirate_weapons_light"},
	attacks = {}
}

CreatureTemplates:addCreatureTemplate(the_mos_taike_mayor, "the_mos_taike_mayor")