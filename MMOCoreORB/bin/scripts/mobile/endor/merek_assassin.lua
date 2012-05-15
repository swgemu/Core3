merek_assassin = Creature:new {
	objectName = "@mob/creature_names:merek_assassin",
	socialGroup = "Merek",
	pvpFaction = "",
	faction = "",
	level = 31,
	chanceHit = 0.39,
	damageMin = 325,
	damageMax = 260,
	baseXp = 3188,
	baseHAM = 7700,
	baseHAMmax = 9400,
	armor = 0,
	resists = {50,20,20,20,-1,20,-1,-1,-1},
	meatType = "meat_wild",
	meatAmount = 0,
	hideType = "hide_leathery",
	hideAmount = 45,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.25,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = PACK + KILLER + STALKER,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/merek.iff"},
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"dizzyattack","dizzyChance=50"},
		{"strongpoison",""}
	}
}

CreatureTemplates:addCreatureTemplate(merek_assassin, "merek_assassin")