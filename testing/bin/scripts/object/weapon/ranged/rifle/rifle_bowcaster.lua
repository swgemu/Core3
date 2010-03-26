object_weapon_ranged_rifle_rifle_bowcaster = object_weapon_ranged_rifle_shared_rifle_bowcaster:new {

	attackType = RANGEDATTACK,
	damageType = ENERGY,

	certificationsRequired = { "cert_rifle_bowcaster" },
	
	creatureAccuracyModifiers = { "rifle_accuracy" },
	defenderDefenseModifiers = { "ranged_defense" },
	speedModifiers = { "rifle_speed" },
	damageModifiers = { }
	
}

ObjectTemplates:addTemplate(object_weapon_ranged_rifle_rifle_bowcaster, "object/weapon/ranged/rifle/rifle_bowcaster.iff")
