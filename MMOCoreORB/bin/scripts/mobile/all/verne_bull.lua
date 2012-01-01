verne_bull = Creature:new {
	objectName = "@mob/creature_names:verne_bull",
	socialGroup = "Verne",
	pvpFaction = "",
	faction = "",
	level = 19,
	chanceHit = 0.32,
	damageMin = 170,
	damageMax = 180,
	baseXp = 1426,
	baseHAM = 4500,
	baseHAMmax = 5500,
	armor = 0,
	resists = {0,0,0,0,0,0,0,0,0},
	meatType = "meat_wild",
	meatAmount = 110,
	hideType = "hide_leathery",
	hideAmount = 95,
	boneType = "bone_mammal",
	boneAmount = 85,
	milk = 1,
	tamingChance = 0.25,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = PACK + HERD,
	optionsBitmask = 0,
	diet = HERBIVORE,

	templates = {"object/mobile/verne_bull.iff"},
	lootgroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"stunattack","stunChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(verne_bull, "verne_bull")