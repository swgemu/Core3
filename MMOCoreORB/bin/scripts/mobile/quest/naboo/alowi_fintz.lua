alowi_fintz = Creature:new {
  objectName = "",
  customName = "Alowi Fintz",
  socialGroup = "rebel",
  faction = "rebel",
  mobType = MOB_NPC,
  level = 20,
  chanceHit = 0.33,
  damageMin = 180,
  damageMax = 190,
  baseXp = 1803,
  baseHAM = 4500,
  baseHAMmax = 5500,
  armor = 0,
  resists = {10,15,0,40,-1,40,0,-1,-1},
  meatType = "",
  meatAmount = 0,
  hideType = "",
  hideAmount = 0,
  boneType = "",
  boneAmount = 0,
  milk = 0,
  tamingChance = 0,
  ferocity = 0,
  pvpBitmask = NONE,
  creatureBitmask = NONE,
  optionsBitmask = AIENABLED + CONVERSABLE,
  diet = HERBIVORE,

  templates = {"object/mobile/dressed_criminal_smuggler_human_female_01.iff"},
  lootGroups = {},
  primaryWeapon = "pirate_weapons_heavy",
	secondaryWeapon = "unarmed",
  conversationTemplate = "arven_wendik_mission_target_convotemplate",
  
	-- primaryAttacks and secondaryAttacks should be separate skill groups specific to the weapon type listed in primaryWeapon and secondaryWeapon
	-- Use merge() to merge groups in creatureskills.lua together. If a weapon is set to "none", set the attacks variable to empty brackets
	primaryAttacks = merge(riflemanmaster,pistoleermaster,carbineermaster,brawlermaster),
	secondaryAttacks = { }
}

CreatureTemplates:addCreatureTemplate(alowi_fintz, "alowi_fintz")
