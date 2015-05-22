tricky_pubam_scout = Creature:new {
	objectName = "@mob/creature_names:tricky_pubam_scout",
	randomNameType = NAME_GENERIC_TAG,
	socialGroup = "pubam",
	faction = "pubam",
	level = 50,
	chanceHit = 0.55,
	damageMin = 420,
	damageMax = 550,
	baseXp = 4916,
	baseHAM = 11000,
	baseHAMmax = 13000,
	armor = 0,
	resists = {-1,35,0,0,0,-1,0,0,-1},
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
			lootChance = 2000000
		}
	},
	weapons = {},
	conversationTemplate = "",
	attacks = brawlermaster
}

CreatureTemplates:addCreatureTemplate(tricky_pubam_scout, "tricky_pubam_scout")
