kimogila_dwarf = Creature:new {
	objectName = "@mob/creature_names:kimogila_dwarf",
	socialGroup = "kimogila",
	faction = "",
	level = 139,
	chanceHit = 4.5,
	damageMin = 800,
	damageMax = 1400,
	baseXp = 12671,
	baseHAM = 71000,
	baseHAMmax = 79000,
	armor = 2,
	resists = {135,180,20,180,20,20,200,20,-1},
	meatType = "meat_carnivore",
	meatAmount = 1000,
	hideType = "hide_leathery",
	hideAmount = 1000,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0,
	ferocity = 20,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK + KILLER,
	optionsBitmask = AIENABLED,
	diet = CARNIVORE,

	templates = {"object/mobile/kimogila_hue.iff"},
	hues = { 16, 17, 18, 19, 20, 21, 22, 23 },
	scale = 0.8,
	lootGroups = {
	 {
	        groups = {
				{group = "kimogila_common", chance = 10000000}
			},
			lootChance = 3460000
		}
	},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"posturedownattack",""},
		{"dizzyattack",""}
	}
}

CreatureTemplates:addCreatureTemplate(kimogila_dwarf, "kimogila_dwarf")
