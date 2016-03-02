riverside_sulfur_mynock = Creature:new {
	objectName = "@mob/creature_names:riverside_sulfur_mynock",
	socialGroup = "mynock",
	faction = "",
	level = 33,
	chanceHit = 0.4,
	damageMin = 305,
	damageMax = 320,
	baseXp = 3370,
	baseHAM = 8600,
	baseHAMmax = 10500,
	armor = 1,
	resists = {-1,135,0,165,-1,0,165,-1,-1},
	meatType = "meat_herbivore",
	meatAmount = 60,
	hideType = "hide_leathery",
	hideAmount = 78,
	boneType = "bone_mammal",
	boneAmount = 30,
	milk = 0,
	tamingChance = 0.25,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK + KILLER,
	optionsBitmask = AIENABLED,
	diet = CARNIVORE,

	templates = {"object/mobile/riverside_sulfur_mynock.iff"},
	controlDeviceTemplate = "object/intangible/pet/salt_mynock_hue.iff",
	scale = 1.1,
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"blindattack",""},
		{"mediumdisease",""}
	}
}

CreatureTemplates:addCreatureTemplate(riverside_sulfur_mynock, "riverside_sulfur_mynock")
