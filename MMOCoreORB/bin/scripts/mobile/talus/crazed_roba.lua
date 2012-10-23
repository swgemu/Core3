crazed_roba = Creature:new {
	objectName = "@mob/creature_names:crazed_roba",
	socialGroup = "self",
	pvpFaction = "",
	faction = "",
	level = 12,
	chanceHit = 0.29,
	damageMin = 140,
	damageMax = 150,
	baseXp = 609,
	baseHAM = 1000,
	baseHAMmax = 1200,
	armor = 0,
	resists = {0,0,0,0,0,0,0,-1,-1},
	meatType = "meat_carnivore",
	meatAmount = 12,
	hideType = "hide_leathery",
	hideAmount = 18,
	boneType = "bone_mammal",
	boneAmount = 12,
	milk = 0,
	tamingChance = 0.25,
	ferocity = 2,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK + KILLER,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/roba_hue.iff"},
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"stunattack","stunChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(crazed_roba, "crazed_roba")