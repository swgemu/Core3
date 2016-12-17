chiss_imp_snow_agent = Creature:new {
	objectName = "@mob/creature_names:patron_chiss_male",
	socialGroup = "imperial",
	faction = "imperial",
	level = 100,
	chanceHit = 1,
	damageMin = 645,
	damageMax = 1000,
	baseXp = 9429,
	baseHAM = 24000,
	baseHAMmax = 30000,
	armor = 0,
	resists = {15,15,15,10,195,15,15,15,-1},
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

	templates = {"object/mobile/dressed_patron_chiss_m_01.iff"},
	lootGroups = {
		{
			groups = {
				{group = "color_crystals", chance = 100000},
				{group = "junk", chance = 3400000},
				{group = "rifles", chance = 1200000},
				{group = "pistols", chance = 1200000},
				{group = "melee_weapons", chance = 1200000},
				{group = "carbines", chance = 1200000},
				{group = "clothing_attachments", chance = 250000},
				{group = "armor_attachments", chance = 250000},
				{group = "stormtrooper_common", chance = 700000},
				{group = "wearables_common", chance = 500000}
			}
		}
	},
	weapons = {"imperial_weapons_medium"},
	conversationTemplate = "",
	reactionStf = "@npc_reaction/military",
	attacks = merge(brawlermaster,marksmanmaster)
}

CreatureTemplates:addCreatureTemplate(chiss_imp_snow_agent, "chiss_imp_snow_agent")