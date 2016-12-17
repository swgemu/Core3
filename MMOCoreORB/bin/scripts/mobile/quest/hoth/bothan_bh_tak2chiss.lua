bothan_bh_tak2chiss = Creature:new {
	objectName = "@mob/creature_names:bounty_hunter",
	randomNameType = NAME_GENERIC,
	randomNameTag = true,
	socialGroup = "mercenary",
	faction = "",
	level = 115,
	chanceHit = 1,
	damageMin = 820,
	damageMax = 1350,
	baseXp = 10087,
	baseHAM = 24000,
	baseHAMmax = 30000,
	armor = 2,
	resists = {55,55,55,45,155,55,55,-1,-1},
	meatType = "",
	meatAmount = 0,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = KILLER + STALKER,
	optionsBitmask = AIENABLED,
	diet = HERBIVORE,

	templates = { "object/mobile/space_comm_quest_hortrix_steelarm_chiss_m.iff" },
	lootGroups = {
		{
			groups = {
				{group = "junk", chance = 3000000},
				{group = "wearables_common", chance = 1500000},
				{group = "wearables_uncommon", chance = 500000},
				{group = "loot_kit_parts", chance = 2000000},
				{group = "tailor_components", chance = 1000000},
				{group = "melee_weapons", chance = 2000000}
			}
		}
	},
	weapons = {"melee_weapons"},
	conversationTemplate = "",
	reactionStf = "@npc_reaction/slang",
	attacks = merge(brawlermaster,tkamaster)
}

CreatureTemplates:addCreatureTemplate(bothan_bh_tak2chiss, "bothan_bh_tak2chiss")
