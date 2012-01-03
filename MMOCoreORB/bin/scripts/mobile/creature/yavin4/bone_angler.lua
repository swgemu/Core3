bone_angler = Creature:new {
	objectName = "@mob/creature_names:angler_bone",
	socialGroup = "Angler",
	pvpFaction = "",
	faction = "",
	level = 27,
	chanceHit = 0.37,
	damageMin = 210,
	damageMax = 220,
	baseXp = 2730,
	baseHAM = 7700,
	baseHAMmax = 9400,
	armor = 0,
	resists = {15,15,15,15,15,15,15,-1,-1},
	meatType = "meat_insect",
	meatAmount = 4,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.05,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = PACK + STALKER,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/angler.iff"},
	lootgroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"intimidationattack","intimidationChance=50"},
		{"strongpoison",""}
	}
}

CreatureTemplates:addCreatureTemplate(bone_angler, "bone_angler")