variegated_womp_rat = Creature:new {
	objectName = "@mob/creature_names:variegated_womprat",
	socialGroup = "self",
	pvpFaction = "",
	faction = "",
	level = 14,
	chanceHit = 0.3,
	damageMin = 160,
	damageMax = 170,
	baseXp = 609,
	baseHAM = 1500,
	baseHAMmax = 1900,
	armor = 0,
	resists = {0,0,15,0,0,0,0,0,-1},
	meatType = "meat_wild",
	meatAmount = 3,
	hideType = "hide_leathery",
	hideAmount = 3,
	boneType = "bone_mammal",
	boneAmount = 2,
	milk = 0,
	tamingChance = 0.25,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = HERD,
	optionsBitmask = 0,
	diet = CARNIVORE,

	templates = {"object/mobile/womp_rat.iff"},
	lootgroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"stunattack","stunChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(variegated_womp_rat, "variegated_womp_rat")