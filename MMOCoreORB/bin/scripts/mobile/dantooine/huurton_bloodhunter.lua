huurton_bloodhunter = Creature:new {
	objectName = "@mob/creature_names:huurton_bloodhunter",
	socialGroup = "huurton",
	pvpFaction = "",
	faction = "",
	level = 28,
	chanceHit = 0.37,
	damageMin = 290,
	damageMax = 300,
	baseXp = 2914,
	baseHAM = 9000,
	baseHAMmax = 9000,
	armor = 0,
	resists = {115,115,15,125,115,15,15,-1,-1},
	meatType = "meat_wild",
	meatAmount = 15,
	hideType = "hide_wooly",
	hideAmount = 15,
	boneType = "bone_mammal",
	boneAmount = 15,
	milk = 0,
	tamingChance = 0.05,
	ferocity = 9,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK + HERD + KILLER,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/huurton_hue.iff"},
	controlDeviceTemplate = "object/intangible/pet/huurton_hue.iff",
	scale = 1.2,
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"stunattack","stunChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(huurton_bloodhunter, "huurton_bloodhunter")
