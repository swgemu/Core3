hutt_expeditonary_force_leader = Creature:new {
	objectName = "@mob/creature_names:hutt_expedition_force_leader",
	randomNameType = NAME_GENERIC,
	randomNameTag = true,
	socialGroup = "hutt",
	faction = "hutt",
	level = 21,
	chanceHit = 0.34,
	damageMin = 200,
	damageMax = 210,
	baseXp = 2006,
	baseHAM = 5400,
	baseHAMmax = 6600,
	armor = 0,
	resists = {15,15,15,30,-1,-1,-1,-1,-1},
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

	templates = {"object/mobile/dressed_hutt_expedition_force_leader.iff"},
	lootGroups = {
		{
			groups = {
				{group = "junk", chance = 3400000},
				{group = "tailor_components", chance = 1000000},
				{group = "loot_kit_parts", chance = 1000000},
				{group = "color_crystals", chance = 200000},
				{group = "power_crystals", chance = 200000},
				{group = "pistols", chance = 600000},
				{group = "carbines", chance = 600000},
				{group = "rifles", chance = 600000},
				{group = "clothing_attachments", chance = 200000},
				{group = "armor_attachments", chance = 200000},
				{group = "hutt_exp_common", chance = 2000000}
			}
		}
	},
	weapons = {"pirate_weapons_heavy"},
	conversationTemplate = "",
	reactionStf = "@npc_reaction/slang",
	attacks = merge(brawlermaster,marksmanmaster)
}

CreatureTemplates:addCreatureTemplate(hutt_expeditonary_force_leader, "hutt_expeditonary_force_leader")
