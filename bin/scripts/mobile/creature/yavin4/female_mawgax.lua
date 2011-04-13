female_mawgax = Creature:new {
	objectName = "@mob/creature_names:mawgax_female",
	socialGroup = "Mawgax",
	pvpFaction = "",
	faction = "",
	level = 23,
	chanceHit = 0.350000,
	damageMin = 240,
	damageMax = 250,
	baseXp = 2219,
	baseHAM = 6550,
	baseHAMmax = 6550,
	armor = 0,
	resists = {15,15,0,-1,0,0,-1,-1,-1},
	meatType = "",
	meatAmount = 115,
	hideType = "hide_leathery",
	hideAmount = 72,
	boneType = "bone_avian",
	boneAmount = 52,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK + HERD,
	diet = CARNIVORE,

	templates = {"object/mobile/mawgax.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"stunattack","stunChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(female_mawgax, "female_mawgax")