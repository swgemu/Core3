theme_park_jabba_veterinarian = Creature:new {
	objectName = "@mob/creature_names:alkhara_champion",
	socialGroup = "alkhara",
	faction = "alkhara",
	level = 20,
	chanceHit = 0.33,
	damageMin = 180,
	damageMax = 190,
	baseXp = 1803,
	baseHAM = 5000,
	baseHAMmax = 6100,
	armor = 0,
	resists = {15,15,25,25,-1,-1,-1,-1,-1},
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

	templates = {"object/mobile/dressed_tatooine_alkhara_champion.iff"},
	lootGroups = {
	    {
			groups = {
				{group = "theme_park_loot_jabba_veterinarian", chance = 10000000},
			},
			lootChance = 10000000
		}			
	},
	weapons = {"pirate_weapons_medium"},
	conversationTemplate = "",
	attacks = merge(brawlermaster,marksmanmaster)
}

CreatureTemplates:addCreatureTemplate(theme_park_jabba_veterinarian, "theme_park_jabba_veterinarian")