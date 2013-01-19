seasoned_panshee_warrior = Creature:new {
	objectName = "@mob/creature_names:seasoned_panshee_warrior",
	socialGroup = "panshee_tribe",
	pvpFaction = "panshee_tribe",
	faction = "panshee_tribe",
	level = 42,
	chanceHit = 0.440000,
	damageMin = 345,
	damageMax = 400,
	baseXp = 4097,
	baseHAM = 9300,
	baseHAMmax = 11300,
	armor = 0,
	resists = {40,40,0,0,0,0,0,0,-1},
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
				{group = "ewok", chance = 10000000}
			},
			lootChance = 3000000
		}
	},
	weapons = {"ewok_weapons"},
	attacks = merge(riflemanmaster)
}

CreatureTemplates:addCreatureTemplate(seasoned_panshee_warrior, "seasoned_panshee_warrior")
