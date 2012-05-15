mature_hanadak = Creature:new {
	objectName = "@mob/creature_names:mature_hanadak",
	socialGroup = "Hanadak",
	pvpFaction = "",
	faction = "",
	level = 31,
	chanceHit = 0.39,
	damageMin = 290,
	damageMax = 300,
	baseXp = 3097,
	baseHAM = 8400,
	baseHAMmax = 10200,
	armor = 0,
	resists = {25,20,-1,80,80,80,-1,-1,-1},
	meatType = "meat_carnivore",
	meatAmount = 20,
	hideType = "hide_bristley",
	hideAmount = 20,
	boneType = "bone_mammal",
	boneAmount = 20,
	milk = 0,
	tamingChance = 0.25,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = PACK + HERD,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/hanadak.iff"},
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"dizzyattack","dizzyChance=50"},
		{"intimidationattack","intimidationChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(mature_hanadak, "mature_hanadak")