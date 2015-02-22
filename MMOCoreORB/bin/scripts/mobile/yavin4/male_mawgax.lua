male_mawgax = Creature:new {
	objectName = "@mob/creature_names:mawgax_male",
	socialGroup = "mawgax",
	faction = "",
	level = 25,
	chanceHit = 0.36,
	damageMin = 240,
	damageMax = 250,
	baseXp = 2543,
	baseHAM = 7200,
	baseHAMmax = 8800,
	armor = 0,
	resists = {120,120,15,-1,15,15,130,-1,-1},
	meatType = "meat_domesticated",
	meatAmount = 100,
	hideType = "hide_leathery",
	hideAmount = 70,
	boneType = "bone_avian",
	boneAmount = 55,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK + HERD,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/mawgax.iff"},
	scale = 1.05,
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"",""},
		{"intimidationattack","intimidationChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(male_mawgax, "male_mawgax")
