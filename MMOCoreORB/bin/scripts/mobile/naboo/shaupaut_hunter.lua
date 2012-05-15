shaupaut_hunter = Creature:new {
	objectName = "@mob/creature_names:shaupaut_hunter",
	socialGroup = "shaupaut",
	pvpFaction = "",
	faction = "",
	level = 22,
	chanceHit = 0.34,
	damageMin = 200,
	damageMax = 210,
	baseXp = 2006,
	baseHAM = 5400,
	baseHAMmax = 6600,
	armor = 0,
	resists = {20,20,10,-1,10,-1,10,-1,-1},
	meatType = "meat_carnivore",
	meatAmount = 10,
	hideType = "hide_bristley",
	hideAmount = 6,
	boneType = "bone_mammal",
	boneAmount = 6,
	milk = 0,
	tamingChance = 0.25,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = STALKER,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/shaupaut.iff"},
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"blindattack","blindChance=50"},
		{"stunattack","stunChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(shaupaut_hunter, "shaupaut_hunter")