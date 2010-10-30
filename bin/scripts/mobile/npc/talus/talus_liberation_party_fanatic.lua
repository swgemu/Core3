talus_liberation_party_fanatic = Creature:new {
	objectName = "Talus Liberation Party fanatic",
	socialGroup = "Liberal Party",
	pvpFaction = "Liberal Party",
	faction = "",
	level = 17,
	chanceHit = 0.320000,
	damageMin = 170,
	damageMax = 180,
	baseXp = 1102,
	baseHAM = 2400,
	baseHAMmax = 3000,
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
	creatureBitmask = PACK + HERD,
	diet = HERBIVORE,

	templates = {},
	lootgroups = {},
	weapons = {"pirate_weapons_medium"},
	attacks = {}
}

CreatureTemplates:addCreatureTemplate(talus_liberation_party_fanatic, "talus_liberation_party_fanatic")