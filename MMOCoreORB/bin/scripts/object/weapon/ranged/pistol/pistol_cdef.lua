
object_weapon_ranged_pistol_pistol_cdef = object_weapon_ranged_pistol_shared_pistol_cdef:new {

	attackType = RANGEDATTACK,
	damageType = ENERGY,
	
	certificationsRequired = { "cert_pistol_cdef" },
	
	creatureAccuracyModifiers = { "pistol_accuracy" },
	defenderDefenseModifiers = { "ranged_defense" },
	speedModifiers = { "pistol_speed" },
	damageModifiers = { }
	
}

ObjectTemplates:addTemplate(object_weapon_ranged_pistol_pistol_cdef, "object/weapon/ranged/pistol/pistol_cdef.iff")
