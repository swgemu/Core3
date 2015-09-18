fbase_rebel_medic_hard = Creature:new {
	objectName = "@mob/creature_names:fbase_rebel_medic_hard",
	randomNameType = NAME_GENERIC_TAG,
	socialGroup = "rebel",
	faction = "rebel",
	level = 51,
	chanceHit = 0.51,
	damageMin = 400,
	damageMax = 510,
	baseXp = 5100,
	baseHAM = 10000,
	baseHAMmax = 13000,
	armor = 1,
	resists = {5,5,5,5,5,5,5,5,-1},
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
	creatureBitmask = PACK + HEALER,
	optionsBitmask = 136,
	diet = HERBIVORE,

	templates = {
		"object/mobile/dressed_rebel_medic3_moncal_female_01.iff",
		"object/mobile/dressed_rebel_medic2_21b_01.iff",
		"object/mobile/dressed_rebel_medic1_bothan_male_01.iff"},
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
	weapons = {"rebel_weapons_light"},
	conversationTemplate = "rebelRecruiterConvoTemplate",
	reactionStf = "@npc_reaction/military",
	attacks = merge(brawlermaster,marksmanmaster,pistoleermid)
}

CreatureTemplates:addCreatureTemplate(fbase_rebel_medic_hard, "fbase_rebel_medic_hard")
