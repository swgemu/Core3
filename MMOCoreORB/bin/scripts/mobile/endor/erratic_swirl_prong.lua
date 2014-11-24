erratic_swirl_prong = Creature:new {
	objectName = "@mob/creature_names:erratic_swirl_prong",
	socialGroup = "prong",
	pvpFaction = "",
	faction = "",
	level = 27,
	chanceHit = 0.36,
	damageMin = 240,
	damageMax = 250,
	baseXp = 2730,
	baseHAM = 7200,
	baseHAMmax = 8800,
	armor = 0,
	resists = {125,135,15,150,150,-1,-1,-1,-1},
	meatType = "meat_herbivore",
	meatAmount = 150,
	hideType = "hide_leathery",
	hideAmount = 110,
	boneType = "bone_mammal",
	boneAmount = 95,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK + HERD,
	optionsBitmask = 128,
	diet = HERBIVORE,

	templates = {"object/mobile/swirl_prong_hue.iff"},
	scale = 1.05,
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"intimidationattack","intimidationChance=50"},
		{"posturedownattack","postureDownChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(erratic_swirl_prong, "erratic_swirl_prong")
