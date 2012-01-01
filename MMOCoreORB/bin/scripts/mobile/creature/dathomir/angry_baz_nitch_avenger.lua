angry_baz_nitch_avenger = Creature:new {
	objectName = "@mob/creature_names:angry_baz_nitch_avenger",
	socialGroup = "Baz Nitch",
	pvpFaction = "",
	faction = "",
	level = 24,
	chanceHit = 0.35,
	damageMin = 230,
	damageMax = 240,
	baseXp = 2543,
	baseHAM = 5000,
	baseHAMmax = 6100,
	armor = 0,
	resists = {10,35,10,10,10,10,10,10,-1},
	meatType = "meat_wild",
	meatAmount = 5,
	hideType = "hide_leathery",
	hideAmount = 2,
	boneType = "bone_mammal",
	boneAmount = 2,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = PACK + HERD + KILLER,
	optionsBitmask = 128,
	diet = HERBIVORE,

	templates = {"object/mobile/baz_nitch.iff"},
	lootgroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"dizzyattack","dizzyChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(angry_baz_nitch_avenger, "angry_baz_nitch_avenger")