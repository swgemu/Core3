dewback = Creature:new {
	objectName = "@monster_name:dewback",
	socialGroup = "Dewback",
	pvpFaction = "",
	faction = "",
	level = 19,
	chanceHit = 0.320000,
	damageMin = 170,
	damageMax = 180,
	range = 0,
	baseXp = 1426,
	baseHAM = 4550,
	armor = 0,
	resists = {20,0,10,0,-1,-1,-1,-1,-1},
	meatType = "meat_reptil",
	meatAmount = 350,
	hideType = "hide_leathery",
	hideAmount = 275,
	boneType = "bone_mammal",
	boneAmount = 200,
	milk = 0,
	tamingChance = 0.250000,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK,
	diet = HERBIVORE,

	templates = {},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"stunattack","stunChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(dewback, "dewback")
