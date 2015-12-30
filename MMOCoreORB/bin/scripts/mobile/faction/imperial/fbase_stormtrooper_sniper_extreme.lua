fbase_stormtrooper_sniper_extreme = Creature:new {
	objectName = "@mob/creature_names:fbase_stormtrooper_sniper_extreme",
	randomNameType = NAME_STORMTROOPER,
	randomNameTag = true,
	socialGroup = "imperial",
	faction = "imperial",
	level = 156,
	chanceHit = 6.6,
	damageMin = 925,
	damageMax = 1560,
	baseXp = 15600,
	baseHAM = 83000,
	baseHAMmax = 117000,
	armor = 2,
	resists = {110,110,140,35,35,35,35,-1,-1},
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
	diet = HERBIVORE,
	scale = 1.05,

	templates = {"object/mobile/dressed_stormtrooper_black_black.iff"},
	lootGroups = {
		{
			groups = {
				{group = "color_crystals", chance = 100000},
				{group = "junk", chance = 6000000},
				{group = "weapons_all", chance = 1200000},
				{group = "armor_all", chance = 1200000},
				{group = "clothing_attachments", chance = 150000},
				{group = "armor_attachments", chance = 150000},
				{group = "stormtrooper_common", chance = 200000},
				{group = "wearables_all", chance = 1000000}
			}
		}
	},
	weapons = {"st_sniper_weapons"},
	reactionStf = "@npc_reaction/stormtrooper",
	attacks = merge(riflemanmaster,brawlermaster,marksmanmaster)
}

CreatureTemplates:addCreatureTemplate(fbase_stormtrooper_sniper_extreme, "fbase_stormtrooper_sniper_extreme")
