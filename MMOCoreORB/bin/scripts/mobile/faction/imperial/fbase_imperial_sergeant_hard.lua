fbase_imperial_sergeant_hard = Creature:new {
	objectName = "@mob/creature_names:fbase_imperial_sergeant_hard",
	randomNameType = NAME_GENERIC_TAG,
	socialGroup = "imperial",
	faction = "imperial",
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
		"object/mobile/dressed_imperial_officer_f.iff",
		"object/mobile/dressed_imperial_medic1_human_male_01.iff"},
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
	weapons = {"imperial_weapons_medium"},
	conversationTemplate = "imperialRecruiterConvoTemplate",
	reactionStf = "@npc_reaction/military",
	attacks = merge(brawlermaster,marksmanmaster,carbineermaster)
}

CreatureTemplates:addCreatureTemplate(fbase_imperial_sergeant_hard, "fbase_imperial_sergeant_hard")
