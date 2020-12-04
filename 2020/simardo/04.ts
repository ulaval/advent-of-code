// https://github.com/simardo/adventofcode2020/tree/main/src/04

console.log('4 décembre');

function getPassports(input: string): any[] {
    const batch: string[] = input.split('\n');
    batch.push('');
    const passports: any[] = [];
    while (batch.length > 0) {
        const pinfo: string[] = batch.splice(0, batch.indexOf('') + 1);
        const passport: any = pinfo.reduce((a, p) => {
            p.split(' ').map(li => li.split(':')).reduce((aa, i) => {
                aa[i[0]] = i[1];
                return aa;
            }, a);
            return a;
        }, {} as any);
        passports.push(passport);
    }

    return passports;
}

// part 1
function doPart1(input: string): void {
    const passports: any[] = getPassports(input);

    const crit: string[] = ['byr', 'iyr', 'eyr', 'hgt', 'hcl', 'ecl', 'pid'];
    const valid: number = passports.reduce((a, p) => crit.every(c => p[c] !== undefined) ? a + 1 : a, 0);

    console.log(valid);
}

doPart1(INPUT);

// part 2
function doPart2(input: string): void {
    const byr = (s: string) => s.length === 4 && s.match(/\d{4}/) !== null && Number.parseInt(s) >= 1920 && Number.parseInt(s) <= 2002;
    const iyr = (s: string) => s.length === 4 && s.match(/\d{4}/) !== null && Number.parseInt(s) >= 2010 && Number.parseInt(s) <= 2020;
    const eyr = (s: string) => s.length === 4 && s.match(/\d{4}/) !== null && Number.parseInt(s) >= 2020 && Number.parseInt(s) <= 2030;
    const hgt = (s: string) => {
        const m: RegExpMatchArray | null = s.match(/(\d+)(cm|in)/);
        if (m !== null) {
            const height: number = Number.parseInt(m[1]);
            return m[2] === 'cm' && height >= 150 && height <= 193 || m[2] === 'in' && height >= 59 && height <= 76;
        } else {
            return false;
        }
    };
    const hcl = (s: string) => s.length === 7 && s.match(/\#(([0-9]|[a-f]){6})/) !== null;
    const ecl = (s: string) => ['amb', 'blu', 'brn', 'gry', 'grn', 'hzl', 'oth'].indexOf(s) >= 0;
    const pid = (s: string) => s.length === 9 && s.match(/\d{9}/) !== null;

    const crit: any[][] = [['byr', byr], ['iyr', iyr], ['eyr', eyr], ['hgt', hgt], ['hcl', hcl], ['ecl', ecl], ['pid', pid]];

    const passports: any[] = getPassports(input);
    const valid: number = passports.reduce((a, p) => crit.every(c => p[c[0]] !== undefined && c[1](p[c[0]])) ? a + 1 : a, 0);

    console.log(valid);
}

doPart2(INPUT);
