singing_mountain_clan_slave = Creature:new {
	objectName = "Singing Mountain clan slave",
	socialGroup = "Mtn. Clan",
	pvpFaction = "Mtn. Clan",
	faction = "",
	level = 10,
	chanceHit = 0.280000,
	damageMin = 130,
	damageMax = 140,
	baseXp = 292,
	baseHAM = 405,
	baseHAMmax = 495,
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
	pvpBitmask = ATTACKABLE + AGGRESSIVE,
	creatureBitmask = NONE,
	diet = HERBIVORE,

	templates = {},
	lootgroups = {},
	weapons = {""},
	attacks = {}
}

CreatureTemplates:addCreatureTemplate(singing_mountain_clan_slave, "singing_mountain_clan_slave")