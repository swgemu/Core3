shear_mite_queen = Creature:new {
	objectName = "@mob/creature_names:shear_mite_queen",
	socialGroup = "Shearmite",
	pvpFaction = "",
	faction = "",
	level = 39,
	chanceHit = 0.430000,
	damageMin = 340,
	damageMax = 390,
	baseXp = 3824,
	baseHAM = 10000,
	baseHAMmax = 10000,
	armor = 0,
	resists = {30,45,-1,60,-1,60,60,-1,-1},
	meatType = "meat_insect",
	meatAmount = 15,
	hideType = "hide_scaley",
	hideAmount = 12,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = STALKER + PACK,
	diet = CARNIVORE,

	templates = {"object/mobile/shear_mite_queen.iff"},
	lootgroups = {},
	weapons = {"creature_spit_small_yellow"},
	attacks = {
		{"dizzyattack","dizzyChance=50"},
		{"strongpoison",""}
	}
}

CreatureTemplates:addCreatureTemplate(shear_mite_queen, "shear_mite_queen")