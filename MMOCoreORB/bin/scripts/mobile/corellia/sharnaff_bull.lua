sharnaff_bull = Creature:new {
	objectName = "@mob/creature_names:sharnaff_bull",
	socialGroup = "sharnaff",
	pvpFaction = "",
	faction = "",
	level = 38,
	chanceHit = 0.41,
	damageMin = 335,
	damageMax = 380,
	baseXp = 3733,
	baseHAM = 9400,
	baseHAMmax = 11400,
	armor = 0,
	resists = {25,25,25,120,120,120,120,150,-1},
	meatType = "meat_carnivore",
	meatAmount = 482,
	hideType = "hide_scaley",
	hideAmount = 335,
	boneType = "bone_mammal",
	boneAmount = 200,
	milk = 0,
	tamingChance = 0,
	ferocity = 8,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/sharnaff_bull.iff"},
	lootGroups = {
		{
			groups = {
				{group = "sharnaff_common", chance = 10000000}
			},
			lootChance = 3300000
		}
	},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"dizzyattack","dizzyChance=50"},
		{"stunattack","stunChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(sharnaff_bull, "sharnaff_bull")
