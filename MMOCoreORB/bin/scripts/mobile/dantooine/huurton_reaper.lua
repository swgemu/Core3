huurton_reaper = Creature:new {
	objectName = "@mob/creature_names:huurton_reaper",
	socialGroup = "huurton",
	pvpFaction = "",
	faction = "",
	level = 84,
	chanceHit = 0.9,
	damageMin = 620,
	damageMax = 950,
	baseXp = 8038,
	baseHAM = 12000,
	baseHAMmax = 15000,
	armor = 0,
	resists = {35,35,0,40,100,-1,-1,-1,-1},
	meatType = "meat_wild",
	meatAmount = 25,
	hideType = "hide_wooly",
	hideAmount = 0,
	boneType = "bone_mammal",
	boneAmount = 25,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK + KILLER + STALKER,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/huurton_hue.iff"},
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"dizzyattack","dizzyChance=50"},
		{"intimidationattack","intimidationChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(huurton_reaper, "huurton_reaper")