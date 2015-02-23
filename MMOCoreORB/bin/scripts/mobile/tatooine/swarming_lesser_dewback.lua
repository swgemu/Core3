swarming_lesser_dewback = Creature:new {
	objectName = "@mob/creature_names:swarming_lesser_dewback",
	socialGroup = "self",
	faction = "",
	level = 15,
	chanceHit = 0.31,
	damageMin = 140,
	damageMax = 150,
	baseXp = 831,
	baseHAM = 3500,
	baseHAMmax = 4300,
	armor = 0,
	resists = {115,5,110,5,-1,-1,-1,-1,-1},
	meatType = "meat_reptilian",
	meatAmount = 175,
	hideType = "hide_leathery",
	hideAmount = 125,
	boneType = "bone_mammal",
	boneAmount = 100,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK + STALKER,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/swarming_lesser_dewback.iff"},
	scale = 0.9,
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"stunattack",""}
	}
}

CreatureTemplates:addCreatureTemplate(swarming_lesser_dewback, "swarming_lesser_dewback")
