borgle_life_sapper = Creature:new {
	objectName = "@mob/creature_names:borgle_life_sapper",
	socialGroup = "Borgle",
	pvpFaction = "",
	faction = "",
	level = 25,
	chanceHit = 0.350000,
	damageMin = 220,
	damageMax = 230,
	baseXp = 2637,
	baseHAM = 7000,
	baseHAMmax = 7000,
	armor = 0,
	resists = {20,30,-1,-1,35,35,50,-1,-1},
	meatType = "meat_carnivore",
	meatAmount = 5,
	hideType = "hide_leathery",
	hideAmount = 5,
	boneType = "bone_avian",
	boneAmount = 5,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = KILLER + STALKER + PACK,
	diet = HERBIVORE,

	templates = {"object/mobile/borgle.iff"},
	lootgroups = {},
	weapons = {"creature_spit_small_red"},
	attacks = {
		{"posturedownattack","postureDownChance=50"},
		{"mediumpoison",""}
	}
}

CreatureTemplates:addCreatureTemplate(borgle_life_sapper, "borgle_life_sapper")