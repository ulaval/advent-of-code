import { readFileSync } from "fs";

const data: string[] = readFileSync("./input.txt", "utf8").split("\n");
const fields: string[] = [
  "byr:",
  "iyr:",
  "eyr:",
  "hgt:",
  "hcl:",
  "ecl:",
  "pid:",
];
const numRegExp = new RegExp("^[0-9]*$");
const numAFRegExp = new RegExp("^[A-Fa-f0-9 -]*$");

let validPassportsBasic: number = 0;
let validPassportsAdvance: number = 0;

const validatePassportBasic = (passport: string): boolean =>
  fields.every((field) => passport.includes(field));

const validatePassportAdvance = (passport: string): boolean => {
  if (validatePassportBasic(passport)) {
    const passportFields: string[] = passport.split(" ");

    return passportFields.every((field) => {
      switch (field.substr(0, 4)) {
        case "byr:":
          const byr: string = field.substring(4);
          return (
            byr.length === 4 &&
            !!byr.match(numRegExp) &&
            parseInt(byr) >= 1920 &&
            parseInt(byr) <= 2002
          );
        case "iyr:":
          const iyr: string = field.substring(4);
          return (
            iyr.length === 4 &&
            !!iyr.match(numRegExp) &&
            parseInt(iyr) >= 2010 &&
            parseInt(iyr) <= 2020
          );
        case "eyr:":
          const eyr: string = field.substring(4);
          return (
            eyr.length === 4 &&
            !!eyr.match(numRegExp) &&
            parseInt(eyr) >= 2020 &&
            parseInt(eyr) <= 2030
          );
        case "hgt:":
          const hgt: string = field.substring(4);
          const hgtVal: string = hgt.substring(0, hgt.length - 2);
          const hgtUnit: string = hgt.substring(hgt.length - 2);
          if (hgtUnit === "cm") {
            return (
              !!hgtVal.match(numRegExp) &&
              parseInt(hgtVal) >= 150 &&
              parseInt(hgtVal) <= 193
            );
          } else {
            return (
              !!hgtVal.match(numRegExp) &&
              parseInt(hgtVal) >= 59 &&
              parseInt(hgtVal) <= 76
            );
          }
        case "hcl:":
          const hcl: string = field.substring(4);
          return (
            hcl.substr(0, 1) === "#" &&
            hcl.substr(1).length === 6 &&
            !!hcl.substr(1).match(numAFRegExp)
          );
        case "ecl:":
          return "amb blu brn gry grn hzl oth".includes(field.substring(4));
        case "pid:":
          const pid: string = field.substring(4);
          return pid.length <= 9 && !!pid.match(numRegExp);
        default:
          return true;
      }
    });
  }
  return false;
};

data.reduce((acc: string, line: string, index) => {
  acc += line + " ";
  if (line === "\r" || index === data.length - 1) {
    acc = acc.replace(/(\r\n|\n|\r)/gm, "");
    if (validatePassportBasic(acc)) validPassportsBasic++;
    if (validatePassportAdvance(acc)) validPassportsAdvance++;
    acc = "";
  }

  return acc;
});

console.log(validPassportsBasic);
console.log(validPassportsAdvance);
