kinad_baz_nitch = Creature:new {
	objectName = "@mob/creature_names:kinad_baz_nitch",
	socialGroup = "Baz Nitch",
	pvpFaction = "",
	faction = "",
	level = 46,
	chanceHit = 0.480000,
	damageMin = 380,
	damageMax = 470,
	range = 0,
	baseXp = 4552,
	baseHAM = 10600,
	armor = 0,
	resists = {20,20,0,40,0,0,0,0,-1},
	meatType = "meat_wild",
	meatAmount = 15,
	hideType = "hide_leathery",
	hideAmount = 10,
	boneType = "bone_mammal",
	boneAmount = 5,
	milk = 0,
	tamingChance = 0.150000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE,
	creatureBitmask = KILLER + PACK + HERD,
	diet = CARNIVORE,

	templates = {},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"intimidationattack","intimidationChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(kinad_baz_nitch, "kinad_baz_nitch")
