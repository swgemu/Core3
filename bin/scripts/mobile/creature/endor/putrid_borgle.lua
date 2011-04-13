putrid_borgle = Creature:new {
	objectName = "@mob/creature_names:putrid_borgle",
	socialGroup = "Borgle",
	pvpFaction = "",
	faction = "",
	level = 19,
	chanceHit = 0.320000,
	damageMin = 170,
	damageMax = 180,
	baseXp = 1426,
	baseHAM = 4550,
	baseHAMmax = 4550,
	armor = 0,
	resists = {10,0,0,-1,25,25,45,-1,-1},
	meatType = "meat_carnivore",
	meatAmount = 0,
	hideType = "hide_leathery",
	hideAmount = 5,
	boneType = "bone_avian",
	boneAmount = 5,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = PACK,
	diet = CARNIVORE,

	templates = {"object/mobile/borgle.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"intimidationattack","intimidationChance=50"},
		{"mediumdisease",""}
	}
}

CreatureTemplates:addCreatureTemplate(putrid_borgle, "putrid_borgle")