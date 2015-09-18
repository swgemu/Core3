fbase_imperial_exterminator_hard = Creature:new {
	objectName = "@mob/creature_names:fbase_imperial_exterminator_hard",
	randomNameType = NAME_GENERIC_TAG,
	socialGroup = "imperial",
	faction = "imperial",
	level = 86,
	chanceHit = 0.86,
	damageMin = 575,
	damageMax = 860,
	baseXp = 8600,
	baseHAM = 17500,
	baseHAMmax = 24500,
	armor = 1,
	resists = {15,15,15,-1,130,-1,130,-1,-1},
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
	attacks = merge(brawlermaster,marksmanmaster,riflemanmaster,teraskasimid)
}

CreatureTemplates:addCreatureTemplate(fbase_imperial_exterminator_hard, "fbase_imperial_exterminator_hard")
