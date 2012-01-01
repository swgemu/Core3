blurrg = Creature:new {
	objectName = "@mob/creature_names:blurrg",
	socialGroup = "Blurrg",
	pvpFaction = "",
	faction = "",
	level = 50,
	chanceHit = 0.5,
	damageMin = 395,
	damageMax = 500,
	baseXp = 4825,
	baseHAM = 10000,
	baseHAMmax = 12000,
	armor = 1,
	resists = {20,20,5,40,80,80,-1,-1,-1},
	meatType = "meat_carnivore",
	meatAmount = 0,
	hideType = "hide_leathery",
	hideAmount = 0,
	boneType = "bone_avian",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.1,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/blurrg.iff"},
	lootgroups = {},
	weapons = {"creature_spit_small_yellow"},
	conversationTemplate = "",
	attacks = {
		{"blindattack","blindChance=50"},
		{"stunattack","stunChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(blurrg, "blurrg")