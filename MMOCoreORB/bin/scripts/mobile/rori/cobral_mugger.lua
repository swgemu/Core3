cobral_mugger = Creature:new {
	objectName = "",
	customName = "a Neo-Cobral Mugger",
	socialGroup = "cobral",
	pvpFaction = "cobral",
	faction = "cobral",
	level = 9,
	chanceHit = 0.27,
	damageMin = 80,
	damageMax = 90,
	baseXp = 235,
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
	pvpBitmask = ATTACKABLE,
	creatureBitmask = NONE,
	optionsBitmask = 128,
	diet = HERBIVORE,

	templates = {
		"object/mobile/dressed_cobral_mugger_human_male_01.iff",
		"object/mobile/dressed_cobral_mugger_human_female_01.iff"},
	lootGroups = {
      	{
			groups = {
				{group = "junk", chance = 3000000},
				{group = "wearables_common", chance = 2000000},
				{group = "loot_kit_parts", chance = 2000000},
				{group = "tailor_components", chance = 1000000},
				{group = "melee_weapons", chance = 2000000}
			},
			lootChance = 3000000
		}
	},
	weapons = {"pirate_weapons_light"},
	conversationTemplate = "",
	attacks = merge(brawlernovice,marksmannovice)
}

CreatureTemplates:addCreatureTemplate(cobral_mugger, "cobral_mugger")