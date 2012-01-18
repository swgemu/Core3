singing_mountain_clan_rancor = Creature:new {
	objectName = "@mob/creature_names:singing_mountain_clan_rancor",
	socialGroup = "Mountain Clan",
	pvpFaction = "",
	faction = "",
	level = 55,
	chanceHit = 0.5,
	damageMin = 370,
	damageMax = 450,
	baseXp = 5281,
	baseHAM = 11000,
	baseHAMmax = 13000,
	armor = 1,
	resists = {30,60,5,100,100,100,5,5,-1},
	meatType = "meat_carnivore",
	meatAmount = 620,
	hideType = "hide_leathery",
	hideAmount = 510,
	boneType = "bone_mammal",
	boneAmount = 480,
	milk = 0,
	tamingChance = 0,
	ferocity = 10,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = PACK + STALKER,
	optionsBitmask = 128,
	diet = CARNIVORE,
	lootChance = 4200000,

	templates = {"object/mobile/rancor.iff"},
	lootgroups = {
		{group = "rancor_common", chance = 3300000},
		{group = "pistols", chance = 3300000},
		{group = "rifles", chance = 3400000}
	},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"intimidationattack","intimidationChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(singing_mountain_clan_rancor, "singing_mountain_clan_rancor")