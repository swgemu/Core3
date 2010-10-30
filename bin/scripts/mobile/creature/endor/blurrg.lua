blurrg = Creature:new {
	objectName = "@monster_name:blurrg",
	socialGroup = "Blurrg",
	pvpFaction = "",
	faction = "",
	level = 50,
	chanceHit = 0.500000,
	damageMin = 395,
	damageMax = 500,
	baseXp = 4825,
	baseHAM = 11000,
	baseHAMmax = 11000,
	armor = 0,
	resists = {20,20,0,40,80,80,-1,-1,-1},
	meatType = "meat_carnivore",
	meatAmount = 0,
	hideType = "hide_leathery",
	hideAmount = 0,
	boneType = "bone_avian",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.100000,
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

CreatureTemplates:addCreatureTemplate(blurrg, "blurrg")