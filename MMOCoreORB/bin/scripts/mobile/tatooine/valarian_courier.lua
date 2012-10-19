valarian_courier = Creature:new {
	objectName = "@mob/creature_names:valarian_assassin",
	socialGroup = "valarian",
	pvpFaction = "valarian",
	faction = "valarian",
	level = 16,
	chanceHit = 0.31,
	damageMin = 160,
	damageMax = 170,
	baseXp = 1102,
	baseHAM = 2900,
	baseHAMmax = 3500,
	armor = 0,
	resists = {5,5,5,5,5,5,5,-1,-1},
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
	optionsBitmask = 128,
	diet = HERBIVORE,

	templates = {"object/mobile/dressed_tatooine_valarian_assassin.iff"},
	lootGroups = {
	    {
			groups = {
				{group = "theme_park_loot_jabba_courier", chance = 10000000},
			},
			lootChance = 10000000
		}				
	},
	weapons = {"pirate_weapons_medium"},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(valarian_courier, "valarian_courier")