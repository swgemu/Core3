razorCatAttack1 = {
        attackname = "razorCatAttack1",
        animation = "creature_attack_light",
        
        requiredWeaponType = NONE,

        range = 7,

        damageRatio = 1.2,

        speedRatio = 4,

        arearange = 7,
        accuracyBonus = 0,
                
        knockdownChance = 50,
        postureDownChance = 0,
        postureUpChance = 0,
        dizzyChance = 0,
        blindChance = 0,
        stunChance = 0,
        intimidateChance = 0,
        
        CbtSpamBlock = "attack_block",
        CbtSpamCounter = "attack_counter",
        CbtSpamEvade = "attack_evade",
        CbtSpamHit = "attack_hit",
        CbtSpamMiss = "attack_miss",

	invalidStateMask = 0,
	invalidPostures = "",
	instant = 0
}

AddRandomPoolAttackTargetSkill(razorCatAttack1)

---------------------------------------------------------------------------------------

razorCatAttack2 = {
        attackname = "razorCatAttack2",
        animation = "creature_attack_light",
        
        requiredWeaponType = NONE,

        range = 7,

        damageRatio = 1.2,

        speedRatio = 4,

        arearange = 7,
        accuracyBonus = 0,
                
        knockdownChance = 0,
        postureDownChance = 0,
        postureUpChance = 0,
        dizzyChance = 0,
        blindChance = 0,
        stunChance = 0,
        intimidateChance = 50,
        
        CbtSpamBlock = "attack_block",
        CbtSpamCounter = "attack_counter",
        CbtSpamEvade = "attack_evade",
        CbtSpamHit = "attack_hit",
        CbtSpamMiss = "attack_miss",

	invalidStateMask = 0,
	invalidPostures = "",
	instant = 0
}

AddRandomPoolAttackTargetSkill(razorCatAttack2)

---------------------------------------------------------------------------------------
