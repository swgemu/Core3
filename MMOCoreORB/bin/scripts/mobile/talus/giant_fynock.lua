giant_fynock = Creature:new {
	objectName = "@mob/creature_names:giant_fynock",
	socialGroup = "fynock",
	faction = "",
	level = 42,
	chanceHit = 0.44,
	damageMin = 345,
	damageMax = 400,
	baseXp = 4188,
	baseHAM = 10000,
	baseHAMmax = 12000,
	armor = 0,
	resists = {30,30,30,30,30,30,30,30,-1},
	meatType = "meat_avian",
	meatAmount = 70,
	hideType = "hide_leathery",
	hideAmount = 50,
	boneType = "bone_avian",
	boneAmount = 55,
	milk = 0,
	tamingChance = 0,
	ferocity = 9,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK + KILLER,
	optionsBitmask = AIENABLED,
	diet = CARNIVORE,

	templates = {"object/mobile/fynock_hue.iff"},
	scale = 4,
	lootGroups = {},
	weapons = {"creature_spit_small_red"},
	conversationTemplate = "",
	attacks = {
		{"intimidationattack",""},
		{"creatureareaknockdown",""}
	}
}

CreatureTemplates:addCreatureTemplate(giant_fynock, "giant_fynock")
