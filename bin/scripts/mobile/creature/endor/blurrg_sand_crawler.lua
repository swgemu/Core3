blurrg_sand_crawler = Creature:new {
	objectName = "@mob/creature_names:blurrg_sand_crawler",
	socialGroup = "Blurrg",
	pvpFaction = "",
	faction = "",
	level = 43,
	chanceHit = 0.440000,
	damageMin = 345,
	damageMax = 400,
	baseXp = 4188,
	baseHAM = 10300,
	baseHAMmax = 10300,
	armor = 0,
	resists = {45,45,0,100,20,100,-1,-1,-1},
	meatType = "meat_carnivore",
	meatAmount = 0,
	hideType = "hide_leathery",
	hideAmount = 0,
	boneType = "bone_avian",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK,
	diet = CARNIVORE,

	templates = {"object/mobile/blurrg.iff"},
	lootgroups = {},
	weapons = {"creature_spit_small_yellow"},
	attacks = {
		{"stunattack","stunChance=50"},
		{"blindattack","blindChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(blurrg_sand_crawler, "blurrg_sand_crawler")