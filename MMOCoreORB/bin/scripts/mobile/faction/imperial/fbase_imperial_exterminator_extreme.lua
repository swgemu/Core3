fbase_imperial_exterminator_extreme = Creature:new {
	objectName = "@mob/creature_names:fbase_imperial_exterminator_extreme",
	randomNameType = NAME_GENERIC_TAG,
	socialGroup = "imperial",
	faction = "imperial",
	level = 172,
	chanceHit = 8.2,
	damageMin = 1005,
	damageMax = 1720,
	baseXp = 17200,
	baseHAM = 107000,
	baseHAMmax = 149000,
	armor = 2,
	resists = {25,25,25,-1,130,-1,130,-1,-1},
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
	creatureBitmask = PACK + KILLER + STALKER,
	optionsBitmask = 128,
	diet = HERBIVORE,

	templates = {"object/mobile/dressed_imperial_exterminator.iff"},
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
	conversationTemplate = "",
	reactionStf = "@npc_reaction/military",
	attacks = merge(brawlermaster,marksmanmaster,riflemanmaster,teraskasimaster)
}

CreatureTemplates:addCreatureTemplate(fbase_imperial_exterminator_extreme, "fbase_imperial_exterminator_extreme")
