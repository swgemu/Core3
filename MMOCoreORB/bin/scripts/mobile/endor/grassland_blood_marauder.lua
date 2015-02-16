grassland_blood_marauder = Creature:new {
	objectName = "@mob/creature_names:grassland_blood_marauder",
	socialGroup = "endor_marauder",
	faction = "endor_marauder",
	level = 50,
	chanceHit = 0.5,
	damageMin = 420,
	damageMax = 550,
	baseXp = 4916,
	baseHAM = 11000,
	baseHAMmax = 13000,
	armor = 0,
	resists = {30,30,0,-1,-1,-1,0,-1,-1},
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
	creatureBitmask = PACK + KILLER + STALKER,
	optionsBitmask = 128,
	diet = HERBIVORE,

	templates = {"object/mobile/dressed_grassland_blood_marauder.iff"},
	lootGroups = {
		{
			groups = {
				{group = "pistols", chance = 2000000},
				{group = "carbines", chance = 2000000},
				{group = "rifles", chance = 2000000},
				{group = "melee_baton", chance = 2000000},
				{group = "loot_kit_parts", chance = 1000000},
				{group = "armor_attachments", chance = 500000},
				{group = "clothing_attachments", chance = 500000}
			},
			lootChance = 2400000
		},
		{
			groups = {
				{group = "bone_armor", chance = 2000000},
				{group = "chitin_armor", chance = 2000000},
				{group = "mabari_armor", chance = 2000000},
				{group = "tantel_armor", chance = 2000000},
				{group = "ubese_armor", chance = 2000000},
			},
			lootChance = 2800000
		}
	},
	weapons = {"pirate_weapons_medium"},
	conversationTemplate = "",
	attacks = merge(riflemanmaster,pistoleermaster,carbineermaster,brawlermaster)
}

CreatureTemplates:addCreatureTemplate(grassland_blood_marauder, "grassland_blood_marauder")
