singing_mountain_clan_councilwoman = Creature:new {
	objectName = "Singing Mountain clan councilwoman",
	socialGroup = "Mtn. Clan",
	pvpFaction = "Mtn. Clan",
	faction = "",
	level = 253,
	chanceHit = 23.500000,
	damageMin = 1395,
	damageMax = 2500,
	baseXp = 24180,
	baseHAM = 261000,
	baseHAMmax = 320000,
	armor = 0,
	resists = {100,0,0,100,100,100,100,100,-1},
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
	weapons = {"mixed_force_weapons"},
	attacks = {}
}

CreatureTemplates:addCreatureTemplate(singing_mountain_clan_councilwoman, "singing_mountain_clan_councilwoman")