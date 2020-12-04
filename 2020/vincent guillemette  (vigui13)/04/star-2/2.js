const fs = require('fs');
const readline = require('readline');
const { indexOf } = require('../../03/star-2/2-input');

const readInterface = readline.createInterface({
    input: fs.createReadStream('./input.txt'),
});

let passports = [];
let raw = [];
const fields = [
    {
        code: 'byr',
        validation: (value) => {
            return !isNaN(value) && value >= 1920 && value <= 2002;
        },
    },
    {
        code: 'iyr',
        validation: (value) => {
            return !isNaN(value) && value >= 2010 && value <= 2020;
        },
    },
    {
        code: 'eyr',
        validation: (value) => {
            return !isNaN(value) && value >= 2020 && value <= 2030;
        },
    },
    {
        code: 'hgt',
        validation: (value) => {
            const units = value.slice(value.length - 2).trim();
            const amount = parseInt(value.slice(0, value.length - 1).trim());

            return units === 'cm'
                ? !isNaN(amount) && amount >= 150 && amount <= 193
                : !isNaN(amount) && amount >= 59 && amount <= 76;
        },
    },
    {
        code: 'hcl',
        validation: (value) => {
            return RegExp('^#[0-9|a-f]{6}$', 'g').test(value);
        },
    },
    {
        code: 'ecl',
        validation: (value) => {
            return ['amb', 'blu', 'brn', 'gry', 'grn', 'hzl', 'oth'].includes(
                value
            );
        },
    },
    {
        code: 'pid',
        validation: (value) => {
            return RegExp('^[0-9]{9}$', 'g').test(value);
        },
    },
];

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
                const passportFields = parts.map((p) => ({
                    code: p.split(':')[0],
                    value: p.split(':')[1],
                }));
                return fields.every((f) => {
                    const match = passportFields.find((p) => p.code === f.code);

                    return !!match && f.validation(match.value);
                });
            }).length
        );
    });
