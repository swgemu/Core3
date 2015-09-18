fbase_rebel_colonel = Creature:new {
	objectName = "@mob/creature_names:fbase_rebel_colonel",
	randomNameType = NAME_GENERIC_TAG,
	socialGroup = "rebel",
	faction = "rebel",
	level = 33,
	chanceHit = 0.41,
	damageMin = 310,
	damageMax = 330,
	baseXp = 3300,
	baseHAM = 8700,
	baseHAMmax = 10700,
	armor = 0,
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
		"object/mobile/dressed_rebel_colonel_bothan_male.iff",
		"object/mobile/dressed_rebel_colonel_fat_zabrak_male.iff",
		"object/mobile/dressed_rebel_colonel_moncal_female.iff",
		"object/mobile/dressed_rebel_colonel_old_human_female.iff",
		"object/mobile/dressed_rebel_colonel_sullustan_male_01.iff",
		"object/mobile/dressed_rebel_colonel_twk_male_01.iff"},
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
	attacks = merge(brawlermaster,marksmanmaster,riflemannovice,carbineernovice)
}

CreatureTemplates:addCreatureTemplate(fbase_rebel_colonel, "fbase_rebel_colonel")
