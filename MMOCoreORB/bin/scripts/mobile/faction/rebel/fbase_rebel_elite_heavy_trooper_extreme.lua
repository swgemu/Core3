fbase_rebel_elite_heavy_trooper_extreme = Creature:new {
	objectName = "@mob/creature_names:fbase_rebel_elite_heavy_trooper_extreme",
	randomNameType = NAME_GENERIC_TAG,
	socialGroup = "rebel",
	faction = "rebel",
	level = 270,
	chanceHit = 18.0,
	damageMin = 1495,
	damageMax = 2700,
	baseXp = 27000,
	baseHAM = 254000,
	baseHAMmax = 345000,
	armor = 3,
	resists = {140,30,30,150,150,150,150,-1,-1},
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
	optionsBitmask = 128,
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
	attacks = merge(brawlermaster,marksmanmaster,riflemanmaster,teraskasimaster)
}

CreatureTemplates:addCreatureTemplate(fbase_rebel_elite_heavy_trooper_extreme, "fbase_rebel_elite_heavy_trooper_extreme")
