lesser_dewback = Creature:new {
	objectName = "@mob/creature_names:lesser_dewback",
	socialGroup = "self",
	pvpFaction = "",
	faction = "",
	level = 9,
	chanceHit = 0.270000,
	damageMin = 50,
	damageMax = 55,
	baseXp = 292,
	baseHAM = 900,
	baseHAMmax = 900,
	armor = 0,
	resists = {15,0,10,0,-1,-1,-1,-1,-1},
	meatType = "meat_reptilian",
	meatAmount = 175,
	hideType = "hide_leathery",
	hideAmount = 125,
	boneType = "bone_mammal",
	boneAmount = 100,
	milk = 0,
	tamingChance = 0.250000,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK,
	diet = CARNIVORE,

	templates = {"object/mobile/dewback.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"stunattack","stunChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(lesser_dewback, "lesser_dewback")