furious_ronto = Creature:new {
	objectName = "@mob/creature_names:ronto_furious",
	socialGroup = "Ronto",
	pvpFaction = "",
	faction = "",
	level = 27,
	chanceHit = 0.370000,
	damageMin = 250,
	damageMax = 260,
	baseXp = 2730,
	baseHAM = 9100,
	baseHAMmax = 9100,
	armor = 0,
	resists = {15,25,-1,50,40,-1,0,-1,-1},
	meatType = "meat_herbivore",
	meatAmount = 465,
	hideType = "hide_leathery",
	hideAmount = 320,
	boneType = "bone_mammal",
	boneAmount = 200,
	milk = 0,
	tamingChance = 0.050000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = PACK,
	diet = CARNIVORE,

	templates = {"object/mobile/ronto.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"posturedownattack","postureDownChance=50"},
		{"stunattack","stunChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(furious_ronto, "furious_ronto")