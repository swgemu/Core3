odoof_grunda = Creature:new {
  objectName = "",
  customName = "Odoof Grunda",
  socialGroup = "townsperson",
  faction = "townsperson",
  level = 100,
  chanceHit = 1,
  damageMin = 645,
  damageMax = 1000,
  baseXp = 9429,
  baseHAM = 24000,
  baseHAMmax = 30000,
  armor = 0,
  resists = {0,0,0,0,0,0,0,0,-1},
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

  templates = {"object/mobile/gungan_male.iff"},
  lootGroups = {},
  weapons = {},
  conversationTemplate = "jaleela_bindoo_mission_target_convotemplate",
  attacks = {
  }
}

CreatureTemplates:addCreatureTemplate(odoof_grunda, "odoof_grunda")
