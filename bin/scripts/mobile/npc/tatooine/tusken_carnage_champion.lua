tusken_carnage_champion = Creature:new {
	objectName = "Tusken carnage champion",
	socialGroup = "Tusken Raider",
	pvpFaction = "Tusken Raider",
	faction = "",
	level = 116,
	chanceHit = 3.850000,
	damageMin = 750,
	damageMax = 1210,
	baseXp = 11015,
	baseHAM = 43000,
	baseHAMmax = 53000,
	armor = 0,
	resists = {65,40,0,30,-1,30,-1,-1,-1},
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
	creatureBitmask = PACK + KILLER + HERD,
	diet = HERBIVORE,

	templates = {},
	lootgroups = {},
	weapons = {"tusken_weapons"},
	attacks = {}
}

CreatureTemplates:addCreatureTemplate(tusken_carnage_champion, "tusken_carnage_champion")