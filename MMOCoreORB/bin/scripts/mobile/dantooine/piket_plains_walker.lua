piket_plains_walker = Creature:new {
	objectName = "@mob/creature_names:piket_plains_walker",
	socialGroup = "piket",
	faction = "",
	level = 32,
	chanceHit = 0.4,
	damageMin = 290,
	damageMax = 300,
	baseXp = 3188,
	baseHAM = 8700,
	baseHAMmax = 10700,
	armor = 0,
	resists = {140,20,20,20,20,-1,-1,-1,-1},
	meatType = "meat_herbivore",
	meatAmount = 450,
	hideType = "hide_scaley",
	hideAmount = 300,
	boneType = "bone_mammal",
	boneAmount = 210,
	milkType = "milk_wild",
	milk = 225,
	tamingChance = 0.2,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK + HERD,
	optionsBitmask = AIENABLED,
	diet = CARNIVORE,

	templates = {"object/mobile/piket_plains_walker.iff"},
	controlDeviceTemplate = "object/intangible/pet/piket_hue.iff",
	scale = 1.05,
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"dizzyattack",""}
	}
}

CreatureTemplates:addCreatureTemplate(piket_plains_walker, "piket_plains_walker")
