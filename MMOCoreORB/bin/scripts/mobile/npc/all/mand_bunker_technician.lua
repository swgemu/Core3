mand_bunker_technician = Creature:new {
	objectName = "@mob/creature_names:death_watch_technician",
	socialGroup = "Death Watch",
	pvpFaction = "Death Watch",
	faction = "",
	level = 100,
	chanceHit = 1,
	damageMin = 645,
	damageMax = 1000,
	baseXp = 9336,
	baseHAM = 24000,
	baseHAMmax = 30000,
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
	pvpBitmask = NONE,
	creatureBitmask = NONE,
	optionsBitmask = 128,
	diet = HERBIVORE,

	templates = {"object/mobile/dressed_mand_bunker_technician.iff"},
	lootgroups = {},
	weapons = {""},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(mand_bunker_technician, "mand_bunker_technician")