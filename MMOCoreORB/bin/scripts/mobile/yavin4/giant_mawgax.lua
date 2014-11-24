giant_mawgax = Creature:new {
	objectName = "@mob/creature_names:giant_mawgax",
	socialGroup = "mawgax",
	pvpFaction = "",
	faction = "",
	level = 32,
	chanceHit = 0.4,
	damageMin = 305,
	damageMax = 320,
	baseXp = 3188,
	baseHAM = 8600,
	baseHAMmax = 10500,
	armor = 0,
	resists = {20,130,20,-1,130,-1,20,20,-1},
	meatType = "meat_domesticated",
	meatAmount = 130,
	hideType = "hide_leathery",
	hideAmount = 85,
	boneType = "bone_avian",
	boneAmount = 70,
	milk = 0,
	tamingChance = 0.2,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK + HERD,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/giant_mawgax.iff"},
	controlDeviceTemplate = "object/intangible/pet/mawgax_hue.iff",
	scale = 1.4,
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"stunattack","stunChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(giant_mawgax, "giant_mawgax")
