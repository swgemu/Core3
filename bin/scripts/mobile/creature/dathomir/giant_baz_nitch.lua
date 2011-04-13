giant_baz_nitch = Creature:new {
	objectName = "@mob/creature_names:giant_baz_nitch",
	socialGroup = "Baz Nitch",
	pvpFaction = "",
	faction = "",
	level = 35,
	chanceHit = 0.410000,
	damageMin = 320,
	damageMax = 350,
	baseXp = 3551,
	baseHAM = 9700,
	baseHAMmax = 9700,
	armor = 0,
	resists = {45,45,0,-1,-1,-1,0,-1,-1},
	meatType = "meat_wild",
	meatAmount = 9,
	hideType = "hide_leathery",
	hideAmount = 5,
	boneType = "bone_mammal",
	boneAmount = 5,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = KILLER + PACK + HERD,
	diet = CARNIVORE,

	templates = {"object/mobile/giant_baz_nitch.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {}
}

CreatureTemplates:addCreatureTemplate(giant_baz_nitch, "giant_baz_nitch")