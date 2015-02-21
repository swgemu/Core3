borgle_life_sapper = Creature:new {
	objectName = "@mob/creature_names:borgle_life_sapper",
	socialGroup = "borgle",
	faction = "",
	level = 25,
	chanceHit = 0.35,
	damageMin = 220,
	damageMax = 230,
	baseXp = 2637,
	baseHAM = 6300,
	baseHAMmax = 7700,
	armor = 0,
	resists = {120,130,-1,-1,135,135,150,-1,-1},
	meatType = "meat_carnivore",
	meatAmount = 5,
	hideType = "hide_leathery",
	hideAmount = 5,
	boneType = "bone_avian",
	boneAmount = 5,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK + KILLER + STALKER,
	optionsBitmask = 128,
	diet = HERBIVORE,

	templates = {"object/mobile/borgle_hue.iff"},
	scale = 1.1,
	lootGroups = {},
	weapons = {"creature_spit_small_red"},
	conversationTemplate = "",
	attacks = {
		{"posturedownattack","postureDownChance=50"},
		{"mediumpoison",""}
	}
}

CreatureTemplates:addCreatureTemplate(borgle_life_sapper, "borgle_life_sapper")
