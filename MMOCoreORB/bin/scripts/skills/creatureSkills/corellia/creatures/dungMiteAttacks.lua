dungMiteAttack1 = {
        attackname = "dungMiteAttack1",
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
        stunChance = 50,
        intimidateChance = 0,
        
        CbtSpamBlock = "attack_block",
        CbtSpamCounter = "attack_counter",
        CbtSpamEvade = "attack_evade",
        CbtSpamHit = "attack_hit",
        CbtSpamMiss = "attack_miss",
}

AddRandomPoolAttackTargetSkill(dungMiteAttack1)

---------------------------------------------------------------------------------------

dungMiteAttack2 = {
        attackname = "dungMiteAttack2",
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

        bleedingStrength = 0,
		bleedingType = 0,

        poisonStrength = 0,
        poisonType = 0,

        diseaseStrength = 100,
        diseaseType = HEALTH,
                
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

AddDotPoolAttackTargetSkill(dungMiteAttack2)

--------------------------------------------------------------------------------------
dungMiteAttack3 = {
        attackname = "dungMiteAttack3",
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
}

AddRandomPoolAttackTargetSkill(dungMiteAttack3)

---------------------------------------------------------------------------------------
