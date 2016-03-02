fbase_rebel_heavy_trooper_hard = Creature:new {
	objectName = "@mob/creature_names:fbase_rebel_heavy_trooper_hard",
	randomNameType = NAME_GENERIC,
	randomNameTag = true,
	socialGroup = "rebel",
	faction = "rebel",
	level = 100,
	chanceHit = 1.0,
	damageMin = 645,
	damageMax = 1000,
	baseXp = 10000,
	baseHAM = 24000,
	baseHAMmax = 30000,
	armor = 1,
	resists = {140,120,115,150,150,150,150,125,-1},
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
	creatureBitmask = PACK + STALKER + KILLER,
	optionsBitmask = AIENABLED,
	diet = HERBIVORE,

	templates = {
		"object/mobile/dressed_rebel_ris_01.iff",
		"object/mobile/dressed_rebel_ris_02.iff",
		"object/mobile/dressed_rebel_ris_03.iff",
		"object/mobile/dressed_rebel_ris_04.iff"},
	lootGroups = {
		{
			groups = {
				{group = "color_crystals", chance = 300000},
				{group = "junk", chance = 6000000},
				{group = "holocron_dark", chance = 150000},
				{group = "holocron_light", chance = 150000},
				{group = "weapons_all", chance = 1050000},
				{group = "armor_all", chance = 1050000},
				{group = "clothing_attachments", chance = 150000},
				{group = "armor_attachments", chance = 150000},
				{group = "wearables_all", chance = 1000000}
			}
		}
	},
	weapons = {"rebel_weapons_medium"},
	conversationTemplate = "",
	reactionStf = "@npc_reaction/military",
	attacks = merge(brawlermaster,marksmanmaster,riflemanmaster,carbineermid)
}

CreatureTemplates:addCreatureTemplate(fbase_rebel_heavy_trooper_hard, "fbase_rebel_heavy_trooper_hard")
