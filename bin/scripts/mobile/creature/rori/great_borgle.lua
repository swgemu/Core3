great_borgle = Creature:new {
	objectName = "@mob/creature_names:great_borgle",
	socialGroup = "Borgle",
	pvpFaction = "",
	faction = "",
	level = 14,
	chanceHit = 0.300000,
	damageMin = 140,
	damageMax = 150,
	baseXp = 714,
	baseHAM = 2700,
	baseHAMmax = 2700,
	armor = 0,
	resists = {0,0,0,0,0,0,0,-1,-1},
	meatType = "meat_carnivore",
	meatAmount = 11,
	hideType = "hide_leathery",
	hideAmount = 7,
	boneType = "bone_avian",
	boneAmount = 11,
	milk = 0,
	tamingChance = 0.250000,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK,
	diet = CARNIVORE,

	templates = {"object/mobile/great_borgle.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"stunattack","stunChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(great_borgle, "great_borgle")