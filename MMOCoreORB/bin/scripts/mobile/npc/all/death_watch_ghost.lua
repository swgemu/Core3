death_watch_ghost = Creature:new {
	objectName = "@mob/creature_names:mand_bunker_dthwatch_grey",
	socialGroup = "Death Watch",
	pvpFaction = "Death Watch",
	faction = "",
	level = 152,
	chanceHit = 8.5,
	damageMin = 895,
	damageMax = 1500,
	baseXp = 14314,
	baseHAM = 110000,
	baseHAMmax = 110000,
	armor = 2,
	resists = {65,65,70,60,35,35,100,50,-1},
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
	creatureBitmask = KILLER,
	optionsBitmask = 128,
	diet = HERBIVORE,
	lootChance = 1000000,

	templates = {"object/mobile/dressed_death_watch_grey.iff"},
	lootgroups = {
		{group = "death_watch_bunker_commoners",   chance = 6000000},
		{group = "death_watch_bunker_lieutenants", chance = 3500000},
		{group = "death_watch_bunker_ingredient",  chance =  500000},
	},
	weapons = {"pirate_weapons_heavy"},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(death_watch_ghost, "death_watch_ghost")