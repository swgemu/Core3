crackdown_rebel_master_sergeant_hard = Creature:new {
	objectName = "@mob/creature_names:crackdown_rebel_master_sergeant_hard",
	randomNameType = NAME_GENERIC,
	randomNameTag = true,
	socialGroup = "rebel",
	faction = "rebel",
	level = 58,
	chanceHit = 0.59,
	damageMin = 470,
	damageMax = 580,
	baseXp = 5800,
	baseHAM = 11200,
	baseHAMmax = 15000,
	armor = 1,
	resists = {105,105,5,5,5,5,5,-1,-1},
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
	personalityStf = "@hireling/hireling_military",
	attacks = merge(brawlermid,marksmanmaster,carbineermid,pistoleermid,riflemannovice)
}

CreatureTemplates:addCreatureTemplate(crackdown_rebel_master_sergeant_hard, "crackdown_rebel_master_sergeant_hard")
