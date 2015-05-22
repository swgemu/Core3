theme_park_marauder_indar = Creature:new {
	objectName = "@npc_name:marauder_base_male",
	customName = "Indar",
	socialGroup = "self",
	faction = "",
	level = 44,
	chanceHit = 0.47,
	damageMin = 345,
	damageMax = 400,
	baseXp = 4370,
	baseHAM = 12000,
	baseHAMmax = 12000,
	armor = 0,
	resists = {40,40,40,40,40,40,40,40,-1},
	meatType = "",
	meatAmount = 0,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK + KILLER,
	optionsBitmask = 128,
	diet = HERBIVORE,

	templates = {"object/mobile/dressed_marauder.iff"},
	lootGroups = {
		{
			groups = {
				{group = "pistols", chance = 1000000},
				{group = "carbines", chance = 1000000},
				{group = "rifles", chance = 1000000},
				{group = "melee_baton", chance = 1000000},
				{group = "loot_kit_parts", chance = 1000000},
				{group = "armor_attachments", chance = 500000},
				{group = "clothing_attachments", chance = 500000},
				{group = "bone_armor", chance = 800000},
				{group = "chitin_armor", chance = 800000},
				{group = "mabari_armor", chance = 800000},
				{group = "tantel_armor", chance = 800000},
				{group = "ubese_armor", chance = 800000},
			}
		}
	},
	weapons = {"pirate_weapons_heavy"},
	conversationTemplate = "",
	attacks = merge(riflemanmaster,pistoleermaster,carbineermaster,brawlermaster)
}

CreatureTemplates:addCreatureTemplate(theme_park_marauder_indar, "theme_park_marauder_indar")