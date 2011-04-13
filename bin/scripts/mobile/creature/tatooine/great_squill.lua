great_squill = Creature:new {
	objectName = "@mob/creature_names:squill_great",
	socialGroup = "Squill",
	pvpFaction = "",
	faction = "",
	level = 20,
	chanceHit = 0.330000,
	damageMin = 200,
	damageMax = 210,
	baseXp = 1609,
	baseHAM = 6000,
	baseHAMmax = 6000,
	armor = 0,
	resists = {10,10,0,0,-1,-1,0,-1,-1},
	meatType = "meat_carnivore",
	meatAmount = 6,
	hideType = "hide_leathery",
	hideAmount = 6,
	boneType = "bone_mammal",
	boneAmount = 5,
	milk = 0,
	tamingChance = 0.050000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = STALKER + PACK,
	diet = CARNIVORE,

	templates = {"object/mobile/squill.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"stunattack","stunChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(great_squill, "great_squill")