import { INPUT } from './input.ts';

const TEST1: string = `16,1,2,0,4,2,7,1,2,14`;

function doPart(input: string): string | number {
    const nums: number[] = input.split(',').map(s => Number.parseInt(s));

    const max = nums.reduce((p, n) => Math.max(n, p), Number.MIN_VALUE);

    let fuel: number = Number.MAX_VALUE;
    for (let i: number = 0; i <= max; i++) {
        fuel = Math.min(fuel, nums.reduce((p, n) => p + (Math.abs(n - i)), 0));
    }

    return fuel;
}

function go(input: string, expected?: number | string): void {
    const result: number | string = doPart(input);
    console.log(`--> ${result} <--`);
    console.assert(!expected || result === expected, 'got: %s, expected: %s', result, expected);
}

void (() => {
    go(TEST1, 37);
    go(INPUT);
})();

/*
const RE: RegExp = /(\d+)\s<->\s(.+)/g;

let match: RegExpMatchArray | null;
while ((match = RE.exec(input)) !== null) {
    const [, id, ids] = match;
}
*/
