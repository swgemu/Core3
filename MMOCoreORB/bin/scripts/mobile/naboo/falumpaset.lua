falumpaset = Creature:new {
	objectName = "@mob/creature_names:falumpaset",
	socialGroup = "falumpaset",
	pvpFaction = "",
	faction = "",
	level = 19,
	chanceHit = 0.32,
	damageMin = 170,
	damageMax = 180,
	baseXp = 1257,
	baseHAM = 4100,
	baseHAMmax = 5000,
	armor = 0,
	resists = {125,15,125,-1,-1,-1,125,-1,-1},
	meatType = "meat_herbivore",
	meatAmount = 230,
	hideType = "hide_leathery",
	hideAmount = 130,
	boneType = "bone_mammal",
	boneAmount = 90,
	milkType = "milk_wild",
	milk = 125,
	tamingChance = 0.25,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = HERD,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/falumpaset_hue.iff"},
	controlDeviceTemplate = "object/intangible/pet/falumpaset_hue.iff",
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"posturedownattack","postureDownChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(falumpaset, "falumpaset")
