grizzled_dewback = Creature:new {
	objectName = "@mob/creature_names:grizzled_dewback",
	socialGroup = "Dewback",
	pvpFaction = "",
	faction = "",
	level = 27,
	chanceHit = 0.350000,
	damageMin = 270,
	damageMax = 280,
	baseXp = 2730,
	baseHAM = 8550,
	baseHAMmax = 8550,
	armor = 0,
	resists = {35,20,0,40,-1,-1,-1,-1,-1},
	meatType = "meat_reptilian",
	meatAmount = 365,
	hideType = "hide_leathery",
	hideAmount = 285,
	boneType = "bone_mammal",
	boneAmount = 210,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK,
	diet = CARNIVORE,

	templates = {"object/mobile/dewback.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"knockdownattack","knockdownChance=50"},
		{"dizzyattack","dizzyChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(grizzled_dewback, "grizzled_dewback")