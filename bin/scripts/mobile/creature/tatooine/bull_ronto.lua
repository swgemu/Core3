bull_ronto = Creature:new {
	objectName = "@mob/creature_names:ronto_male",
	socialGroup = "Ronto",
	pvpFaction = "",
	faction = "",
	level = 23,
	chanceHit = 0.340000,
	damageMin = 200,
	damageMax = 210,
	baseXp = 2219,
	baseHAM = 6000,
	baseHAMmax = 6000,
	armor = 0,
	resists = {15,25,-1,50,40,-1,0,-1,-1},
	meatType = "meat_herbivore",
	meatAmount = 465,
	hideType = "hide_leathery",
	hideAmount = 320,
	boneType = "bone_mammal",
	boneAmount = 200,
	milk = 0,
	tamingChance = 0.250000,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK,
	diet = HERBIVORE,

	templates = {"object/mobile/ronto.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"posturedownattack","postureDownChance=50"},
		{"stunattack","stunChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(bull_ronto, "bull_ronto")