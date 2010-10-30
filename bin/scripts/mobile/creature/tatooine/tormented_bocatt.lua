tormented_bocatt = Creature:new {
	objectName = "@mob/creature_names:bocatt_tormented",
	socialGroup = "Bocatt",
	pvpFaction = "",
	faction = "",
	level = 26,
	chanceHit = 0.360000,
	damageMin = 250,
	damageMax = 260,
	baseXp = 2637,
	baseHAM = 9000,
	baseHAMmax = 9000,
	armor = 0,
	resists = {0,0,-1,-1,50,50,-1,-1,-1},
	meatType = "meat_reptilian",
	meatAmount = 100,
	hideType = "hide_leathery",
	hideAmount = 60,
	boneType = "bone_mammal",
	boneAmount = 35,
	milk = 0,
	tamingChance = 0.050000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = STALKER + PACK,
	diet = CARNIVORE,

	templates = {"object/mobile/bocatt.iff"},
	lootgroups = {},
	weapons = {"creature_spit_small_yellow"},
	attacks = {
		{"posturedownattack","postureDownChance=50"},
		{"stunattack","stunChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(tormented_bocatt, "tormented_bocatt")