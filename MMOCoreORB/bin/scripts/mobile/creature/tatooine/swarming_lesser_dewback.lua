swarming_lesser_dewback = Creature:new {
	objectName = "@mob/creature_names:swarming_lesser_dewback",
	socialGroup = "self",
	pvpFaction = "",
	faction = "",
	level = 15,
	chanceHit = 0.310000,
	damageMin = 140,
	damageMax = 150,
	baseXp = 831,
	baseHAM = 3900,
	baseHAMmax = 3900,
	armor = 0,
	resists = {15,0,10,0,-1,-1,-1,-1,-1},
	meatType = "meat_reptilian",
	meatAmount = 175,
	hideType = "hide_leathery",
	hideAmount = 125,
	boneType = "bone_mammal",
	boneAmount = 100,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = STALKER + PACK,
	diet = CARNIVORE,

	templates = {"object/mobile/swarming_lesser_dewback.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"stunattack","stunChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(swarming_lesser_dewback, "swarming_lesser_dewback")