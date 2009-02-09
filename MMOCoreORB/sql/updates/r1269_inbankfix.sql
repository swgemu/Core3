ALTER TABLE `swgemu`.`character_items` MODIFY COLUMN `in_bank` TINYINT(3) UNSIGNED NOT NULL DEFAULT 0;
UPDATE `swgemu`.`character_items` SET `in_bank` = 0;