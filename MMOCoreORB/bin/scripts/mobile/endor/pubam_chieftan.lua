pubam_chieftan = Creature:new {
	objectName = "@mob/creature_names:pubam_chieftan",
	randomNameType = NAME_GENERIC_TAG,
	socialGroup = "pubam",
	faction = "pubam",
	level = 51,
	chanceHit = 0.6,
	damageMin = 445,
	damageMax = 600,
	baseXp = 5007,
	baseHAM = 11000,
	baseHAMmax = 14000,
	armor = 1,
	resists = {-1,-1,70,70,70,70,70,100,-1},
	meatType = "",
	meatAmount = 0,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK + KILLER,
	optionsBitmask = 128,
	diet = HERBIVORE,

	templates = {
		"object/mobile/dulok_male.iff",
		"object/mobile/dulok_female.iff"},
	lootGroups = {
		{
			groups = {
				{group = "ewok", chance = 9000000},
				{group = "wearables_all", chance = 1000000},
			},
			lootChance = 2020000
		}
	},
	weapons = {},
	conversationTemplate = "",
	attacks = brawlermaster
}

CreatureTemplates:addCreatureTemplate(pubam_chieftan, "pubam_chieftan")
