hardened_panshee_warrior = Creature:new {
	objectName = "@mob/creature_names:hardened_panshee_warrior",
	randomNameType = NAME_GENERIC_TAG,
	socialGroup = "panshee_tribe",
	faction = "panshee_tribe",
	level = 17,
	chanceHit = 0.31,
	damageMin = 160,
	damageMax = 170,
	baseXp = 1257,
	baseHAM = 3500,
	baseHAMmax = 4300,
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
	creatureBitmask = PACK + KILLER,
	optionsBitmask = 128,
	diet = HERBIVORE,

	templates = {
		"object/mobile/dressed_ewok_m_06.iff",
		"object/mobile/dressed_ewok_m_09.iff"},
	lootGroups = {
		{
			groups = {
				{group = "ewok", chance = 10000000}
			},
			lootChance = 3000000
		}
	},
	weapons = {"ewok_weapons"},
	conversationTemplate = "",
	attacks = merge(marksmanmaster,brawlermaster)
}

CreatureTemplates:addCreatureTemplate(hardened_panshee_warrior, "hardened_panshee_warrior")
