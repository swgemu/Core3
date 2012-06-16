pygmy_torton_protector = Creature:new {
	objectName = "@mob/creature_names:torton_pygmy_protector",
	socialGroup = "torton",
	pvpFaction = "",
	faction = "",
	level = 22,
	chanceHit = 0.33,
	damageMin = 220,
	damageMax = 230,
	baseXp = 2219,
	baseHAM = 3500,
	baseHAMmax = 4300,
	armor = 0,
	resists = {25,25,5,5,5,-1,-1,45,-1},
	meatType = "meat_carnivore",
	meatAmount = 600,
	hideType = "hide_wooly",
	hideAmount = 400,
	boneType = "bone_mammal",
	boneAmount = 600,
	milk = 0,
	tamingChance = 0,
	ferocity = 9,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = PACK + HERD + KILLER,
	optionsBitmask = 128,
	diet = CARNIVORE,

	aiTemplate = "default",

	templates = {"object/mobile/torton.iff"},
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"dizzyattack","dizzyChance=50"},
		{"knockdownattack","knockdownChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(pygmy_torton_protector, "pygmy_torton_protector")