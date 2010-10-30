elder_snorbal_male = Creature:new {
	objectName = "@mob/creature_names:elder_snorbal_male",
	socialGroup = "Snorbalmale",
	pvpFaction = "",
	faction = "",
	level = 37,
	chanceHit = 0.420000,
	damageMin = 330,
	damageMax = 370,
	baseXp = 3642,
	baseHAM = 10000,
	baseHAMmax = 10000,
	armor = 0,
	resists = {45,40,0,-1,-1,-1,-1,0,-1},
	meatType = "meat_herbivore",
	meatAmount = 570,
	hideType = "hide_leathery",
	hideAmount = 455,
	boneType = "bone_mammal",
	boneAmount = 420,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK + HERD,
	diet = HERBIVORE,

	templates = {"object/mobile/elder_snorbal_male.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"posturedownattack","postureDownChance=50"},
		{"stunattack","stunChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(elder_snorbal_male, "elder_snorbal_male")