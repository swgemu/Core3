event_minor_gorax = Creature:new {
	objectName = "@mob/creature_names:minor_gorax",
	customName = "a minor gorax (event)",
	socialGroup = "gorax",
	pvpFaction = "",
	faction = "",
	level = 131,
	chanceHit = 40,
	damageMin = 745,
	damageMax = 1200,
	baseXp = 0,
	baseHAM = 89000,
	baseHAMmax = 109000,
	armor = 3,
	resists = {65,65,50,50,50,50,50,50,-1},
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
	creatureBitmask = PACK + KILLER,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/gorax.iff"},
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"creatureareaattack",""}
	}
}

CreatureTemplates:addCreatureTemplate(event_minor_gorax, "event_minor_gorax")
