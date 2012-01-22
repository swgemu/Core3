ALTER TABLE `swgemu`.`sessions` ADD COLUMN `ip` VARCHAR(15)  NOT NULL AFTER `session_id`,
 ADD COLUMN `expires` DATETIME  NOT NULL AFTER `ip`;
ALTER TABLE `swgemu`.`account_log` MODIFY COLUMN `timestamp` DATETIME  NOT NULL;
