teraud_loyalist_cyborg = Creature:new {
	objectName = "Teraud loyalist cyborg",
	socialGroup = "Warren Teraud",
	pvpFaction = "Warren Teraud",
	faction = "",
	level = 38,
	chanceHit = 0.430000,
	damageMin = 335,
	damageMax = 380,
	baseXp = 3824,
	baseHAM = 9100,
	baseHAMmax = 11100,
	armor = 0,
	resists = {40,50,0,-1,-1,-1,-1,-1,-1},
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
	weapons = {"pirate_weapons_medium"},
	attacks = {}
}

CreatureTemplates:addCreatureTemplate(teraud_loyalist_cyborg, "teraud_loyalist_cyborg")