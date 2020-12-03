// https://github.com/simardo/adventofcode2020/tree/main/src/02

import { INPUT, TEST_1 } from './input.ts';

console.log('2 décembre');

const rx: RegExp = /(\d+)-(\d+)\s(\w):\s(\w+)/g;

// part 1
function doPart1(input: string): void {
    let match: RegExpMatchArray | null;
    let valid: number = 0;

    while ((match = rx.exec(input)) !== null) {
        const min: number = Number.parseInt(match[1]);
        const max: number = Number.parseInt(match[2]);
        const char: string = match[3];
        const pwd: string = match[4];

        const occ: number = [...pwd].reduce((p,s) => s === char ? p + 1 : p, 0);
        if (occ >= min && occ <= max) {
            valid++;
        }
    }

    console.log(valid);
}

doPart1(INPUT);

// part 2
function doPart2(input: string): void {
    let match: RegExpMatchArray | null;
    let valid: number = 0;

    while ((match = rx.exec(input)) !== null) {
        const idx1: number = Number.parseInt(match[1]);
        const idx2: number = Number.parseInt(match[2]);
        const char: string = match[3];
        const pwd: string = match[4];

        if ((pwd[idx1-1] === char) !== (pwd[idx2-1] === char)) {
            valid++;
        }
    }

    console.log(valid);
}

doPart2(INPUT);
