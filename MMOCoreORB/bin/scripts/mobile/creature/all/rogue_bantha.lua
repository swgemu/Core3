rogue_bantha = Creature:new {
	objectName = "@mob/creature_names:rogue_bantha",
	socialGroup = "Bantha",
	pvpFaction = "",
	faction = "",
	level = 15,
	chanceHit = 0.3,
	damageMin = 170,
	damageMax = 180,
	baseXp = 714,
	baseHAM = 1500,
	baseHAMmax = 1900,
	armor = 0,
	resists = {0,0,0,20,0,0,0,-1,-1},
	meatType = "meat_herbivore",
	meatAmount = 400,
	hideType = "hide_wooly",
	hideAmount = 300,
	boneType = "bone_mammal",
	boneAmount = 200,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = NONE,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/bantha.iff"},
	lootgroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"stunattack","stunChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(rogue_bantha, "rogue_bantha")