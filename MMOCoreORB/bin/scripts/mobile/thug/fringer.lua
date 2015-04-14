fringer = Creature:new {
	objectName = "@mob/creature_names:fringer",
	randomNameType = NAME_GENERIC_TAG,
	socialGroup = "mercenary",
	faction = "",
	level = 7,
	chanceHit = 0.260000,
	damageMin = 55,
	damageMax = 65,
	baseXp = 147,
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
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = NONE,
	diet = HERBIVORE,

	templates = {"object/mobile/dressed_commoner_tatooine_rodian_male_02.iff",
		"object/mobile/dressed_commoner_naboo_human_male_02.iff",
		"object/mobile/dressed_commoner_tatooine_bith_male_05.iff"
	},
	lootGroups = {
		{
			groups = {
				{group = "junk", chance = 3500000},
				{group = "wearables_common", chance = 2000000},
				{group = "armor_all", chance = 500000},
				{group = "rifles", chance = 1000000},
				{group = "pistols", chance = 1000000},
				{group = "melee_weapons", chance = 1000000},
				{group = "carbines", chance = 1000000},
			},
			lootChance = 2600000
		}
	},
	weapons = {"pirate_weapons_light"},
	conversationTemplate = "",
	reactionStf = "@npc_reaction/slang",
	attacks = merge(marksmannovice,brawlernovice)
}

CreatureTemplates:addCreatureTemplate(fringer, "fringer")
