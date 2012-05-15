lice_ridden_remmer_queen = Creature:new {
	objectName = "@mob/creature_names:lice_ridden_remmer_queen",
	socialGroup = "Remmer",
	pvpFaction = "",
	faction = "",
	level = 37,
	chanceHit = 0.41,
	damageMin = 320,
	damageMax = 350,
	baseXp = 3642,
	baseHAM = 8800,
	baseHAMmax = 10800,
	armor = 0,
	resists = {55,35,60,0,0,0,-1,-1,-1},
	meatType = "meat_carnivore",
	meatAmount = 0,
	hideType = "hide_bristley",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = PACK,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/lice_ridden_remmer_queen.iff"},
	lootGroups = {},
	weapons = {"creature_spit_small_yellow"},
	conversationTemplate = "",
	attacks = {
		{"knockdownattack","knockdownChance=50"},
		{"mediumdisease",""}
	}
}

CreatureTemplates:addCreatureTemplate(lice_ridden_remmer_queen, "lice_ridden_remmer_queen")