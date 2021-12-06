import { INPUT } from './input.ts';

const TEST1: string = `00100
11110
10110
10111
10101
01111
00111
11100
10000
11001
00010
01010`;

function doPart(input: string): string | number {
    const report: number[][] = input.split('\n').map(s => [...s].map(n => Number.parseInt(n)));

    const occurences: number[] = report.reduce((p, m) => {
        m.forEach((v, i) => {
            if (v === 1) {
                p[i] = p[i] + 1;
            }
        });
        return p;
    }, new Array<number>(report[0].length).fill(0));

    const gamma: number = occurences.reverse().reduce((p, v, i) => v * 2 > report.length ? p | Math.pow(2, i): p, 0);
    const ones: number = Math.pow(2, report[0].length) - 1;
    const epsilon = gamma ^ ones;

    return gamma * epsilon;
}

function go(input: string, expected?: number | string): void {
    const result: number | string = doPart(input);
    console.log(`--> ${result} <--`);
    if (expected && result !== expected) {
        throw -1;
    }
}

void (() => {
    go(TEST1, 198);
    go(INPUT);
})();
