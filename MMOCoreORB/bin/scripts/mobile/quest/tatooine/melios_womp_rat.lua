melios_womp_rat = Creature:new {
	objectName = "@mob/creature_names:mutant_womprat",
	socialGroup = "rat",
	faction = "",
	level = 13,
	chanceHit = 0.29,
	damageMin = 130,
	damageMax = 140,
	baseXp = 609,
	baseHAM = 1000,
	baseHAMmax = 1200,
	armor = 0,
	resists = {110,115,0,0,0,0,115,-1,-1},
	meatType = "meat_wild",
	meatAmount = 6,
	hideType = "hide_leathery",
	hideAmount = 5,
	boneType = "bone_mammal",
	boneAmount = 4,
	milk = 0,
	tamingChance = 0.25,
	ferocity = 3,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK + STALKER,
	optionsBitmask = AIENABLED,
	diet = CARNIVORE,

	templates = {"object/mobile/womp_rat.iff"},
	controlDeviceTemplate = "object/intangible/pet/womp_rat_hue.iff",
	scale = 2.15,
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	lootGroups = {
		{
			groups = {
				{ group = "task_loot_melios_purl_q2", chance = 10000000},			},
 			lootChance = 10000000
		},
	},
	attacks = {
		{"stunattack",""}
	}
}

CreatureTemplates:addCreatureTemplate(melios_womp_rat, "melios_womp_rat")
