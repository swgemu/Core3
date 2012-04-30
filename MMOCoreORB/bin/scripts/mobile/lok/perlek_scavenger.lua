perlek_scavenger = Creature:new {
	objectName = "@mob/creature_names:perlek_scavanger",
	socialGroup = "Perlek",
	pvpFaction = "",
	faction = "",
	level = 15,
	chanceHit = 0.31,
	damageMin = 160,
	damageMax = 170,
	baseXp = 831,
	baseHAM = 2400,
	baseHAMmax = 3000,
	armor = 0,
	resists = {5,5,5,30,30,-1,-1,-1,-1},
	meatType = "meat_avian",
	meatAmount = 275,
	hideType = "hide_leathery",
	hideAmount = 115,
	boneType = "bone_avian",
	boneAmount = 185,
	milk = 0,
	tamingChance = 0.25,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = PACK + STALKER,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/perlek.iff"},
	lootGroups = {},
	weapons = {"creature_spit_small_yellow"},
	conversationTemplate = "",
	attacks = {
		{"stunattack","stunChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(perlek_scavenger, "perlek_scavenger")