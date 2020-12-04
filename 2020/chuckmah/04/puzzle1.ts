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


let valid = 0;
passports.forEach((passport: unknown, index) => {
    if( isPassport(passport)){

        valid++;
    }

});  
console.log(valid);
