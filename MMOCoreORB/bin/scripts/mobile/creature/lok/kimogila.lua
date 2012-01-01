kimogila = Creature:new {
	objectName = "@mob/creature_names:kimogila",
	socialGroup = "Kimogila",
	pvpFaction = "",
	faction = "",
	level = 95,
	chanceHit = 0.9,
	damageMin = 630,
	damageMax = 970,
	baseXp = 9057,
	baseHAM = 22000,
	baseHAMmax = 27000,
	armor = 2,
	resists = {45,75,0,75,0,0,100,-1,-1},
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

	templates = {"object/mobile/kimogila.iff"},
	lootgroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"blindattack","blindChance=50"},
		{"dizzyattack","dizzyChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(kimogila, "kimogila")