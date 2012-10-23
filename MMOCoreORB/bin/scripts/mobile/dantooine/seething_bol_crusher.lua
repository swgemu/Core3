seething_bol_crusher = Creature:new {
	objectName = "@mob/creature_names:seething_bol_crusher",
	socialGroup = "bol",
	pvpFaction = "",
	faction = "",
	level = 44,
	chanceHit = 0.44,
	damageMin = 325,
	damageMax = 360,
	baseXp = 4279,
	baseHAM = 9300,
	baseHAMmax = 11300,
	armor = 0,
	resists = {65,45,80,-1,30,30,30,100,-1},
	meatType = "meat_herbivore",
	meatAmount = 180,
	hideType = "hide_leathery",
	hideAmount = 300,
	boneType = "bone_mammal",
	boneAmount = 180,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK + HERD,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/seething_bol_crusher.iff"},
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"dizzyattack","dizzyChance=50"},
		{"mediumdisease",""}
	}
}

CreatureTemplates:addCreatureTemplate(seething_bol_crusher, "seething_bol_crusher")