tabage_protector = Creature:new {
	objectName = "@mob/creature_names:tabage_protector",
	socialGroup = "tabage",
	faction = "",
	level = 18,
	chanceHit = 0.32,
	damageMin = 160,
	damageMax = 170,
	baseXp = 1257,
	baseHAM = 3500,
	baseHAMmax = 4300,
	armor = 0,
	resists = {0,115,0,0,0,-1,-1,-1,-1},
	meatType = "meat_carnivore",
	meatAmount = 14,
	hideType = "hide_leathery",
	hideAmount = 14,
	boneType = "bone_mammal",
	boneAmount = 14,
	milk = 0,
	tamingChance = 0.25,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK + HERD,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/tabage.iff"},
	controlDeviceTemplate = "object/intangible/pet/langlatch_hue.iff",
	scale = 1.2,
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"stunattack",""},
		{"mildpoison",""}
	}
}

CreatureTemplates:addCreatureTemplate(tabage_protector, "tabage_protector")
