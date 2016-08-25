borvos_scientist_quest_kritus = Creature:new {
	objectName = "@mob/creature_names:borvos_mercenary",
	socialGroup = "borvo",
	faction = "borvo",
	level = 21,
	chanceHit = 0.34,
	damageMin = 200,
	damageMax = 210,
	baseXp = 2006,
	baseHAM = 5400,
	baseHAMmax = 6600,
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
	creatureBitmask = PACK,
	optionsBitmask = AIENABLED + CONVERSABLE,
	diet = HERBIVORE,

	templates = {"object/mobile/dressed_borvos_mercenary.iff"},
	lootGroups = {
		{
			groups = {
				{group = "junk", chance = 4000000},
				{group = "color_crystals", chance = 200000},
				{group = "tailor_components", chance = 1000000},
				{group = "loot_kit_parts", chance = 1000000},
				{group = "rifles", chance = 500000},
				{group = "carbines", chance = 500000},
				{group = "borvos_common", chance = 2800000}
			}
		}
	},
	weapons = {},
	conversationTemplate = "kritus_morven_mission_target_convotemplate",
	reactionStf = "@npc_reaction/slang",
	attacks = merge(brawlermaster,teraskasinovice)
}

CreatureTemplates:addCreatureTemplate(borvos_scientist_quest_kritus, "borvos_scientist_quest_kritus")
