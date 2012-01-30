giant_kimogila = Creature:new {
	objectName = "@mob/creature_names:giant_kimogila",
	socialGroup = "Kimogila",
	pvpFaction = "",
	faction = "",
	level = 139,
	chanceHit = 5.5,
	damageMin = 875,
	damageMax = 1460,
	baseXp = 13178,
	baseHAM = 65000,
	baseHAMmax = 80000,
	armor = 2,
	resists = {35,80,20,80,20,20,100,20,-1},
	meatType = "meat_carnivore",
	meatAmount = 1000,
	hideType = "hide_leathery",
	hideAmount = 1000,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = PACK + KILLER,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/giant_kimogila.iff"},
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"creatureareaknockdown","knockdownChance=50"},
		{"dizzyattack","dizzyChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(giant_kimogila, "giant_kimogila")