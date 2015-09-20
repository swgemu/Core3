fbase_imperial_colonel_extreme = Creature:new {
	objectName = "@mob/creature_names:fbase_imperial_colonel_extreme",
	randomNameType = NAME_GENERIC_TAG,
	socialGroup = "imperial",
	faction = "imperial",
	level = 130,
	chanceHit = 4.0,
	damageMin = 795,
	damageMax = 1300,
	baseXp = 13000,
	baseHAM = 54000,
	baseHAMmax = 75000,
	armor = 2,
	resists = {115,115,10,10,10,-1,10,-1,-1},
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
	optionsBitmask = 136,
	diet = HERBIVORE,

	templates = {"object/mobile/dressed_imperial_colonel_m.iff"},
	lootGroups = {
		{
			groups = {
				{group = "color_crystals", chance = 100000},
				{group = "junk", chance = 6000000},
				{group = "weapons_all", chance = 1100000},
				{group = "armor_all", chance = 1100000},
				{group = "clothing_attachments", chance = 150000},
				{group = "armor_attachments", chance = 150000},
				{group = "imperial_officer_common", chance = 400000},
				{group = "wearables_all", chance = 1000000}
			}
		}
	},
	weapons = {"imperial_weapons_medium"},
	conversationTemplate = "imperialRecruiterConvoTemplate",
	reactionStf = "@npc_reaction/military",
	attacks = merge(brawlermaster,marksmanmaster,carbineermaster,riflemanmaster)
}

CreatureTemplates:addCreatureTemplate(fbase_imperial_colonel_extreme, "fbase_imperial_colonel_extreme")
