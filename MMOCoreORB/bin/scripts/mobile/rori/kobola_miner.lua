kobola_miner = Creature:new {
	objectName = "@mob/creature_names:kobola_miner",
	socialGroup = "kobola",
	faction = "kobola",
	level = 8,
	chanceHit = 0.27,
	damageMin = 70,
	damageMax = 75,
	baseXp = 187,
	baseHAM = 405,
	baseHAMmax = 495,
	armor = 0,
	resists = {0,0,0,10,10,0,0,-1,-1},
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
	creatureBitmask = HERD,
	optionsBitmask = 128,
	diet = HERBIVORE,

	templates = {
		"object/mobile/dressed_kobola_miner_human_male_01.iff",
		"object/mobile/dressed_kobola_miner_human_female_01.iff"},
	lootGroups = {
		{
			groups = {
				{group = "junk", chance = 2400000},
				{group = "tailor_components", chance = 2000000},
				{group = "loot_kit_parts", chance = 2000000},
				{group = "kobola_common", chance = 3600000}
			},
			lootChance = 2400000
		}
	},
	weapons = {"ranged_weapons"},
	conversationTemplate = "",
	reactionStf = "@npc_reaction/slang",
	attacks = merge(brawlernovice,marksmannovice)
}

CreatureTemplates:addCreatureTemplate(kobola_miner, "kobola_miner")
