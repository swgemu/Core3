panshee_veteran = Creature:new {
	objectName = "@mob/creature_names:panshee_veteran",
	randomNameType = NAME_GENERIC,
	randomNameTag = true,
	socialGroup = "panshee_tribe",
	faction = "panshee_tribe",
	level = 35,
	chanceHit = 0.41,
	damageMin = 325,
	damageMax = 360,
	baseXp = 3460,
	baseHAM = 8700,
	baseHAMmax = 10700,
	armor = 0,
	resists = {30,30,30,30,30,30,30,30,-1},
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
		"object/mobile/dressed_ewok_m_08.iff",
		"object/mobile/dressed_ewok_m_09.iff",
		"object/mobile/dressed_ewok_m_10.iff",
		"object/mobile/dressed_ewok_m_12.iff"},
	lootGroups = {
		{
			groups = {
				{group = "ewok", chance = 9000000},
				{group = "wearables_uncommon", chance = 1000000},
			},
			lootChance = 1700000
		}
	},
	weapons = {"ewok_weapons"},
	conversationTemplate = "",
	attacks = merge(riflemanmaster,brawlermaster)
}
CreatureTemplates:addCreatureTemplate(panshee_veteran, "panshee_veteran")
