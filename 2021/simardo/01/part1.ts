import { INPUT } from './input.ts';

const TEST1: string = `199
200
208
210
200
207
240
269
260
263`;

function doPart1(input: string): void {
    const depths: number[] = input.split('\n').map(s => Number.parseInt(s));

    const increases: number = depths.filter((_, i) => i > 0).reduce((p, d, i) => d > depths[i] ? p + 1 : p, 0);

    console.log(increases);
}

doPart1(TEST1);
doPart1(INPUT);
