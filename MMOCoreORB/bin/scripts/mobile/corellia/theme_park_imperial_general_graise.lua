theme_park_imperial_general_graise = Creature:new {
	objectName = "@mob/creature_names:imperial_general",
	socialGroup = "imperial",
	pvpFaction = "imperial",
	faction = "imperial",
	level = 28,
	chanceHit = 0.37,
	damageMin = 270,
	damageMax = 280,
	baseXp = 2914,
	baseHAM = 8200,
	baseHAMmax = 10000,
	armor = 0,
	resists = {20,20,20,-1,30,-1,30,-1,-1},
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

	templates = {"object/mobile/dressed_imperial_general_m.iff"},
	lootGroups = {
		{
			groups = {
				{group = "theme_park_loot_imperial_general_graise", chance = 10000000}
			},
			lootChance = 10000000
		}						
	},
	weapons = {"imperial_weapons_heavy"},
	conversationTemplate = "",
	attacks = merge(riflemanmaster,carbineermaster)
}

CreatureTemplates:addCreatureTemplate(theme_park_imperial_general_graise, "theme_park_imperial_general_graise")