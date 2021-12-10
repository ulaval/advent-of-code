import { INPUT } from './input.ts';

const TEST1: string = `2199943210
3987894921
9856789892
8767896789
9899965678`;

function doPart(input: string): string | number {
    const map: number[][] = input.split('\n').map(s => [...s].map(n => Number.parseInt(n)));

    return map.reduce((py, vy, y) => py + vy.reduce((px, vx, x) => {
        const left: number = x === 0 ? Number.MAX_VALUE : map[y][x - 1];
        const up: number = y === 0 ? Number.MAX_VALUE : map[y - 1][x];
        const right: number = x === map[y].length - 1 ? Number.MAX_VALUE : map[y][x + 1];
        const down: number = y === map.length - 1 ? Number.MAX_VALUE : map[y + 1][x];

        if (vx < left && vx < up && vx < right && vx < down) {
            return px + vx + 1;
        } else {
            return px;
        }
    }, 0), 0);
}

function go(input: string, expected?: number | string): void {
    const result: number | string = doPart(input);
    console.log(`--> ${result} <--`);
    console.assert(!expected || result === expected, 'got: %s, expected: %s', result, expected);
}

void (() => {
    go(TEST1, 15);
    go(INPUT);
})();
