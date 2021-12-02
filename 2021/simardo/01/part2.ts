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

const sum: (v: number[]) => number = v => {
    return v.reduce((p, n) => p + n, 0);
}

function doPart2(input: string): void {
    const depths: number[] = input.split('\n').map(s => Number.parseInt(s));

    let increases: number = 0;
    
    for (let i: number = 3; i < depths.length; i++) {
        if (sum(depths.slice(i - 2, i + 1)) > sum(depths.slice(i - 3, i))) {
            increases++;
        }
    }

    console.log(increases);
}

doPart2(TEST1);
doPart2(INPUT);
