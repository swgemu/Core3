woolamander_harrower = Creature:new {
	objectName = "@mob/creature_names:woolamander_harrower",
	socialGroup = "Woolamander",
	pvpFaction = "",
	faction = "",
	level = 51,
	chanceHit = 0.51,
	damageMin = 400,
	damageMax = 510,
	baseXp = 5007,
	baseHAM = 10000,
	baseHAMmax = 13000,
	armor = 1,
	resists = {35,35,-1,60,60,60,-1,-1,-1},
	meatType = "meat_carnivore",
	meatAmount = 20,
	hideType = "hide_wooly",
	hideAmount = 20,
	boneType = "bone_mammal",
	boneAmount = 20,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = PACK + HERD + KILLER,
	optionsBitmask = 0,
	diet = HERBIVORE,

	templates = {"object/mobile/woolamander.iff"},
	lootgroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"creatureareapoison",""},
		{"knockdownattack","knockdownChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(woolamander_harrower, "woolamander_harrower")