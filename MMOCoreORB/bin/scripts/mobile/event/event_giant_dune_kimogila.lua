event_giant_dune_kimogila = Creature:new {
	objectName = "@mob/creature_names:giant_dune_kimogila",
	customName = "a giant dune kimogila (event)",
	socialGroup = "kimogila",
	pvpFaction = "",
	faction = "",
	level = 153,
	chanceHit = 85,
	damageMin = 895,
	damageMax = 1500,
	baseXp = 0,
	baseHAM = 81000,
	baseHAMmax = 99000,
	armor = 2,
	resists = {65,80,65,100,65,65,100,65,-1},
	meatType = "meat_carnivore",
	meatAmount = 0,
	hideType = "hide_leathery",
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

	templates = {"object/mobile/giant_dune_kimogila.iff"},
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"creatureareacombo",""},
		{"creatureareadisease",""}
	}
}

CreatureTemplates:addCreatureTemplate(event_giant_dune_kimogila, "event_giant_dune_kimogila")
