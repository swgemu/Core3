shear_mite_queen = Creature:new {
	objectName = "@mob/creature_names:shear_mite_queen",
	socialGroup = "shear_mite",
	pvpFaction = "",
	faction = "",
	level = 39,
	chanceHit = 0.43,
	damageMin = 340,
	damageMax = 390,
	baseXp = 3824,
	baseHAM = 9000,
	baseHAMmax = 11000,
	armor = 0,
	resists = {30,45,-1,60,-1,60,60,-1,-1},
	meatType = "meat_insect",
	meatAmount = 15,
	hideType = "hide_scaley",
	hideAmount = 12,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0,
	ferocity = 4,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = PACK + STALKER,
	optionsBitmask = 128,
	diet = CARNIVORE,

	aiTemplate = "default",

	templates = {"object/mobile/shear_mite_queen.iff"},
	lootGroups = {},
	weapons = {"creature_spit_small_yellow"},
	conversationTemplate = "",
	attacks = {
		{"dizzyattack","dizzyChance=50"},
		{"strongpoison",""}
	}
}

CreatureTemplates:addCreatureTemplate(shear_mite_queen, "shear_mite_queen")