hagrin_fed_dub_patrolman = Creature:new {
	objectName = "@mob/creature_names:fed_dub_patrolman",
	socialGroup = "fed_dub",
	faction = "fed_dub",
	level = 9,
	chanceHit = 0.27,
	damageMin = 80,
	damageMax = 90,
	baseXp = 292,
	baseHAM = 675,
	baseHAMmax = 825,
	armor = 0,
	resists = {0,0,0,0,0,0,0,-1,-1},
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
	creatureBitmask = KILLER,
	optionsBitmask = 128,
	diet = HERBIVORE,

	templates = {
		"object/mobile/dressed_fed_dub_patrol_man_human_male_01.iff",
		"object/mobile/dressed_fed_dub_patrolman_human_female_01.iff",
		"object/mobile/dressed_fed_dub_patrolman_human_male_01.iff"},
				
	lootGroups = {
	    {
			groups = {
				{group = "junk", chance = 3000000},
				{group = "wearables_common", chance = 2000000},
				{group = "pistols", chance = 2000000},
				{group = "tailor_components", chance = 1500000},
				{group = "loot_kit_parts", chance = 1500000}
			}
		}
	},
	weapons = {"rebel_weapons_medium"},
	conversationTemplate = "",
	attacks = merge(brawlernovice,marksmannovice)
}

CreatureTemplates:addCreatureTemplate(hagrin_fed_dub_patrolman, "hagrin_fed_dub_patrolman")
