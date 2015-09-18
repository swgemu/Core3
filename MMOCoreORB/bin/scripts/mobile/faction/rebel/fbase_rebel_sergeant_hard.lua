fbase_rebel_sergeant_hard = Creature:new {
	objectName = "@mob/creature_names:fbase_rebel_sergeant_hard",
	randomNameType = NAME_GENERIC_TAG,
	socialGroup = "rebel",
	faction = "rebel",
	level = 53,
	chanceHit = 0.53,
	damageMin = 410,
	damageMax = 530,
	baseXp = 5300,
	baseHAM = 10500,
	baseHAMmax = 13500,
	armor = 1,
	resists = {5,5,5,5,5,5,5,-1,-1},
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
	optionsBitmask = 136,
	diet = HERBIVORE,

	templates = {
		"object/mobile/dressed_rebel_sergeant_fat_zabrak_male_01.iff",
		"object/mobile/dressed_rebel_sergeant_human_male_01.iff",
		"object/mobile/dressed_rebel_sergeant_moncal_male_01.iff",
		"object/mobile/dressed_rebel_sergeant_rodian_female_01.iff",
		"object/mobile/dressed_rebel_sergeant_rodian_male_01.iff",
		"object/mobile/dressed_rebel_sergeant_twilek_female_old_01.iff"},
	lootGroups = {
		{
			groups = {
				{group = "color_crystals", chance = 100000},
				{group = "junk", chance = 4700000},
				{group = "rifles", chance = 1000000},
				{group = "pistols", chance = 1000000},
				{group = "melee_weapons", chance = 1000000},
				{group = "carbines", chance = 1000000},
				{group = "clothing_attachments", chance = 100000},
				{group = "armor_attachments", chance = 100000},
				{group = "wearables_common", chance = 1000000}
			}
		}
	},
	weapons = {"rebel_weapons_medium"},
	conversationTemplate = "rebelRecruiterConvoTemplate",
	reactionStf = "@npc_reaction/military",
	personalityStf = "@hireling/hireling_military",
	attacks = merge(brawlermaster,marksmanmaster)
}

CreatureTemplates:addCreatureTemplate(fbase_rebel_sergeant_hard, "fbase_rebel_sergeant_hard")
