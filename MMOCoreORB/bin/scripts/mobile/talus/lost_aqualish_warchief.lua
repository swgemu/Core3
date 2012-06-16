lost_aqualish_warchief = Creature:new {
	objectName = "@mob/creature_names:lost_aqualish_warchief",
	socialGroup = "lost_aqualish",
	pvpFaction = "lost_aqualish",
	faction = "lost_aqualish",
	level = 27,
	chanceHit = 0.37,
	damageMin = 290,
	damageMax = 300,
	baseXp = 2822,
	baseHAM = 8100,
	baseHAMmax = 9900,
	armor = 0,
	resists = {0,0,0,0,40,-1,-1,-1,-1},
	meatType = "",
	meatAmount = 0,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = PACK + HERD + KILLER,
	optionsBitmask = 128,
	diet = HERBIVORE,

	aiTemplate = "default",

	templates = {
		"object/mobile/dressed_lost_aqualish_warchief_female_01.iff",
		"object/mobile/dressed_lost_aqualish_warchief_male_01.iff"},
	lootGroups = {
	    {
			groups = {
				{group = "junk", chance = 3000000},
				{group = "tailor_components", chance = 500000},
				{group = "loot_kit_parts", chance = 1500000}
			},
			lootChance = 3200000
		}				
	},
	weapons = {"pirate_weapons_heavy"},
	conversationTemplate = "",
	attacks = merge(brawlermaster,marksmanmaster)
}

CreatureTemplates:addCreatureTemplate(lost_aqualish_warchief, "lost_aqualish_warchief")