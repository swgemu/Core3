baz_nitch = Creature:new {
	objectName = "@monster_name:baz_nitch",
	socialGroup = "Baz Nitch",
	pvpFaction = "",
	faction = "",
	level = 22,
	chanceHit = 0.350000,
	damageMin = 210,
	damageMax = 220,
	baseXp = 2219,
	baseHAM = 6550,
	baseHAMmax = 6550,
	armor = 0,
	resists = {20,0,0,-1,0,0,-1,0,-1},
	meatType = "meat_wild",
	meatAmount = 5,
	hideType = "hide_leathery",
	hideAmount = 2,
	boneType = "bone_mammal",
	boneAmount = 2,
	milk = 0,
	tamingChance = 0.250000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = KILLER + PACK + HERD,
	diet = HERBIVORE,

	templates = {"object/mobile/baz_nitch.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {}
}

CreatureTemplates:addCreatureTemplate(baz_nitch, "baz_nitch")