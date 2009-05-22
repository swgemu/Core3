TRUNCATE `swgemu`.`structures`;
TRUNCATE `swgemu`.`harvester_hoppers`;
UPDATE `swgemu`.`characters` SET `lots` = 10;
DELETE FROM `swgemu`.`character_items` WHERE `template_type` = 8388610;