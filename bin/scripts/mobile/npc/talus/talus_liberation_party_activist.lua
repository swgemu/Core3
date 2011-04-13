talus_liberation_party_activist = Creature:new {
	objectName = "Talus Liberation Party activist",
	socialGroup = "Liberat. Party",
	pvpFaction = "Liberat. Party",
	faction = "",
	level = 21,
	chanceHit = 0.340000,
	damageMin = 200,
	damageMax = 210,
	baseXp = 1803,
	baseHAM = 5400,
	baseHAMmax = 6600,
	armor = 0,
	resists = {0,25,0,-1,0,-1,-1,-1,-1},
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
	creatureBitmask = PACK + HERD,
	diet = HERBIVORE,

	templates = {},
	lootgroups = {},
	weapons = {"pirate_weapons_heavy"},
	attacks = {}
}

CreatureTemplates:addCreatureTemplate(talus_liberation_party_activist, "talus_liberation_party_activist")