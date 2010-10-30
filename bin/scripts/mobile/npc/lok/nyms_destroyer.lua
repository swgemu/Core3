nyms_destroyer = Creature:new {
	objectName = "Nym's destroyer",
	socialGroup = "Nym",
	pvpFaction = "Nym",
	faction = "",
	level = 40,
	chanceHit = 0.430000,
	damageMin = 355,
	damageMax = 420,
	baseXp = 4006,
	baseHAM = 9100,
	baseHAMmax = 11100,
	armor = 0,
	resists = {40,40,0,0,60,-1,-1,-1,-1},
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
	weapons = {"rebel_weapons_medium"},
	attacks = {}
}

CreatureTemplates:addCreatureTemplate(nyms_destroyer, "nyms_destroyer")