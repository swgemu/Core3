stormtrooper_dewback = Creature:new {
	objectName = "@mob/creature_names:stormtrooper_dewback",
	socialGroup = "Imperial",
	pvpFaction = "",
	faction = "",
	level = 29,
	chanceHit = 0.380000,
	damageMin = 280,
	damageMax = 290,
	baseXp = 2914,
	baseHAM = 9200,
	baseHAMmax = 9200,
	armor = 0,
	resists = {40,20,0,40,-1,-1,-1,-1,-1},
	meatType = "meat_reptilian",
	meatAmount = 360,
	hideType = "hide_leathery",
	hideAmount = 275,
	boneType = "bone_mammal",
	boneAmount = 250,
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
		{"dizzyattack","dizzyChance=50"},
		{"stunattack","stunChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(stormtrooper_dewback, "stormtrooper_dewback")