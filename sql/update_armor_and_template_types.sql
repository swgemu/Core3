ALTER TABLE `swgemu`.`character_items`
  ADD COLUMN `armor_type` INT NOT NULL DEFAULT 0 AFTER `armor_piercing`,
  MODIFY `template_type` INT NOT NULL DEFAULT 0;