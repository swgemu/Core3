object_weapon_melee_knife_knife_survival = object_weapon_melee_knife_shared_knife_survival:new {

	attackType = MELEEATTACK,
	damageType = KINETIC,
	
	maxRange = 5,
	
	minDamage = 20,
	maxDamage = 50,
	
	xpType = "combat_meleespecialize_onehand",
	
	certificationsRequired = { "cert_knife_survival" },
	
	creatureAccuracyModifiers = { "onehandmelee_accuracy" }, 
	defenderDefenseModifiers = { "melee_defense" },
	defenderSecondaryDefenseModifiers = { "dodge" },
	speedModifiers = { "onehandmelee_speed" },
	damageModifiers = { }
	
}

ObjectTemplates:addTemplate(object_weapon_melee_knife_knife_survival, "object/weapon/melee/knife/knife_survival.iff")
