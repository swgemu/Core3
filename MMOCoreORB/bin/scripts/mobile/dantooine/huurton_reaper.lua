huurton_reaper = Creature:new {
	objectName = "@mob/creature_names:huurton_reaper",
	socialGroup = "huurton",
	faction = "",
	level = 84,
	chanceHit = 0.9,
	damageMin = 620,
	damageMax = 950,
	baseXp = 8038,
	baseHAM = 12000,
	baseHAMmax = 15000,
	armor = 1,
	resists = {135,135,0,140,200,-1,-1,-1,-1},
	meatType = "meat_wild",
	meatAmount = 25,
	hideType = "hide_wooly",
	hideAmount = 25,
	boneType = "bone_mammal",
	boneAmount = 25,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK + KILLER + STALKER,
	optionsBitmask = AIENABLED,
	diet = CARNIVORE,

	templates = {"object/mobile/huurton_hue.iff"},
	hues = { 16, 17, 18, 19, 20, 21, 22, 23 },
	scale = 1.4,
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"intimidationattack",""},
		{"dizzyattack",""}
	}
}

CreatureTemplates:addCreatureTemplate(huurton_reaper, "huurton_reaper")
