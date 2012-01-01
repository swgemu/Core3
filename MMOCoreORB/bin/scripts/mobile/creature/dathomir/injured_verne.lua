injured_verne = Creature:new {
	objectName = "@mob/creature_names:injured_verne",
	socialGroup = "Verne",
	pvpFaction = "",
	faction = "",
	level = 6,
	chanceHit = 0.25,
	damageMin = 50,
	damageMax = 55,
	baseXp = 113,
	baseHAM = 180,
	baseHAMmax = 220,
	armor = 0,
	resists = {5,5,5,0,0,0,0,-1,-1},
	meatType = "meat_wild",
	meatAmount = 30,
	hideType = "hide_leathery",
	hideAmount = 25,
	boneType = "bone_mammal",
	boneAmount = 22,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = HERD,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/verne.iff"},
	lootgroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(injured_verne, "injured_verne")