thune_grassland_guardian = Creature:new {
	objectName = "@mob/creature_names:thune_grassland_guardian",
	socialGroup = "thune",
	faction = "",
	level = 40,
	chanceHit = 0.44,
	damageMin = 345,
	damageMax = 400,
	baseXp = 3915,
	baseHAM = 8300,
	baseHAMmax = 11300,
	armor = 0,
	resists = {145,160,30,-1,-1,-1,-1,-1,-1},
	meatType = "meat_herbivore",
	meatAmount = 135,
	hideType = "hide_wooly",
	hideAmount = 150,
	boneType = "",
	boneAmount = 0,
	milkType = "milk_wild",
	milk = 65,
	tamingChance = 0.15,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/thune_grassland_guardian.iff"},
	controlDeviceTemplate = "object/intangible/pet/thune_hue.iff",
	scale = 1.1,
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"dizzyattack",""},
		{"posturedownattack",""}
	}
}

CreatureTemplates:addCreatureTemplate(thune_grassland_guardian, "thune_grassland_guardian")
