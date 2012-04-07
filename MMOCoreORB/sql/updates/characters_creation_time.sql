ALTER TABLE `swgemu`.`characters` ADD COLUMN `creation_date` TIMESTAMP  NOT NULL AFTER `template`;
ALTER TABLE `swgemu`.`characters_dirty` ADD COLUMN `creation_date` TIMESTAMP  NOT NULL AFTER `template`;
