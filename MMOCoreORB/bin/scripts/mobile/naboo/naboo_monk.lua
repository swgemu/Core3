naboo_monk = Creature:new {
	objectName = "@mob/creature_names:naboo_monk",
	randomNameType = NAME_GENERIC_TAG,
	socialGroup = "self",
	faction = "naboo",
	level = 4,
	chanceHit = 0.24,
	damageMin = 40,
	damageMax = 45,
	baseXp = 62,
	baseHAM = 113,
	baseHAMmax = 138,
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
	creatureBitmask = HERD,
	optionsBitmask = 128,
	diet = HERBIVORE,

	templates = {"object/mobile/dressed_naboo_monk.iff",
		"object/mobile/dressed_commoner_fat_human_female_02.iff", --in Theed?
	},
	lootGroups = {
		{
			groups = {
				{group = "junk", chance = 4000000},
				{group = "wearables_common", chance = 2000000},
				{group = "tailor_components", chance = 2000000},
				{group = "loot_kit_parts", chance = 2000000}
			}
		}
	},
	weapons = {},
	conversationTemplate = "",
	reactionStf = "@npc_reaction/fancy",
	attacks = brawlernovice
}

CreatureTemplates:addCreatureTemplate(naboo_monk, "naboo_monk")
