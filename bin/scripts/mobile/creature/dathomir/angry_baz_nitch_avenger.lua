angry_baz_nitch_avenger = Creature:new {
	objectName = "@mob/creature_names:angry_baz_nitch_avenger",
	socialGroup = "Baz Nitch",
	pvpFaction = "",
	faction = "",
	level = 24,
	chanceHit = 0.350000,
	damageMin = 230,
	damageMax = 240,
	baseXp = 2543,
	baseHAM = 5550,
	baseHAMmax = 5550,
	armor = 0,
	resists = {0,35,0,0,0,0,0,0,-1},
	meatType = "meat_wild",
	meatAmount = 5,
	hideType = "hide_leathery",
	hideAmount = 2,
	boneType = "bone_mammal",
	boneAmount = 2,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = KILLER + PACK + HERD,
	diet = HERBIVORE,

	templates = {"object/mobile/baz_nitch.iff"},
	lootgroups = {},
	weapons = {"creature_spit_small_yellow"},
	attacks = {
		{"dizzyattack","dizzyChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(angry_baz_nitch_avenger, "angry_baz_nitch_avenger")