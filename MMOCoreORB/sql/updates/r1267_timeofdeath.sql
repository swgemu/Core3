/* Changes the column name of rezExpires to timeOfDeath */
ALTER TABLE `swgemu`.`characters` CHANGE COLUMN `rezExpires` `timeOfDeath` INT(8) UNSIGNED NOT NULL DEFAULT 0;
ALTER TABLE `swgemu`.`characters` MODIFY COLUMN `timeOfDeath` BIGINT(20) UNSIGNED NOT NULL DEFAULT 0;