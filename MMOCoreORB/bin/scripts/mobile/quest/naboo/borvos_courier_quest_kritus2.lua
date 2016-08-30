borvos_courier_quest_kritus2 = Creature:new {
	objectName = "@mob/creature_names:borvos_champion",
	socialGroup = "borvo",
	faction = "borvo",
	level = 21,
	chanceHit = 0.34,
	damageMin = 200,
	damageMax = 210,
	baseXp = 2006,
	baseHAM = 5400,
	baseHAMmax = 6600,
	armor = 0,
	resists = {0,0,0,0,0,0,0,-1,-1},
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

	templates = {"object/mobile/dressed_borvos_champion.iff"},
	lootGroups = {
		{
			groups = {
					{group = "task_loot_bioweapon_quest_kritus", chance = 10000000}
				},
			lootChance = 10000000
		}
	},
	weapons = {"pirate_weapons_medium"},
	reactionStf = "@npc_reaction/slang",
	attacks = merge(brawlermaster,marksmanmaster)
}

CreatureTemplates:addCreatureTemplate(borvos_courier_quest_kritus2, "borvos_courier_quest_kritus2")
