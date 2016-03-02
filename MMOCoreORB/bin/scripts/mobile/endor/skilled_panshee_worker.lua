skilled_panshee_worker = Creature:new {
	objectName = "@mob/creature_names:skilled_panshee_worker",
	randomNameType = NAME_GENERIC,
	randomNameTag = true,
	socialGroup = "panshee_tribe",
	faction = "panshee_tribe",
	level = 36,
	chanceHit = 0.42,
	damageMin = 325,
	damageMax = 360,
	baseXp = 3551,
	baseHAM = 8900,
	baseHAMmax = 10900,
	armor = 0,
	resists = {0,0,0,0,0,0,0,0,-1},
	meatType = "",
	meatAmount = 0,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK,
	optionsBitmask = AIENABLED,
	diet = HERBIVORE,

	templates = {
		"object/mobile/dressed_ewok_f_01.iff",
		"object/mobile/dressed_ewok_f_03.iff",
		"object/mobile/dressed_ewok_f_04.iff",
		"object/mobile/dressed_ewok_f_06.iff",
		"object/mobile/dressed_ewok_f_07.iff",
		"object/mobile/dressed_ewok_f_08.iff",
		"object/mobile/dressed_ewok_f_09.iff",
		"object/mobile/dressed_ewok_f_12.iff",
		"object/mobile/dressed_ewok_m_01.iff"},
	lootGroups = {
		{
			groups = {
				{group = "ewok", chance = 9000000},
				{group = "wearables_uncommon", chance = 1000000},
			},
			lootChance = 1720000
		}
	},
	weapons = {"ewok_weapons"},
	conversationTemplate = "",
	attacks = merge(riflemanmaster,brawlermaster)
}

CreatureTemplates:addCreatureTemplate(skilled_panshee_worker, "skilled_panshee_worker")
