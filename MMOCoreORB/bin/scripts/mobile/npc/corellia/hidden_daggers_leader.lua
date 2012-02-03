hidden_daggers_leader = Creature:new {
	objectName = "@mob/creature_names:hidden_daggers_leader",
	socialGroup = "Hidden Dagger",
	pvpFaction = "Hidden Dagger",
	faction = "",
	level = 18,
	chanceHit = 0.32,
	damageMin = 170,
	damageMax = 180,
	baseXp = 1426,
	baseHAM = 2900,
	baseHAMmax = 3500,
	armor = 0,
	resists = {5,15,5,-1,-1,-1,40,-1,-1},
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

	templates = {},
	lootGroups = {
		{
			groups = {
				{group = "loot_kit_items", chance = 10000000}
			},
			lootChance = 3300000
		}
	},
	weapons = {"ranged_weapons"},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(hidden_daggers_leader, "hidden_daggers_leader")