sharnaff_reckless_ravager = Creature:new {
	objectName = "@mob/creature_names:sharnaff_reckless_ravager",
	socialGroup = "Sharnaff",
	pvpFaction = "",
	faction = "",
	level = 34,
	chanceHit = 0.410000,
	damageMin = 315,
	damageMax = 340,
	baseXp = 3460,
	baseHAM = 9800,
	baseHAMmax = 9800,
	armor = 0,
	resists = {15,15,0,20,20,20,20,20,-1},
	meatType = "meat_carnivore",
	meatAmount = 450,
	hideType = "hide_scaley",
	hideAmount = 300,
	boneType = "bone_mammal",
	boneAmount = 180,
	milk = 0,
	tamingChance = 0.050000,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = KILLER + PACK,
	diet = CARNIVORE,

	templates = {"object/mobile/sharnaff.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"dizzyattack","dizzyChance=50"},
		{"knockdownattack","knockdownChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(sharnaff_reckless_ravager, "sharnaff_reckless_ravager")