imperial_courier_quest_yith = Creature:new {
	objectName = "@mob/creature_names:assassin_mission_recruiter_imperial",
	socialGroup = "imperial",
	faction = "imperial",
	level = 13,
	chanceHit = 0.3,
	damageMin = 140,
	damageMax = 150,
	baseXp = 609,
	baseHAM = 1500,
	baseHAMmax = 1900,
	armor = 0,
	resists = {0,0,0,0,0,0,0,0,-1},
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
	optionsBitmask = AIENABLED,
	creatureBitmask = PACK,
	diet = HERBIVORE,

	templates = {"object/mobile/dressed_imperial_soldier_m.iff"},
	lootGroups = {
		{
			groups = {
					{group = "task_loot_imp_orders_quest_yith", chance = 10000000}
				},
			lootChance = 10000000
		}
	},
	weapons = {"ranged_weapons"},
	reactionStf = "@npc_reaction/military",
	personalityStf = "@hireling/hireling_military",
	attacks = merge(marksmanmaster,brawlermaster)
}

CreatureTemplates:addCreatureTemplate(imperial_courier_quest_yith, "imperial_courier_quest_yith")
