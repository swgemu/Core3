mountain_dewback = Creature:new {
	objectName = "@mob/creature_names:mountain_dewback",
	socialGroup = "self",
	pvpFaction = "",
	faction = "",
	level = 20,
	chanceHit = 0.320000,
	damageMin = 190,
	damageMax = 200,
	baseXp = 1609,
	baseHAM = 5550,
	baseHAMmax = 5550,
	armor = 0,
	resists = {20,0,0,40,40,-1,-1,-1,-1},
	meatType = "meat_reptilian",
	meatAmount = 330,
	hideType = "hide_leathery",
	hideAmount = 240,
	boneType = "bone_mammal",
	boneAmount = 170,
	milk = 0,
	tamingChance = 0.250000,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK,
	diet = CARNIVORE,

	templates = {"object/mobile/mountain_dewback.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"knockdownattack","knockdownChance=50"},
		{"dizzyattack","dizzyChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(mountain_dewback, "mountain_dewback")