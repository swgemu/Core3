giant_mawgax = Creature:new {
	objectName = "@mob/creature_names:giant_mawgax",
	socialGroup = "Mawgax",
	pvpFaction = "",
	faction = "",
	level = 32,
	chanceHit = 0.400000,
	damageMin = 305,
	damageMax = 320,
	baseXp = 3188,
	baseHAM = 9550,
	baseHAMmax = 9550,
	armor = 0,
	resists = {0,30,0,-1,30,-1,0,0,-1},
	meatType = "",
	meatAmount = 130,
	hideType = "hide_leathery",
	hideAmount = 85,
	boneType = "bone_avian",
	boneAmount = 70,
	milk = 0,
	tamingChance = 0.020000,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK + HERD,
	diet = CARNIVORE,

	templates = {"object/mobile/giant_mawgax.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"stunattack","stunChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(giant_mawgax, "giant_mawgax")