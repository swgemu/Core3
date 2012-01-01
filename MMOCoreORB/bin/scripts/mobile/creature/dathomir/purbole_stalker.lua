purbole_stalker = Creature:new {
	objectName = "@mob/creature_names:purbole_stalker",
	socialGroup = "Purbole",
	pvpFaction = "",
	faction = "",
	level = 19,
	chanceHit = 0.32,
	damageMin = 190,
	damageMax = 200,
	baseXp = 1609,
	baseHAM = 4100,
	baseHAMmax = 5000,
	armor = 0,
	resists = {5,20,5,-1,-1,35,-1,-1,-1},
	meatType = "meat_carnivore",
	meatAmount = 15,
	hideType = "hide_bristley",
	hideAmount = 11,
	boneType = "bone_mammal",
	boneAmount = 11,
	milk = 0,
	tamingChance = 0.25,
	ferocity = 5,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = PACK + KILLER + STALKER,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/purbole.iff"},
	lootgroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"dizzyattack","dizzyChance=50"},
		{"mildpoison",""}
	}
}

CreatureTemplates:addCreatureTemplate(purbole_stalker, "purbole_stalker")