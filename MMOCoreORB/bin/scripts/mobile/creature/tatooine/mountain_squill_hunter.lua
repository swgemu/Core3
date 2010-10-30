mountain_squill_hunter = Creature:new {
	objectName = "@mob/creature_names:mountain_squill_hunter",
	socialGroup = "Mtn. Squill",
	pvpFaction = "",
	faction = "",
	level = 25,
	chanceHit = 0.350000,
	damageMin = 210,
	damageMax = 220,
	baseXp = 2543,
	baseHAM = 6550,
	baseHAMmax = 6550,
	armor = 0,
	resists = {35,35,0,0,-1,-1,-1,-1,-1},
	meatType = "meat_carnivore",
	meatAmount = 2,
	hideType = "hide_leathery",
	hideAmount = 2,
	boneType = "bone_mammal",
	boneAmount = 1,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = PACK,
	diet = CARNIVORE,

	templates = {"object/mobile/mountain_squill.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"intimidationattack","intimidationChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(mountain_squill_hunter, "mountain_squill_hunter")