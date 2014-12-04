violent_krahbu = Creature:new {
	objectName = "@mob/creature_names:violent_krahbu",
	socialGroup = "self",
	pvpFaction = "",
	faction = "",
	level = 13,
	chanceHit = 0.29,
	damageMin = 130,
	damageMax = 140,
	baseXp = 514,
	baseHAM = 1000,
	baseHAMmax = 1200,
	armor = 0,
	resists = {110,125,0,0,0,0,0,-1,-1},
	meatType = "meat_herbivore",
	meatAmount = 225,
	hideType = "hide_bristley",
	hideAmount = 135,
	boneType = "bone_mammal",
	boneAmount = 135,
	milk = 0,
	tamingChance = 0.25,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = NONE,
	optionsBitmask = 0,
	diet = CARNIVORE,

	templates = {"object/mobile/violent_krahbu.iff"},
	controlDeviceTemplate = "object/intangible/pet/krahbu_hue.iff",
	scale = 1.15,
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"intimidationattack","intimidationChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(violent_krahbu, "violent_krahbu")
