prisoner_quest_vinzel_riot = Creature:new {
	objectName = "@mob/creature_names:prisoner",
	socialGroup = "prisoner",
	faction = "",
	level = 27,
	chanceHit = 0.27,
	damageMin = 260,
	damageMax = 270,
	baseXp = 2637,
	baseHAM = 8100,
	baseHAMmax = 9900,
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
	creatureBitmask = PACK + KILLER,
	optionsBitmask = AIENABLED,
	diet = HERBIVORE,

	templates = {"object/mobile/dressed_dathomir_prisoner_01.iff",
		"object/mobile/dressed_dathomir_prisoner_02.iff",
		"object/mobile/dressed_dathomir_prisoner_04.iff",
		"object/mobile/dressed_dathomir_prisoner_05.iff"
	},
	lootGroups = {
		{
			groups = {
				{group = "junk", chance = 5000000},
				{group = "tailor_components", chance = 2000000},
				{group = "loot_kit_parts", chance = 1500000},
				{group = "wearables_common", chance = 1500000}
			}
		}
	},
	weapons = {},
	conversationTemplate = "",
	reactionStf = "@npc_reaction/military",
	attacks = brawlermaster
}

CreatureTemplates:addCreatureTemplate(prisoner_quest_vinzel_riot, "prisoner_quest_vinzel_riot")
