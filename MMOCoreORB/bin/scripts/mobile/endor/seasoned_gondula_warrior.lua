seasoned_gondula_warrior = Creature:new {
	objectName = "@mob/creature_names:seasoned_gondula_warrior",
	randomNameType = NAME_GENERIC,
	randomNameTag = true,
	socialGroup = "gondula_tribe",
	faction = "gondula_tribe",
	level = 45,
	chanceHit = 0.460000,
	damageMin = 360,
	damageMax = 430,
	baseXp = 4370,
	baseHAM = 9500,
	baseHAMmax = 11700,
	armor = 0,
	resists = {50,50,0,-1,0,0,-1,0,-1},
	meatType = "",
	meatAmount = 0,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK,
	diet = HERBIVORE,

	templates = {
		"object/mobile/dressed_ewok_m_09.iff",
		"object/mobile/dressed_ewok_m_10.iff"},
	lootGroups = {
		{
			groups = {
				{group = "ewok", chance = 9000000},
				{group = "wearables_uncommon", chance = 1000000},
			},
			lootChance = 1900000
		}
	},
	weapons = {"ewok_weapons"},
	attacks = merge(riflemanmaster,brawlermaster)
}

CreatureTemplates:addCreatureTemplate(seasoned_gondula_warrior, "seasoned_gondula_warrior")
