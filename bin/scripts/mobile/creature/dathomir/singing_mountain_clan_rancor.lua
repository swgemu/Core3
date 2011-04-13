singing_mountain_clan_rancor = Creature:new {
	objectName = "singing mountain clan rancor",
	socialGroup = "Mountain Clan",
	pvpFaction = "",
	faction = "",
	level = 55,
	chanceHit = 0.500000,
	damageMin = 370,
	damageMax = 450,
	baseXp = 5281,
	baseHAM = 12000,
	baseHAMmax = 12000,
	armor = 0,
	resists = {30,60,0,100,100,100,0,0,-1},
	meatType = "meat_carnivore",
	meatAmount = 620,
	hideType = "hide_leathery",
	hideAmount = 510,
	boneType = "bone_mammal",
	boneAmount = 480,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = STALKER + PACK,
	diet = CARNIVORE,

	templates = {"object/mobile/rancor.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"intimidationattack","intimidationChance=50"},
		{"intimidationattack","intimidationChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(singing_mountain_clan_rancor, "singing_mountain_clan_rancor")