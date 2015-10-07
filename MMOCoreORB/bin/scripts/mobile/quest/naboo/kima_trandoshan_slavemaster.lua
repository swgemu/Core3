kima_trandoshan_slavemaster = Creature:new {
	objectName = "@mob/creature_names:trandoshan_slavemaster",
	randomNameType = NAME_GENERIC_TAG,
	socialGroup = "imperial",
	faction = "imperial",
	level = 15,
	chanceHit = 0.36,
	damageMin = 155,
	damageMax = 165,
	baseXp = 1587,
	baseHAM = 2700,
	baseHAMmax = 3300,
	armor = 0,
	resists = {20,20,10,25,35,10,10,10,0},
	meatType = "",
	meatAmount = 0,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = ATTACKABLE + ENEMY,
	creatureBitmask = PACK,
	optionsBitmask = 128,
	diet = HERBIVORE,

	templates = {"object/mobile/dressed_tatooine_trandoshan_slavemaster.iff"},
	lootGroups = {
		{
			groups = {
				{group = "junk", chance = 3000000},
				{group = "wearables_common", chance = 2000000},
				{group = "loot_kit_parts", chance = 2000000},
				{group = "tailor_components", chance = 1000000},
				{group = "carbines", chance = 2000000}
			}
		}
	},
	weapons = {"pirate_weapons_medium"},
	conversationTemplate = "",
	reactionStf = "@npc_reaction/slang",
	attacks = merge(marksmannovice,brawlernovice)
}

CreatureTemplates:addCreatureTemplate(kima_trandoshan_slavemaster, "kima_trandoshan_slavemaster")
