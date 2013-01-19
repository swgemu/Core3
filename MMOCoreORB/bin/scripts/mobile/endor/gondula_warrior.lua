gondula_warrior = Creature:new {
	objectName = "@mob/creature_names:gondula_warrior",
	socialGroup = "gondula_tribe",
	pvpFaction = "gondula_tribe",
	faction = "gondula_tribe",
	level = 23,
	chanceHit = 0.33,
	damageMin = 190,
	damageMax = 200,
	baseXp = 2219,
	baseHAM = 5000,
	baseHAMmax = 6100,
	armor = 0,
	resists = {30,30,0,50,50,-1,-1,-1,-1},
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
	optionsBitmask = 128,
	diet = HERBIVORE,

	templates = {
		"object/mobile/dressed_ewok_m_06.iff",
		"object/mobile/dressed_ewok_m_08.iff"},
	lootGroups = {
		 {
	        groups = {
				{group = "ewok", chance = 3300000}
			},
			lootChance = 1000000
		}
	},
	weapons = {"ewok_weapons"},
	conversationTemplate = "",
	attacks = merge(riflemanmaster)
}

CreatureTemplates:addCreatureTemplate(gondula_warrior, "gondula_warrior")
