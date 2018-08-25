shear_mite_queen = Creature:new {
	objectName = "@mob/creature_names:shear_mite_queen",
	socialGroup = "shear_mite",
	faction = "",
	level = 39,
	chanceHit = 0.43,
	damageMin = 340,
	damageMax = 390,
	baseXp = 3824,
	baseHAM = 9000,
	baseHAMmax = 11000,
	armor = 0,
	resists = {130,145,-1,160,-1,160,160,-1,-1},
	meatType = "meat_insect",
	meatAmount = 15,
	hideType = "hide_scaley",
	hideAmount = 12,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0,
	ferocity = 4,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK + STALKER,
	optionsBitmask = AIENABLED,
	diet = CARNIVORE,

	templates = {"object/mobile/shear_mite_queen.iff"},
	hues = { 8, 9, 10, 11, 12, 13, 14, 15 },
	scale = 1.2,
	lootGroups = {},
	weapons = {"creature_spit_small_yellow"},
	conversationTemplate = "",
	attacks = {
		{"dizzyattack",""},
		{"strongpoison",""}
	}
}

CreatureTemplates:addCreatureTemplate(shear_mite_queen, "shear_mite_queen")
