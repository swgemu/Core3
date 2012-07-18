female_mawgax = Creature:new {
	objectName = "@mob/creature_names:mawgax_female",
	socialGroup = "mawgax",
	pvpFaction = "",
	faction = "",
	level = 23,
	chanceHit = 0.35,
	damageMin = 240,
	damageMax = 250,
	baseXp = 2219,
	baseHAM = 5900,
	baseHAMmax = 7200,
	armor = 0,
	resists = {15,15,10,-1,10,10,-1,-1,-1},
	meatType = "meat_carnivore",
	meatAmount = 115,
	hideType = "hide_leathery",
	hideAmount = 72,
	boneType = "bone_avian",
	boneAmount = 52,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK + HERD,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/mawgax_hue.iff"},
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"stunattack","stunChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(female_mawgax, "female_mawgax")