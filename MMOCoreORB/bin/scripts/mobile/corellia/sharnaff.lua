sharnaff = Creature:new {
	objectName = "@mob/creature_names:sharnaff",
	socialGroup = "sharnaff",
	faction = "",
	level = 31,
	chanceHit = 0.38,
	damageMin = 300,
	damageMax = 310,
	baseXp = 3005,
	baseHAM = 8600,
	baseHAMmax = 10600,
	armor = 0,
	resists = {15,15,15,120,120,120,120,150,-1},
	meatType = "meat_carnivore",
	meatAmount = 450,
	hideType = "hide_scaley",
	hideAmount = 300,
	boneType = "bone_mammal",
	boneAmount = 180,
	milkType = "milk_wild",
	milk = 220,
	tamingChance = 0,
	ferocity = 2,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = NONE,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/sharnaff.iff"},
	lootGroups = {
		{
			groups = {
				{group = "sharnaff_common", chance = 10000000}
			},
			lootChance = 1620000
		}
	},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"dizzyattack",""},
		{"stunattack",""}
	}
}

CreatureTemplates:addCreatureTemplate(sharnaff, "sharnaff")
