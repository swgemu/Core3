mand_bunker_technician = Creature:new {
	objectName = "",
	customName = "Labsoll Renuffi (a technican)",
	socialGroup = "death_watch",
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
	optionsBitmask = INVULNERABLE + CONVERSABLE,
	diet = HERBIVORE,

	templates = {"object/mobile/dressed_mand_bunker_technician.iff"},
	lootGroups = {},
	weapons = {},
	conversationTemplate = "deathWatchTechnicianConvoTemplate",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(mand_bunker_technician, "mand_bunker_technician")
