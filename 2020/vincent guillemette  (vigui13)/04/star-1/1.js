const fs = require('fs');
const readline = require('readline');

const readInterface = readline.createInterface({
    input: fs.createReadStream('./input.txt'),
});

let passports = [];
let raw = [];
const fields = ['byr', 'iyr', 'eyr', 'hgt', 'hcl', 'ecl', 'pid'];

readInterface
    .on('line', (line) => {
        raw.push(line);
    })
    .on('close', () => {
        while (raw.length) {
            let emptyLineIndex = raw.indexOf('');

            if (emptyLineIndex === -1) {
                emptyLineIndex = raw.length;
            }

            const passport = raw
                .slice(0, emptyLineIndex)
                .reduce((acc, cur) => ((acc += ' ' + cur), acc), '');

            raw = raw.slice(emptyLineIndex + 1);
            passports.push(passport.trim());
        }

        console.log(
            passports.filter((p) => {
                const parts = p.split(' ');
                const passportFields = parts.map((p) => p.split(':')[0]);
                return fields.every((f) => {
                    return passportFields.includes(f);
                });
            }).length
        );
    });
