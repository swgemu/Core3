elder_snorbal_male = Creature:new {
	objectName = "@mob/creature_names:elder_snorbal_male",
	socialGroup = "snorbal",
	pvpFaction = "",
	faction = "",
	level = 37,
	chanceHit = 0.42,
	damageMin = 330,
	damageMax = 370,
	baseXp = 3642,
	baseHAM = 9000,
	baseHAMmax = 11000,
	armor = 0,
	resists = {145,140,25,-1,-1,-1,-1,25,-1},
	meatType = "meat_herbivore",
	meatAmount = 570,
	hideType = "hide_leathery",
	hideAmount = 455,
	boneType = "bone_mammal",
	boneAmount = 420,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK + HERD,
	optionsBitmask = 128,
	diet = HERBIVORE,

	templates = {"object/mobile/elder_snorbal_male.iff"},
	scale = 1.2,
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"posturedownattack","postureDownChance=50"},
		{"stunattack","stunChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(elder_snorbal_male, "elder_snorbal_male")
