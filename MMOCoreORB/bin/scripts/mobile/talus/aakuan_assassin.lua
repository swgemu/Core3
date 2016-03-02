aakuan_assassin = Creature:new {
	objectName = "",
	randomNameType = NAME_GENERIC,
	randomNameTag = true,
	customName = "an Aa'kuan Assassin",
	socialGroup = "aakuans",
	faction = "aakuans",
	level = 31,
	chanceHit = 0.37,
	damageMin = 270,
	damageMax = 280,
	baseXp = 3188,
	baseHAM = 8200,
	baseHAMmax = 10000,
	armor = 0,
	resists = {40,40,0,0,0,-1,0,0,-1},
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
	optionsBitmask = AIENABLED,
	diet = HERBIVORE,

	templates = {
		"object/mobile/dressed_aakuan_follower_trandoshan_female_01.iff",
		"object/mobile/dressed_aakuan_follower_trandoshan_male_01.iff"},
	lootGroups = {
		{
			groups = {
				{group = "junk", chance = 4000000},
				{group = "wearables_all", chance = 1000000},
				{group = "data_storage_unit_parts", chance = 1600000},
				{group = "aakuan_common", chance = 2300000},
				{group = "armor_attachments", chance = 500000},
				{group = "clothing_attachments", chance = 600000}
			}
		}
	},
	weapons = {"melee_weapons"},
	conversationTemplate = "",
	reactionStf = "@npc_reaction/fancy",
	attacks = merge(brawlermaster,swordsmanmaster)
}

CreatureTemplates:addCreatureTemplate(aakuan_assassin, "aakuan_assassin")
