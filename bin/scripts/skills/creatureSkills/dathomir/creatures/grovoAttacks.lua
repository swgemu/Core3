grovoAttack1 = {
        attackname = "grovoAttack1",
        animation = "creature_attack_light",
        
        requiredWeaponType = NONE,

        range = 7,

        damageRatio = 1.2,

        speedRatio = 4,

        arearange = 7,
        accuracyBonus = 0,

        healthAttackChance = 100,
        actionAttackChance = 0,
        mindAttackChance = 0,

        dotChance = 50,
        tickStrengthOfHit = 1,

        fireStrength = 0,
        fireType = 0,

        bleedingStrength = 100,
		bleedingType = HEALTH,

        poisonStrength = 0,
        poisonType = 0,

        diseaseStrength = 0,
        diseaseType = 0,
                
        knockdownChance = 0,
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
}

AddDotPoolAttackTargetSkill(grovoAttack1)

--------------------------------------------------------------------------------------

grovoAttack2 = { 
        attackname = "grovoAttack2",
        animation = "creature_attack_light",

        requiredWeaponType = NONE,
        
        range = 7,
        damageRatio = 1.2,
        speedRatio = 1.45,
        arearange = 7,
        accuracyBonus = 0,

        healthAttackChance = 0,
        strengthAttackChance = 0,
        constitutionAttackChance = 0,

        actionAttackChance = 50,
        quicknessAttackChance = 0,
        staminaAttackChance = 0,

        mindAttackChance = 100,
        focusAttackChance = 0,
        willpowerAttackChance = 0,
                
        knockdownChance = 50,
        postureDownChance = 0,
        dizzyChance = 0,
        blindChance = 0,
        stunChance = 0,
        intimidateChance = 0,
        
        CbtSpamBlock = "melee_block",
        CbtSpamCounter = "melee_counter",
        CbtSpamEvade = "melee_evade",
        CbtSpamHit = "melee_hit",
        CbtSpamMiss = "melee_miss",
}

AddDirectPoolAttackTargetSkill(grovoAttack2)

--------------------------------------------------------------------------------------
