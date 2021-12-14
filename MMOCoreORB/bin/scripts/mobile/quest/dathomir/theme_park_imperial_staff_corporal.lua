theme_park_imperial_staff_corporal = Creature:new {
  objectName = "@mob/creature_names:imperial_staff_corporal",
  randomNameType = NAME_GENERIC,
  randomNameTag = true,
	mobType = MOB_NPC,
  socialGroup = "imperial",
  faction = "imperial",
  level = 17,
  chanceHit = 0.32,
  damageMin = 160,
  damageMax = 170,
  baseXp = 112,
  baseHAM = 3500,
  baseHAMmax = 4300,
  armor = 0,
  resists = {0,0,0,0,0,0,0,-1,-1},
  meatType = "",
  meatAmount = 0,
  hideType = "",
  hideAmount = 0,
  boneType = "",
  boneAmount = 0,
  milk = 0,
  tamingChance = 0,
  ferocity = 0,
  pvpBitmask = ATTACKABLE,
  creatureBitmask = PACK,
  optionsBitmask = AIENABLED + CONVERSABLE,
  diet = HERBIVORE,

  templates = {"object/mobile/dressed_imperial_soldier_m.iff"},
  lootGroups = {},
  primaryWeapon = "unarmed",
	secondaryWeapon = "none",
  conversationTemplate = "theme_park_nightsister_mission_target_convotemplate",
  
	-- primaryAttacks and secondaryAttacks should be separate skill groups specific to the weapon type listed in primaryWeapon and secondaryWeapon
	-- Use merge() to merge groups in creatureskills.lua together. If a weapon is set to "none", set the attacks variable to empty brackets
	primaryAttacks = merge(brawlermaster,marksmanmaster),
	secondaryAttacks = { }
}

CreatureTemplates:addCreatureTemplate(theme_park_imperial_staff_corporal, "theme_park_imperial_staff_corporal")