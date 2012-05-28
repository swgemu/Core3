ALTER TABLE `swgemu`.`accounts` ADD COLUMN `salt` VARCHAR(32)  NOT NULL AFTER `admin_level`;
