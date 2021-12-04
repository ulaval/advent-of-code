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
    const map: number[][] = input.split('\n').map(s => [...s].map(n => Number.parseInt(n)));

    const getMostLeastCommon: (map: number[][], index: number, most: boolean) => number = (list, index, most) => {
        const gamma: number[] = list.reduce((p, m) => {
            m.forEach((v, i) => {
                if (v === 1) {
                    p[i] = p[i] + 1;
                }
            });
            return p;
        }, new Array(map[0].length).fill(0));

        return most ? gamma[index] * 2 >= list.length ? 1 : 0 : gamma[index] * 2 >= list.length ? 0 : 1;
    }
    
    let bagO: number[][] = [...map];
    let bagC: number[][] = [...map];

    for (let i: number = 0; i < map[0].length && bagO.length > 1; i++) {
        const mostCommon: number = getMostLeastCommon(bagO, i, true);
        bagO = bagO.reduce((p, v) => {
            if (v[i] === mostCommon) {
                p.push(v);
            }
            return p;
        }, [] as number[][]);
    };

    for (let i: number = 0; i < map[0].length && bagC.length > 1; i++) {
        const leastCommon: number = getMostLeastCommon(bagC, i, false);
        bagC = bagC.reduce((p, v) => {
            if (v[i] === leastCommon) {
                p.push(v);
            }
            return p;
        }, [] as number[][]);
    };

    const o: number = Number.parseInt(bagO[0].join(''), 2);
    const c: number = Number.parseInt(bagC[0].join(''), 2);

    return o * c;
}

function go(input: string, expected?: number | string): void {
    const result: number | string = doPart(input);
    console.log(`--> ${result} <--`);
    if (expected && result !== expected) {
        throw -1;
    }
}

void (() => {
    go(TEST1, 230);
    go(INPUT);
})();
