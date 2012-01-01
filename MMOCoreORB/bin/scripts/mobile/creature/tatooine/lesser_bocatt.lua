lesser_bocatt = Creature:new {
	objectName = "@mob/creature_names:lesser_bocatt",
	socialGroup = "Bocatt",
	pvpFaction = "",
	faction = "",
	level = 15,
	chanceHit = 0.3,
	damageMin = 150,
	damageMax = 160,
	baseXp = 831,
	baseHAM = 2000,
	baseHAMmax = 2400,
	armor = 0,
	resists = {0,0,0,0,15,15,-1,-1,-1},
	meatType = "meat_reptilian",
	meatAmount = 100,
	hideType = "hide_leathery",
	hideAmount = 60,
	boneType = "bone_mammal",
	boneAmount = 35,
	milk = 0,
	tamingChance = 0.25,
	ferocity = 7,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = PACK + STALKER,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/bocatt.iff"},
	lootgroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"posturedownattack","postureDownChance=50"},
		{"stunattack","stunChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(lesser_bocatt, "lesser_bocatt")