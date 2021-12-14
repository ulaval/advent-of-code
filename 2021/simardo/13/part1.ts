import { INPUT } from './input.ts';

const TEST1: string = `6,10
0,14
9,10
0,3
10,4
4,11
6,0
6,12
4,1
0,13
10,12
3,4
3,0
8,4
1,10
2,14
8,10
9,0

fold along y=7
fold along x=5`;

function doPart(input: string): string | number {
    const [coords, fold] = input.split('\n\n').map(s => s);

    const map: boolean[][] = [];
    coords.split('\n').forEach(s => {
        const [x, y] = s.split(',').map(n => Number.parseInt(n));
        for (let i = 0; i <= y; i++) {
            if (map[i] === undefined) {
                map[i] = [];
            }
        }
        for (let i = 0; i <= x; i++) {
            if (map[y][i] === undefined) {
                map[y][i] = false;
            }
        }
        map[y][x] = true;
    });

    const instr: [string, number][] = fold.split('\n').map(s => {
        const [axis, value]: string[] = s.substring('fold along '.length).split('=');
        return [axis, Number.parseInt(value)];
    });

    const [axis, value] = instr[0];
    if (axis === 'y') {
        for (let y = value + 1; y < map.length; y++) {
            map[y].forEach((v, x) => {
                const foldY: number = y - ((y - value) * 2);
                if (foldY >= 0) {
                    map[foldY][x] = map[foldY][x] || v;
                }
                map[y][x] = false;
            });
        }
    } else {
        map.forEach(vy => {
            for (let x = value + 1; x < vy.length; x++) {
                const foldX: number = x - ((x - value) * 2);
                if (foldX >= 0) {
                    vy[foldX] = vy[foldX] || vy[x];
                }
                vy[x] = false;
            }
        });
    }

    return map.reduce((p, vy) => p + vy.reduce((p, vx) => vx ? p + 1 : p, 0), 0);
}

function go(input: string, expected?: number | string): void {
    const result: number | string = doPart(input);
    console.log(`--> ${result} <--`);
    console.assert(!expected || result === expected, 'got: %s, expected: %s', result, expected);
}

void (() => {
    go(TEST1, 17);
    go(INPUT);
})();
