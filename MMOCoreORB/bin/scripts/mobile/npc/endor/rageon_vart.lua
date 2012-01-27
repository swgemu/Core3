rageon_vart = Creature:new {
	objectName = "",
	customName = "Rageon Vart",
	socialGroup = "Death Watch",
	pvpFaction = "Death Watch",
	faction = "",
	level = 178,
	chanceHit = 12.25,
	damageMin = 1020,
	damageMax = 1750,
	baseXp = 16794,
	baseHAM = 175000,
	baseHAMmax = 175000,
	armor = 2,
	resists = {75,75,90,80,45,45,100,70,-1},
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
	lootChance = 10000000, 
	
	templates = {"object/mobile/dressed_death_watch_grey.iff"},
	lootgroups = { 
		{group = "rageon_vart_drop", chance = 10000000} 
	},
	weapons = {"death_watch_commander_weapons"},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(rageon_vart, "rageon_vart")