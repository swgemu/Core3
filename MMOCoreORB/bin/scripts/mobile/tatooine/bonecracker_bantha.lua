bonecracker_bantha = Creature:new {
	objectName = "@mob/creature_names:bantha_bonecracker",
	socialGroup = "bantha",
	faction = "",
	level = 24,
	chanceHit = 0.35,
	damageMin = 240,
	damageMax = 250,
	baseXp = 2443,
	baseHAM = 7200,
	baseHAMmax = 8800,
	armor = 0,
	resists = {10,125,10,140,-1,-1,-1,-1,-1},
	meatType = "meat_herbivore",
	meatAmount = 475,
	hideType = "hide_wooly",
	hideAmount = 345,
	boneType = "bone_mammal",
	boneAmount = 300,
	milk = 0,
	tamingChance = 0.05,
	ferocity = 2,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK + HERD,
	optionsBitmask = AIENABLED,
	diet = HERBIVORE,

	templates = {"object/mobile/bantha_hue.iff"},
	controlDeviceTemplate = "object/intangible/pet/bantha_hue.iff",
	scale = 1.3,
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"intimidationattack",""},
		{"stunattack",""}
	}
}

CreatureTemplates:addCreatureTemplate(bonecracker_bantha, "bonecracker_bantha")
