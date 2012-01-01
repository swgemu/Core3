young_malkloc_plainswalker = Creature:new {
	objectName = "@mob/creature_names:young_malkloc_plainswalker",
	socialGroup = "Malkloc PW",
	pvpFaction = "",
	faction = "",
	level = 55,
	chanceHit = 0.5,
	damageMin = 370,
	damageMax = 450,
	baseXp = 5281,
	baseHAM = 12000,
	baseHAMmax = 14000,
	armor = 1,
	resists = {0,0,0,0,0,0,0,0,0},
	meatType = "meat_herbivore",
	meatAmount = 1500,
	hideType = "hide_leathery",
	hideAmount = 1350,
	boneType = "bone_mammal",
	boneAmount = 1100,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK + HERD,
	optionsBitmask = 0,
	diet = HERBIVORE,

	templates = {"object/mobile/young_malkloc.iff"},
	lootgroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"posturedownattack","postureDownChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(young_malkloc_plainswalker, "young_malkloc_plainswalker")