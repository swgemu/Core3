mawgax_youth = Creature:new {
	objectName = "@mob/creature_names:mawgax_youth",
	socialGroup = "mawgax",
	faction = "",
	level = 21,
	chanceHit = 0.34,
	damageMin = 200,
	damageMax = 210,
	baseXp = 1803,
	baseHAM = 5400,
	baseHAMmax = 6600,
	armor = 0,
	resists = {10,10,10,10,10,10,10,-1,-1},
	meatType = "meat_domesticated",
	meatAmount = 650,
	hideType = "hide_leathery",
	hideAmount = 60,
	boneType = "bone_avian",
	boneAmount = 45,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK + HERD,
	optionsBitmask = AIENABLED,
	diet = CARNIVORE,

	templates = {"object/mobile/mawgax_youth.iff"},
	scale = 0.75,
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(mawgax_youth, "mawgax_youth")
