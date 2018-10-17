ALTER TABLE `swgemu`.`deleted_characters` ADD COLUMN `db_deleted` BOOLEAN  NOT NULL DEFAULT 0 AFTER `creation_date`;
