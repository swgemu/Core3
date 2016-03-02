fbase_rebel_squad_leader_hard = Creature:new {
	objectName = "@mob/creature_names:fbase_rebel_squad_leader_hard",
	randomNameType = NAME_GENERIC,
	randomNameTag = true,
	socialGroup = "rebel",
	faction = "rebel",
	level = 84,
	chanceHit = 0.84,
	damageMin = 565,
	damageMax = 840,
	baseXp = 8400,
	baseHAM = 16500,
	baseHAMmax = 24000,
	armor = 1,
	resists = {110,110,40,40,130,40,130,-1,-1},
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
	optionsBitmask = AIENABLED,
	diet = HERBIVORE,

	templates = {
		"object/mobile/dressed_rebel_general_fat_human_male_01.iff",
		"object/mobile/dressed_rebel_general_human_female_01.iff",
		"object/mobile/dressed_rebel_general_human_female_02.iff",
		"object/mobile/dressed_rebel_general_moncal_male_01.iff",
		"object/mobile/dressed_rebel_general_old_twilek_male_01.iff",
		"object/mobile/dressed_rebel_general_rodian_female_01.iff"
		},
	lootGroups = {
		{
			groups = {
				{group = "color_crystals", chance = 200000},
				{group = "junk", chance = 6000000},
				{group = "weapons_all", chance = 1250000},
				{group = "armor_all", chance = 1250000},
				{group = "clothing_attachments", chance = 150000},
				{group = "armor_attachments", chance = 150000},
				{group = "wearables_all", chance = 1000000}
			}
		}
	},
	weapons = {"rebel_weapons_medium"},
	conversationTemplate = "",
	reactionStf = "@npc_reaction/military",
	attacks = merge(brawlermaster,marksmanmaster,carbineermid)
}

CreatureTemplates:addCreatureTemplate(fbase_rebel_squad_leader_hard, "fbase_rebel_squad_leader_hard")
