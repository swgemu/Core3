lesser_dewback = Creature:new {
	objectName = "@mob/creature_names:lesser_dewback",
	socialGroup = "self",
	pvpFaction = "",
	faction = "",
	level = 9,
	chanceHit = 0.27,
	damageMin = 50,
	damageMax = 55,
	baseXp = 292,
	baseHAM = 810,
	baseHAMmax = 990,
	armor = 0,
	resists = {15,0,10,0,-1,-1,-1,-1,-1},
	meatType = "meat_reptilian",
	meatAmount = 175,
	hideType = "hide_leathery",
	hideAmount = 125,
	boneType = "bone_mammal",
	boneAmount = 100,
	milk = 0,
	tamingChance = 0.25,
	ferocity = 5,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/dewback.iff"},
	lootgroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"stunattack","stunChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(lesser_dewback, "lesser_dewback")