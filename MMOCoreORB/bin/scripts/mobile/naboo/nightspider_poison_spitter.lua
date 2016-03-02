nightspider_poison_spitter = Creature:new {
	objectName = "@mob/creature_names:nightspider_poison_spitter",
	socialGroup = "spider",
	faction = "",
	level = 11,
	chanceHit = 0.29,
	damageMin = 130,
	damageMax = 140,
	baseXp = 430,
	baseHAM = 810,
	baseHAMmax = 990,
	armor = 0,
	resists = {0,0,0,0,0,0,115,-1,-1},
	meatType = "meat_insect",
	meatAmount = 7,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK + HERD + STALKER,
	optionsBitmask = AIENABLED,
	diet = CARNIVORE,

	templates = {"object/mobile/nightspider_poison_spitter.iff"},
	scale = 0.6,
	lootGroups = {},
	weapons = {"creature_spit_small_toxicgreen"},
	conversationTemplate = "",
	attacks = {
		{"stunattack",""},
		{"mildpoison",""}
	}
}

CreatureTemplates:addCreatureTemplate(nightspider_poison_spitter, "nightspider_poison_spitter")
