import fs from 'fs';

const passports: Map<string, string>[] = fs.readFileSync(__dirname + '/data-4.txt', 'utf8').split('\n\n')
    .map((passport: string): [string, string][] => replaceAll(passport, '\n', ' ').split(' ')
        .map((keyValue): [string, string] => keyValue.split(':')
            .reduce((acc, value) => acc[0] === '' ? [value, ''] : [acc[0], value], ['', ''])))
    .map((passport: [string, string][]) => new Map(passport));

function replaceAll(string: string, search: string, replace: string): string {
    return string.split(search).join(replace);
}

const passportsWithRequiredFields: Map<string, string>[] = passports.filter((passport: Map<string, string>) => passport.size === 8 || passport.size === 7 && !passport.has('cid'));

console.log(passportsWithRequiredFields.length);


const checkHeight = (height: string) => {
    const numericValue = Number(height.replace(/(cm|in)/, ''));
    return (height.indexOf('cm') !== -1) ? numericValue >= 150 && numericValue <= 193 : numericValue >= 59 && numericValue <= 76;
}

const validPassports: Map<string, string>[] = passportsWithRequiredFields.filter((passport: Map<string, string>) =>
    Number(passport.get('byr')) >= 1920 && Number(passport.get('byr')) <= 2002
    && Number(passport.get('iyr')) >= 2010 && Number(passport.get('iyr')) <= 2020
    && Number(passport.get('eyr')) >= 2020 && Number(passport.get('eyr')) <= 2030
    && checkHeight(passport.get('hgt')!)
    && passport.get('hcl')?.charAt(0) === '#' && passport.get('hcl')?.length === 7
    && 'amb blu brn gry grn hzl oth'.split(' ').includes(passport.get('ecl') || '')
    && passport.get('pid')!.length === 9 && !isNaN(Number(passport.get('pid')))
)

console.log(validPassports.length);
