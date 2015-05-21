aakuan_defender = Creature:new {
	objectName = "@mob/creature_names:aakuan_defender",
	randomNameType = NAME_GENERIC_TAG,
	socialGroup = "aakuans",
	faction = "aakuans",
	level = 23,
	chanceHit = 0.33,
	damageMin = 190,
	damageMax = 200,
	baseXp = 2443,
	baseHAM = 5000,
	baseHAMmax = 6100,
	armor = 0,
	resists = {35,35,-1,10,10,-1,10,-1,-1},
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

	templates = {
		"object/mobile/dressed_aakuan_defender_human_male_01.iff",
		"object/mobile/dressed_aakuan_defender_human_female_01.iff"},
	lootGroups = {
		{
			groups = {
				{group = "junk", chance = 6600000},
				{group = "aakuan_common", chance = 2300000},
				{group = "armor_attachments", chance = 200000},
				{group = "rifles", chance = 300000},
				{group = "carbines", chance = 300000},
				{group = "pistols", chance = 300000}
			}
		}
	},
	weapons = {"melee_weapons"},
	conversationTemplate = "",
	reactionStf = "@npc_reaction/fancy",
	attacks = brawlermaster
}

CreatureTemplates:addCreatureTemplate(aakuan_defender, "aakuan_defender")
