import { INPUT } from './input.ts';

const TEST1: string = `0,9 -> 5,9
8,0 -> 0,8
9,4 -> 3,4
2,2 -> 2,1
7,0 -> 7,4
6,4 -> 2,0
0,9 -> 2,9
3,4 -> 1,4
0,0 -> 8,8
5,5 -> 8,2`;

function doPart(input: string): string | number {
    const lines: number[][][] = input.split('\n').map(s => s.split(' -> ')).map(c => {
        const [left, right] = c;
        return [left.split(',').map(n => Number.parseInt(n)), right.split(',').map(n => Number.parseInt(n))];
    });

    const map: number[][] = [];

    lines.forEach(l => {
        const [left, right] = l;
        let [x, y] = left;
        const [x2, y2] = right;

        let done: boolean = false;
        let last: boolean = false;
        while (!done) {
            let my: number[] = map[y];
            if (my === undefined) {
                my = [];
                map[y] = my;
            }
            let mxy: number = my[x];
            if (mxy === undefined) {
                mxy = 0;
            }
            map[y][x] = mxy + 1;

            x = x < x2 ? x + 1 : x > x2 ? x - 1 : x;
            y = y < y2 ? y + 1 : y > y2 ? y - 1 : y;

            done = last;
            last = x === x2 && y === y2;
        }
    });

    return map.reduce((p, y) => p + y.reduce((pp, x) => pp + ((x && x >= 2) ? 1 : 0), 0), 0);
}

function go(input: string, expected?: number | string): void {
    const result: number | string = doPart(input);
    console.log(`--> ${result} <--`);
    console.assert(!expected || result === expected, 'got: %s, expected: %s', result, expected);
}

void (() => {
    go(TEST1, 12);
    go(INPUT);
})();
