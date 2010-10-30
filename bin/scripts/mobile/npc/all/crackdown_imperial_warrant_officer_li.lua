crackdown_imperial_warrant_officer_li = Creature:new {
	objectName = "Crackdown Imperial Warrant Officer li",
	socialGroup = "Imperial",
	pvpFaction = "Imperial",
	faction = "",
	level = 1,
	chanceHit = 0.320000,
	damageMin = 170,
	damageMax = 180,
	baseXp = 45,
	baseHAM = 4100,
	baseHAMmax = 5000,
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
	creatureBitmask = PACK + KILLER,
	diet = HERBIVORE,

	templates = {},
	lootgroups = {},
	weapons = {"imperial_weapons_medium"},
	attacks = {}
}

CreatureTemplates:addCreatureTemplate(crackdown_imperial_warrant_officer_li, "crackdown_imperial_warrant_officer_li")