singing_mountain_clan_guardian = Creature:new {
	objectName = "Singing Mountain clan guardian",
	socialGroup = "Mtn. Clan",
	pvpFaction = "Mtn. Clan",
	faction = "",
	level = 156,
	chanceHit = 8.500000,
	damageMin = 895,
	damageMax = 1500,
	baseXp = 14789,
	baseHAM = 81000,
	baseHAMmax = 99000,
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

CreatureTemplates:addCreatureTemplate(singing_mountain_clan_guardian, "singing_mountain_clan_guardian")