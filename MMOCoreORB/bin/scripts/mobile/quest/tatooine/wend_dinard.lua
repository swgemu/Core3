wend_dinard = Creature:new {
	objectName = "",
	socialGroup = "hutt",
	pvpFaction = "hutt",
	faction = "hutt",
	level = 7,
	chanceHit = 0.26,
	damageMin = 55,
	damageMax = 65,
	baseXp = 187,
	baseHAM = 270,
	baseHAMmax = 330,
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
	pvpBitmask = ATTACKABLE,
	creatureBitmask = NONE,
	optionsBitmask = 136,
	diet = HERBIVORE,

	templates = {"object/mobile/dressed_tatooine_jabba_thug.iff"},
	lootGroups = {
	    {
			groups = {
				{group = "junk", chance = 1500000},
				{group = "wearables_common", chance = 2000000},
				{group = "melee_weapons", chance = 2000000},
				{group = "tailor_components", chance = 1500000},
				{group = "loot_kit_parts", chance = 1500000},
				{group = "jabba_common", chance = 1500000}
			},
			lootChance = 2200000
		}
	},
	weapons = {"pirate_weapons_light"},
	conversationTemplate = "lt_harburik_mission_target_convotemplate",
	attacks = merge(brawlernovice,marksmannovice)
}

CreatureTemplates:addCreatureTemplate(wend_dinard, "wend_dinard")
