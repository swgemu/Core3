rabid_mutant_kahmurra = Creature:new {
	objectName = "@mob/creature_names:rabid_mutant_kahmurra",
	socialGroup = "kahmurra",
	faction = "",
	level = 41,
	chanceHit = 0.44,
	damageMin = 345,
	damageMax = 400,
	baseXp = 4097,
	baseHAM = 9300,
	baseHAMmax = 11300,
	armor = 0,
	resists = {30,30,30,145,145,145,145,135,-1},
	meatType = "meat_herbivore",
	meatAmount = 50,
	hideType = "hide_bristley",
	hideAmount = 30,
	boneType = "bone_mammal",
	boneAmount = 35,
	milk = 0,
	tamingChance = 0.15,
	ferocity = 6,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK + KILLER,
	optionsBitmask = AIENABLED,
	diet = CARNIVORE,

	templates = {"object/mobile/mutated_kahmurra.iff"},
	hues = { 16, 17, 18, 19, 20, 21, 22, 23 },
	controlDeviceTemplate = "object/intangible/pet/murra_hue.iff",
	scale = 1.3,
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"strongdisease",""},
		{"stunattack",""}
	}
}

CreatureTemplates:addCreatureTemplate(rabid_mutant_kahmurra, "rabid_mutant_kahmurra")
