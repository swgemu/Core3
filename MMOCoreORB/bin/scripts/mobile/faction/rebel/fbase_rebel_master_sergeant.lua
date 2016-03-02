fbase_rebel_master_sergeant = Creature:new {
	objectName = "@mob/creature_names:fbase_rebel_master_sergeant",
	randomNameType = NAME_GENERIC,
	randomNameTag = true,
	socialGroup = "rebel",
	faction = "rebel",
	level = 28,
	chanceHit = 0.39,
	damageMin = 270,
	damageMax = 280,
	baseXp = 2800,
	baseHAM = 8200,
	baseHAMmax = 10000,
	armor = 0,
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
	optionsBitmask = AIENABLED + CONVERSABLE,
	diet = HERBIVORE,

	templates = {
		"object/mobile/dressed_rebel_sergeant_major_bothan_male_01.iff",
		"object/mobile/dressed_rebel_sergeant_major_human_male_01.iff",
		"object/mobile/dressed_rebel_sergeant_major_moncal_male_01.iff",
		"object/mobile/dressed_rebel_sergeant_major_moncal_female_01.iff",
		"object/mobile/dressed_rebel_sergeant_major_rodian_female_01.iff",
		"object/mobile/dressed_rebel_sergeant_major_old_zabrak_male_01.iff"},
	lootGroups = {
		{
			groups = {
				{group = "color_crystals", chance = 100000},
				{group = "junk", chance = 6000000},
				{group = "weapons_all", chance = 1100000},
				{group = "armor_all", chance = 1100000},
				{group = "clothing_attachments", chance = 150000},
				{group = "armor_attachments", chance = 150000},
				{group = "rebel_officer_common", chance = 400000},
				{group = "wearables_all", chance = 1000000}
			}
		}
	},
	weapons = {"rebel_weapons_medium"},
	conversationTemplate = "rebelRecruiterConvoTemplate",
	reactionStf = "@npc_reaction/military",
	attacks = merge(brawlermaster,marksmanmaster,carbineernovice)
}

CreatureTemplates:addCreatureTemplate(fbase_rebel_master_sergeant, "fbase_rebel_master_sergeant")
