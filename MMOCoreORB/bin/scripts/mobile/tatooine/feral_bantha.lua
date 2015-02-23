feral_bantha = Creature:new {
	objectName = "@mob/creature_names:feral_bantha",
	socialGroup = "bantha",
	faction = "",
	level = 15,
	chanceHit = 0.31,
	damageMin = 170,
	damageMax = 180,
	baseXp = 960,
	baseHAM = 1200,
	baseHAMmax = 1400,
	armor = 0,
	resists = {5,110,5,130,-1,-1,-1,-1,-1},
	meatType = "meat_herbivore",
	meatAmount = 415,
	hideType = "hide_wooly",
	hideAmount = 305,
	boneType = "bone_mammal",
	boneAmount = 215,
	milk = 0,
	tamingChance = 0.25,
	ferocity = 2,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK + HERD + KILLER,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/bantha_hue.iff"},
	controlDeviceTemplate = "object/intangible/pet/bantha_hue.iff",
	scale = 1.05,
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"dizzyattack",""}
	}
}

CreatureTemplates:addCreatureTemplate(feral_bantha, "feral_bantha")
