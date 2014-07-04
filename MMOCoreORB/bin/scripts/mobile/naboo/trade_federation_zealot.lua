trade_federation_zealot = Creature:new {
	objectName = "@mob/creature_names:trade_federation_zealot",
	socialGroup = "trade_federation",
	pvpFaction = "trade_federation",
	faction = "trade_federation",
	level = 17,
	chanceHit = 0.32,
	damageMin = 160,
	damageMax = 170,
	baseXp = 1102,
	baseHAM = 3500,
	baseHAMmax = 4300,
	armor = 0,
	resists = {5,5,5,0,0,0,0,-1,-1},
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
	creatureBitmask = PACK,
	optionsBitmask = 128,
	diet = HERBIVORE,

	templates = {"object/mobile/dressed_trade_federation_zealot.iff"},
	lootGroups = {
	    {
			groups = {
				{group = "junk", chance = 2000000},
				{group = "wearables_common", chance = 2000000},
				{group = "melee_weapons", chance = 2000000},					
				{group = "tailor_components", chance = 2000000},
				{group = "loot_kit_parts", chance = 2000000}
			},
			lootChance = 4800000
		}			
	},
	weapons = {"pirate_weapons_medium"},
	conversationTemplate = "",
	attacks = merge(brawlermaster,marksmanmaster)
}

CreatureTemplates:addCreatureTemplate(trade_federation_zealot, "trade_federation_zealot")
