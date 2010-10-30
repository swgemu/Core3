flewt_leviathan = Creature:new {
	objectName = "@mob/creature_names:flewt_leviathan",
	socialGroup = "Flewt",
	pvpFaction = "",
	faction = "",
	level = 9,
	chanceHit = 0.280000,
	damageMin = 90,
	damageMax = 110,
	baseXp = 292,
	baseHAM = 450,
	baseHAMmax = 450,
	armor = 0,
	resists = {0,0,0,-1,0,-1,0,-1,-1},
	meatType = "meat_insect",
	meatAmount = 3,
	hideType = "hide_scaley",
	hideAmount = 5,
	boneType = "bone_avian",
	boneAmount = 3,
	milk = 0,
	tamingChance = 0.050000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = PACK + HERD,
	diet = CARNIVORE,

	templates = {"object/mobile/flewt.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"dizzyattack","dizzyChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(flewt_leviathan, "flewt_leviathan")