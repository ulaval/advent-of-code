import { INPUT } from './input.ts';

const TEST1: string = `2199943210
3987894921
9856789892
8767896789
9899965678`;

function toString(x: number, y: number): string {
    return `${x},${y}`;
}

function doPart(input: string): string | number {
    const map: number[][] = input.split('\n').map(s => [...s].map(n => Number.parseInt(n)));

    const computed: Set<string> = new Set<string>();

    const getBoundariesVLURD: (x: number, y: number) => [number, number, number, number, number] = (x, y) => {
        const left: number = x === 0 ? 9 : map[y][x - 1];
        const up: number = y === 0 ? 9 : map[y - 1][x];
        const right: number = x === map[y].length - 1 ? 9 : map[y][x + 1];
        const down: number = y === map.length - 1 ? 9 : map[y + 1][x];

        return [map[y][x], left, up, right, down];
    }

    const computeBassin: (x: number, y: number) => number = (x, y) => {
        const id: string = toString(x, y);
        if (computed.has(id)) {
            return 0;
        }

        computed.add(id);

        const [v, left, up, right, down] = getBoundariesVLURD(x, y);

        let result: number = 1;
        if (v < left && left !== 9) {
            result += computeBassin(x - 1, y);
        }
        if (v < right && right !== 9) {
            result += computeBassin(x + 1, y);
        }
        if (v < up && up !== 9) {
            result += computeBassin(x, y - 1);
        }
        if (v < down && down !== 9) {
            result += computeBassin(x, y + 1);
        }
        return result;
    }

    const bassins: number[] = [];

    for (let y: number = 0; y < map.length; y++) {
        for (let x: number = 0; x < map[y].length; x++) {
            const [v, left, up, right, down] = getBoundariesVLURD(x, y);

            if (v < left && v < right && v < up && v < down) {
                bassins.push(computeBassin(x, y));
            }
        }
    }

    return bassins.sort((a, b) => a < b ? -1 : a > b ? 1 : 0).reverse().slice(0, 3).reduce((p, v) => p * v, 1);
}

function go(input: string, expected?: number | string): void {
    const result: number | string = doPart(input);
    console.log(`--> ${result} <--`);
    console.assert(!expected || result === expected, 'got: %s, expected: %s', result, expected);
}

void (() => {
    go(TEST1, 1134);
    go(INPUT);
})();
