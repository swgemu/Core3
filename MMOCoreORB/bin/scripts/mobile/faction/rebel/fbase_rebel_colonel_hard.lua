fbase_rebel_colonel_hard = Creature:new {
	objectName = "@mob/creature_names:fbase_rebel_colonel_hard",
	randomNameType = NAME_GENERIC_TAG,
	socialGroup = "rebel",
	faction = "rebel",
	level = 65,
	chanceHit = 0.65,
	damageMin = 470,
	damageMax = 650,
	baseXp = 6500,
	baseHAM = 12500,
	baseHAMmax = 17500,
	armor = 1,
	resists = {115,115,10,10,10,-1,10,-1,-1},
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
	optionsBitmask = 136,
	diet = HERBIVORE,

	templates = {
		"object/mobile/dressed_rebel_lieutenant_colonel_human_male_01.iff",
		"object/mobile/dressed_rebel_lieutenant_colonel_human_male_02.iff",
		"object/mobile/dressed_rebel_lieutenant_colonel_moncal_female_01.iff",
		"object/mobile/dressed_rebel_lieutenant_colonel_rodian_female_01.iff",
		"object/mobile/dressed_rebel_lieutenant_colonel_rodian_male_01.iff",
		"object/mobile/dressed_rebel_lieutenant_colonel_zabrak_male_01.iff"},
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
	attacks = merge(brawlermaster,marksmanmaster,riflemanmid,carbineermid)
}

CreatureTemplates:addCreatureTemplate(fbase_rebel_colonel_hard, "fbase_rebel_colonel_hard")
