huf_dun_bull = Creature:new {
	objectName = "@mob/creature_names:huf_dun_bull",
	socialGroup = "Huf Dun",
	pvpFaction = "",
	faction = "",
	level = 22,
	chanceHit = 0.350000,
	damageMin = 230,
	damageMax = 240,
	baseXp = 2006,
	baseHAM = 7550,
	baseHAMmax = 7550,
	armor = 0,
	resists = {15,0,0,-1,-1,-1,0,-1,-1},
	meatType = "meat_herbivore",
	meatAmount = 1000,
	hideType = "hide_leathery",
	hideAmount = 1000,
	boneType = "bone_mammal",
	boneAmount = 1000,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK + HERD,
	diet = CARNIVORE,

	templates = {"object/mobile/huf_dun.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"dizzyattack","dizzyChance=50"},
		{"stunattack","stunChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(huf_dun_bull, "huf_dun_bull")