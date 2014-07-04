corellian_butterfly_warrior = Creature:new {
	objectName = "@mob/creature_names:corellian_butterfly_warrior",
	socialGroup = "butterfly",
	pvpFaction = "",
	faction = "",
	level = 14,
	chanceHit = 0.3,
	damageMin = 170,
	damageMax = 180,
	baseXp = 714,
	baseHAM = 1200,
	baseHAMmax = 1400,
	armor = 0,
	resists = {0,0,0,0,0,0,0,-1,-1},
	meatType = "meat_insect",
	meatAmount = 12,
	hideType = "hide_scaley",
	hideAmount = 12,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.25,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK + HERD,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/corellian_butterfly_hue.iff"},
	controlDeviceTemplate = "object/intangible/pet/corellian_butterfly_hue.iff",
	scale = 1.15,
	lootGroups = {},
	weapons = {"creature_spit_small_yellow"},
	conversationTemplate = "",
	attacks = {
		{"stunattack","stunChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(corellian_butterfly_warrior, "corellian_butterfly_warrior")
