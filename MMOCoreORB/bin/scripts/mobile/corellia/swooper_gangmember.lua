swooper_gangmember = Creature:new {
	objectName = "",
	randomNameType = NAME_GENERIC_TAG,
	customName = "a swooper gangmember",
	socialGroup = "cor_swoop",
	faction = "cor_swoop",
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
	creatureBitmask = STALKER,
	optionsBitmask = 128,
	diet = HERBIVORE,

	templates = {"object/mobile/dressed_criminal_swooper_zabrak_female_01.iff",
		"object/mobile/dressed_criminal_swooper_human_male_01.iff"},
	lootGroups = {
		{
			groups = {
				{group = "junk", chance = 3500000},
				{group = "loot_kit_parts", chance = 2000000},
				{group = "tailor_components", chance = 1500000},
				{group = "printer_parts", chance = 1000000},
				{group = "swooper_common", chance = 2000000}
			},
			lootChance = 2200000
		}
	},
	weapons = {"pirate_weapons_light"},
	conversationTemplate = "",
	reactionStf = "@npc_reaction/slang",
	attacks = merge(brawlernovice,marksmannovice)
}

CreatureTemplates:addCreatureTemplate(swooper_gangmember, "swooper_gangmember")
