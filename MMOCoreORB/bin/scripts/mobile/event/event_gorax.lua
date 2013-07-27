event_gorax = Creature:new {
	objectName = "@mob/creature_names:gorax",
	customName = "Gorax (event)",
	socialGroup = "gorax",
	pvpFaction = "",
	faction = "",
	level = 300,
	chanceHit = 30,
	damageMin = 1645,
	damageMax = 3000,
	baseXp = 0,
	baseHAM = 385000,
	baseHAMmax = 471000,
	armor = 3,
	resists = {65,65,65,65,65,65,65,65,1},
	meatType = "",
	meatAmount = 0,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0,
	ferocity = 20,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = PACK + KILLER,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/gorax.iff"},
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"creatureareaattack",""},
		{"creatureareaknockdown","knockdownChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(event_gorax, "event_gorax")
