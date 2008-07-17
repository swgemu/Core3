/* You may have to enter each of these commands manually for it to work */

ALTER TABLE `characters` ADD COLUMN `adminLevel` TINYINT(1) UNSIGNED NOT NULL DEFAULT 4 AFTER `BattleFatigue`;
UPDATE `characters` SET adminLevel = 2 WHERE (firstname = 'ramsey' or firstname = 'ultyma' or firstname = 'seaseme' or firstname = 'theanswer' or firstname = 'oru' or firstname = 'smusatto' or firstname = 'phantm' or firstname = 'vash' or firstname = 'mcmahon' or firstname = 'bobius' or firstname = 'kellina' or firstname = 'kyle' or firstname = 'panchjr');
UPDATE `characters` SET adminLevel = 1 WHERE (firstname = 'ekaika' or firstname = 'learningdisease' or firstname = 'megatron' or firstname = 'serpentkaa' or firstname = 'tolbat' or firstname = 'vashman');