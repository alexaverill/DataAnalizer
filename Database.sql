-- MySQL Workbench Forward Engineering

SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0;
SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0;
SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='TRADITIONAL,ALLOW_INVALID_DATES';

-- -----------------------------------------------------
-- Schema mydb
-- -----------------------------------------------------

-- -----------------------------------------------------
-- Schema mydb
-- -----------------------------------------------------
CREATE SCHEMA IF NOT EXISTS `mydb` DEFAULT CHARACTER SET utf8 ;
USE `mydb` ;

-- -----------------------------------------------------
-- Table `mydb`.`Samples`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `mydb`.`Samples` ;

CREATE TABLE IF NOT EXISTS `mydb`.`Samples` (
  `idSamples` INT NOT NULL AUTO_INCREMENT,
  `SampleName` VARCHAR(45) NULL,
  PRIMARY KEY (`idSamples`))
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `mydb`.`Temperatures`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `mydb`.`Temperatures` ;

CREATE TABLE IF NOT EXISTS `mydb`.`Temperatures` (
  `idTemperatures` INT NOT NULL AUTO_INCREMENT,
  `temperature` VARCHAR(45) NULL,
  PRIMARY KEY (`idTemperatures`))
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `mydb`.`trial`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `mydb`.`trial` ;

CREATE TABLE IF NOT EXISTS `mydb`.`trial` (
  `idtrial` INT NOT NULL,
  `replicantID` INT NULL,
  `sampleID` INT NULL,
  `temperatureID` INT NULL,
  PRIMARY KEY (`idtrial`),
  INDEX `samples_idx` (`sampleID` ASC),
  INDEX `temperature_idx` (`temperatureID` ASC),
  CONSTRAINT `samples`
    FOREIGN KEY (`sampleID`)
    REFERENCES `mydb`.`Samples` (`idSamples`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `temperature`
    FOREIGN KEY (`temperatureID`)
    REFERENCES `mydb`.`Temperatures` (`idTemperatures`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `mydb`.`data`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `mydb`.`data` ;

CREATE TABLE IF NOT EXISTS `mydb`.`data` (
  `iddata` INT NOT NULL AUTO_INCREMENT,
  `trialID` INT NULL,
  `rxntemp` MEDIUMTEXT NULL,
  `rxnTime` MEDIUMTEXT NULL,
  `rxnheatFlow` MEDIUMTEXT NULL,
  `rxnrevCP` MEDIUMTEXT NULL,
  `rxnArea` MEDIUMTEXT NULL,
  PRIMARY KEY (`iddata`),
  INDEX `trialNum_idx` (`trialID` ASC),
  CONSTRAINT `trialNum`
    FOREIGN KEY (`trialID`)
    REFERENCES `mydb`.`trial` (`idtrial`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


SET SQL_MODE=@OLD_SQL_MODE;
SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS;
SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS;
