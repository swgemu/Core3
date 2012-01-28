death_watch_black_sun_guard = Creature:new {
	objectName = "@mob/creature_names:mand_bunker_blksun_guard",
	socialGroup = "Death Watch",
	pvpFaction = "Death Watch",
	faction = "",
	level = 96,
	chanceHit = 0.95,
	damageMin = 620,
	damageMax = 950,
	baseXp = 9057,
	baseHAM = 22000,
	baseHAMmax = 22000,
	armor = 2,
	resists = {40,40,60,35,55,70,35,40,-1},
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

	templates = {"object/mobile/dressed_black_sun_guard.iff"},
	lootgroups = {
		{group = "death_watch_bunker_commoners", chance = 10000000},
	},
	weapons = {"pirate_weapons_heavy"},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(death_watch_black_sun_guard, "death_watch_black_sun_guard")