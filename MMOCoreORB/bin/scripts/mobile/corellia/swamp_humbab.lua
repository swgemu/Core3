swamp_humbab = Creature:new {
	objectName = "@mob/creature_names:swamp_humbaba",
	socialGroup = "humbaba",
	pvpFaction = "",
	faction = "",
	level = 19,
	chanceHit = 0.33,
	damageMin = 160,
	damageMax = 170,
	baseXp = 1426,
	baseHAM = 5000,
	baseHAMmax = 6100,
	armor = 0,
	resists = {10,10,10,10,10,10,10,-1,-1},
	meatType = "meat_carnivore",
	meatAmount = 250,
	hideType = "hide_leathery",
	hideAmount = 150,
	boneType = "bone_mammal",
	boneAmount = 105,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK + HERD,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/savage_humbaba.iff"},
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"stunattack","stunChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(swamp_humbab, "swamp_humbab")