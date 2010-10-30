giant_kimogila = Creature:new {
	objectName = "@mob/creature_names:giant_kimogila",
	socialGroup = "Kimogila",
	pvpFaction = "",
	faction = "",
	level = 139,
	chanceHit = 5.500000,
	damageMin = 875,
	damageMax = 1460,
	baseXp = 13178,
	baseHAM = 72500,
	baseHAMmax = 72500,
	armor = 0,
	resists = {35,80,0,80,0,0,100,0,-1},
	meatType = "meat_carnivore",
	meatAmount = 1000,
	hideType = "hide_leathery",
	hideAmount = 1000,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = KILLER + PACK,
	diet = CARNIVORE,

	templates = {"object/mobile/giant_kimogila.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"creatureareaknockdown","knockdownChance=30"},
		{"dizzyattack","dizzyChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(giant_kimogila, "giant_kimogila")