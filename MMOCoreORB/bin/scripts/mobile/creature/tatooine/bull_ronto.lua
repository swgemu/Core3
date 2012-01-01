bull_ronto = Creature:new {
	objectName = "@mob/creature_names:bull_ronto",
	socialGroup = "Ronto",
	pvpFaction = "",
	faction = "",
	level = 23,
	chanceHit = 0.34,
	damageMin = 200,
	damageMax = 210,
	baseXp = 2219,
	baseHAM = 5400,
	baseHAMmax = 6600,
	armor = 0,
	resists = {15,25,-1,50,40,-1,10,-1,-1},
	meatType = "meat_herbivore",
	meatAmount = 465,
	hideType = "hide_leathery",
	hideAmount = 320,
	boneType = "bone_mammal",
	boneAmount = 200,
	milk = 0,
	tamingChance = 0.25,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK,
	optionsBitmask = 128,
	diet = HERBIVORE,

	templates = {"object/mobile/ronto.iff"},
	lootgroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"posturedownattack","postureDownChance=50"},
		{"stunattack","stunChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(bull_ronto, "bull_ronto")