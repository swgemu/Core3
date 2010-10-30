mantigrue_screecher = Creature:new {
	objectName = "@mob/creature_names:mantigrue_screecher",
	socialGroup = "Mantigrue",
	pvpFaction = "",
	faction = "",
	level = 55,
	chanceHit = 0.550000,
	damageMin = 420,
	damageMax = 550,
	baseXp = 5281,
	baseHAM = 12000,
	baseHAMmax = 12000,
	armor = 0,
	resists = {35,35,0,0,0,-1,0,0,-1},
	meatType = "meat_carnivore",
	meatAmount = 0,
	hideType = "hide_wooly",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.010000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = PACK,
	diet = CARNIVORE,

	templates = {"object/mobile/mantigrue_night_stalker.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"intimidationattack","intimidationChance=50"},
		{"creatureareadisease",""}
	}
}

CreatureTemplates:addCreatureTemplate(mantigrue_screecher, "mantigrue_screecher")