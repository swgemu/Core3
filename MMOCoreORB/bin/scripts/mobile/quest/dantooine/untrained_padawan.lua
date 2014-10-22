untrained_padawan = Creature:new {
	objectName = "",
	customName = "Untrained Padawan",	
	socialGroup = "force",
	pvpFaction = "",
	faction = "",
	level = 100,
	chanceHit = 1,
	damageMin = 550,
	damageMax = 750,
	baseXp = 8830,
	baseHAM = 12000,
	baseHAMmax = 16000,
	armor = 1,
	resists = {80,80,80,80,80,80,80,80,-1},
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
	creatureBitmask = KILLER,
	optionsBitmask = 128,
	diet = HERBIVORE,

	templates = {"object/mobile/dressed_dark_force_crystal_hunter.iff"}, 
	lootGroups = {},
	lootGroups = {
	 {
	        groups = {
				{group = "task_loot_padawan_braid", chance = 10000000}
			},
			lootChance = 10000000
		}
	},	
	weapons = {"mixed_force_weapons"},
	conversationTemplate = "",
	attacks = merge(pikemanmaster,brawlermaster)
}

CreatureTemplates:addCreatureTemplate(untrained_padawan, "untrained_padawan")
