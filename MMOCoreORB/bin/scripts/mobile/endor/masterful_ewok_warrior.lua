masterful_ewok_warrior = Creature:new {
	objectName = "@mob/creature_names:masterful_ewok_warrior",
	socialGroup = "gondula_tribe",
	faction = "gondula_tribe",
	level = 11,
	chanceHit = 0.28,
	damageMin = 90,
	damageMax = 110,
	baseXp = 514,
	baseHAM = 810,
	baseHAMmax = 990,
	armor = 0,
	resists = {5,5,0,15,15,0,0,-1,-1},
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
	diet = HERBIVORE,

	templates = {
		"object/mobile/dressed_ewok_m_06.iff",
		"object/mobile/dressed_ewok_m_08.iff"},
	lootGroups = {
		 {
	        groups = {
				{group = "ewok", chance = 10000000}
			},
			lootChance = 1000000
		}
	},
	weapons = {"ewok_weapons"},
	attacks = merge(marksmanmid,brawlermid)
}

CreatureTemplates:addCreatureTemplate(masterful_ewok_warrior, "masterful_ewok_warrior")
