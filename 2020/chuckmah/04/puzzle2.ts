import * as fs from 'fs';
import * as path from 'path';
import * as _ from 'lodash';

const input = fs.readFileSync('input.txt', 'utf8').toString().replace(/\r\n/g, '\n');
const passportsInput = input.split('\n\n');

const passports = passportsInput.map(passportInput => {
    const keyPairs = _.split(passportInput, /\s/g).map(keyPair => {
        return _.split(keyPair, ':');
    })
    return _.fromPairs(keyPairs);
})


type Passport = {
    byr: string;
    iyr: string;
    eyr: string;
    hgt: string;
    hcl: string;
    ecl: string;
    pid: string;
    cid?: string;
}

//typecheck!
const isPassport = (passportToCheck: any): passportToCheck is Passport => {
    return (passportToCheck as Passport).byr !== undefined && (passportToCheck as Passport).iyr !== undefined 
    && (passportToCheck as Passport).eyr !== undefined && (passportToCheck as Passport).hgt !== undefined
    && (passportToCheck as Passport).hcl !== undefined && (passportToCheck as Passport).ecl !== undefined
    && (passportToCheck as Passport).pid !== undefined
}

//validation
const isValidPassport = (passportToCheck: Passport) : boolean => {
    //byr (Birth Year) - four digits; at least 1920 and at most 2002.
    if(passportToCheck.byr.trim().length !== 4 || Number(passportToCheck.byr) < 1920 || Number(passportToCheck.byr) > 2002){
        return false;
    }
    //iyr (Issue Year) - four digits; at least 2010 and at most 2020.
    if(passportToCheck.iyr.trim().length !== 4 || Number(passportToCheck.iyr) < 2010 || Number(passportToCheck.iyr) > 2020){
        return false;
    }
    //eyr (Expiration Year) - four digits; at least 2020 and at most 2030.
    if(passportToCheck.eyr.trim().length !== 4 || Number(passportToCheck.eyr) < 2020 || Number(passportToCheck.eyr) > 2030){
        return false;
    }
    //hgt (Height) - a number followed by either cm or in:
    if(_.endsWith(passportToCheck.hgt, 'cm') ||  _.endsWith(passportToCheck.hgt, 'in')){
        //If cm, the number must be at least 150 and at most 193.
        if(_.endsWith(passportToCheck.hgt, 'cm')){
           let heightInCm = _.split(passportToCheck.hgt, 'cm')[0];
           if(Number(heightInCm) < 150 || Number(heightInCm) > 193){
            return false;
           }
        }

        //If in, the number must be at least 59 and at most 76.
        if(_.endsWith(passportToCheck.hgt, 'in')){
            let heightInInch = _.split(passportToCheck.hgt, 'in')[0];
            if(Number(heightInInch) < 59 || Number(heightInInch) > 76){

             return false;
            }
         }
    }else{
        return false;
    }

    //hcl (Hair Color) - a # followed by exactly six characters 0-9 or a-f.
    if(passportToCheck.hcl.length !== 7 || !_.startsWith(passportToCheck.hcl, '#') || !passportToCheck.hcl.match(/^[#a-z0-9]+$/g)){
        return false;
    }


    //ecl (Eye Color) - exactly one of: amb blu brn gry grn hzl oth.
    if(! (['amb','blu','brn','gry', 'grn', 'hzl', 'oth'].includes(passportToCheck.ecl.trim()))){
        return false;
    }
 

    //pid (Passport ID) - a nine-digit number, including leading zeroes.
    if(passportToCheck.pid.trim().length !== 9 || !passportToCheck.pid.match(/^[0-9]+$/g) ){
        return false;
    }

    return true;
}

let valid = 0;
passports.forEach((passport: unknown, index) => {
    if( isPassport(passport)){
        if(isValidPassport(passport)){
            valid++;
        }

    } else {

    }
});  
console.log(valid);
