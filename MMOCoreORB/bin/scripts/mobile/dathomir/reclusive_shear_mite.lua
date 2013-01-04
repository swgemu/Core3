reclusive_shear_mite = Creature:new {
	objectName = "@mob/creature_names:reclusive_shear_mite",
	socialGroup = "shear_mite",
	pvpFaction = "",
	faction = "",
	level = 26,
	chanceHit = 0.35,
	damageMin = 260,
	damageMax = 270,
	baseXp = 2637,
	baseHAM = 5400,
	baseHAMmax = 6600,
	armor = 1,
	resists = {30,45,-1,60,-1,-1,-1,-1,-1},
	meatType = "meat_insect",
	meatAmount = 15,
	hideType = "hide_scaley",
	hideAmount = 12,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.25,
	ferocity = 4,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK + STALKER,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/shear_mite.iff"},
	lootGroups = {},
	weapons = {"creature_spit_small_yellow"},
	conversationTemplate = "",
	attacks = {
		{"blindattack","blindChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(reclusive_shear_mite, "reclusive_shear_mite")