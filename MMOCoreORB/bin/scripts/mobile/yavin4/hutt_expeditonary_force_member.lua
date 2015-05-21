hutt_expeditonary_force_member = Creature:new {
	objectName = "@mob/creature_names:hutt_expedition_force_member",
	randomNameType = NAME_GENERIC_TAG,
	socialGroup = "hutt",
	faction = "hutt",
	level = 17,
	chanceHit = 0.32,
	damageMin = 160,
	damageMax = 170,
	baseXp = 1257,
	baseHAM = 3500,
	baseHAMmax = 4300,
	armor = 0,
	resists = {15,5,5,-1,-1,-1,-1,-1,-1},
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
	optionsBitmask = 128,
	diet = HERBIVORE,

	templates = {"object/mobile/dressed_hutt_expedition_force_member.iff"},
	lootGroups = {
		{
			groups = {
				{group = "junk", chance = 3400000},
				{group = "tailor_components", chance = 1000000},
				{group = "loot_kit_parts", chance = 1000000},
				{group = "color_crystals", chance = 200000},
				{group = "crystals_poor", chance = 200000},
				{group = "pistols", chance = 600000},
				{group = "carbines", chance = 600000},
				{group = "rifles", chance = 600000},
				{group = "clothing_attachments", chance = 200000},
				{group = "armor_attachments", chance = 200000},
				{group = "hutt_exp_common", chance = 2000000}
			}
		}
	},
	weapons = {"ranged_weapons"},
	conversationTemplate = "",
	reactionStf = "@npc_reaction/slang",
	attacks = merge(brawlermaster,marksmanmaster)
}

CreatureTemplates:addCreatureTemplate(hutt_expeditonary_force_member, "hutt_expeditonary_force_member")
