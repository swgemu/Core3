blurrg_raptor = Creature:new {
	objectName = "@mob/creature_names:blurrg_raptor",
	socialGroup = "blurrg",
	faction = "",
	level = 141,
	chanceHit = 6.25,
	damageMin = 945,
	damageMax = 1600,
	baseXp = 13367,
	baseHAM = 62000,
	baseHAMmax = 75000,
	armor = 2,
	resists = {20,20,20,20,20,20,20,20,-1},
	meatType = "meat_carnivore",
	meatAmount = 50,
	hideType = "hide_leathery",
	hideAmount = 40,
	boneType = "bone_avian",
	boneAmount = 35,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK + KILLER + STALKER,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/blurrg_hue.iff"},
	scale = 1.35,
	lootGroups = {},
	weapons = {"creature_spit_small_yellow"},
	conversationTemplate = "",
	attacks = {
		{"stunattack","stunChance=50"},
		{"blindattack","blindChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(blurrg_raptor, "blurrg_raptor")
