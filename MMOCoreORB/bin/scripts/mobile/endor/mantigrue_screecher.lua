mantigrue_screecher = Creature:new {
	objectName = "@mob/creature_names:mantigrue_screecher",
	socialGroup = "mantigrue",
	pvpFaction = "",
	faction = "",
	level = 55,
	chanceHit = 0.55,
	damageMin = 420,
	damageMax = 550,
	baseXp = 5281,
	baseHAM = 11000,
	baseHAMmax = 13000,
	armor = 1,
	resists = {135,135,10,10,10,-1,10,10,-1},
	meatType = "meat_carnivore",
	meatAmount = 85,
	hideType = "hide_wooly",
	hideAmount = 65,
	boneType = "bone_avian",
	boneAmount = 45,
	milk = 0,
	tamingChance = 0.01,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/mantigrue_night_stalker.iff"},
	controlDeviceTemplate = "object/intangible/pet/perlek_hue.iff",
	scale = 1.2,
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"creatureareadisease",""},
		{"intimidationattack","intimidationChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(mantigrue_screecher, "mantigrue_screecher")
