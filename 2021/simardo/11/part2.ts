import { INPUT } from './input.ts';

const TEST1: string = `5483143223
2745854711
5264556173
6141336146
6357385478
4167524645
2176841721
6882881134
4846848554
5283751526`;

function doPart(input: string): string | number {
    const map: number[][] = input.split('\n').map(s => [...s].map(n => Number.parseInt(n)));

    const increaseEnergy: (x: number, y: number) => void = (x, y) => {
        if (y >= 0 && y < map.length && x >= 0 && x < map[0].length) {
            map[y][x]++;
        }
    };

    const flash: (x: number, y: number) => void = (x, y) => {
        map[y][x] = Number.NaN;
        increaseEnergy(x, y - 1);
        increaseEnergy(x + 1, y - 1);
        increaseEnergy(x + 1, y);
        increaseEnergy(x + 1, y + 1);
        increaseEnergy(x, y + 1);
        increaseEnergy(x - 1, y + 1);
        increaseEnergy(x - 1, y);
        increaseEnergy(x - 1, y - 1);
    };

    const reset: (x: number, y: number) => void = (x, y) => {
        if (Number.isNaN(map[y][x])) {
            map[y][x] = 0;
        }
    };

    let step: number = 0;
    let allFlashed: boolean = false;
    while (!allFlashed) {
        step++;
        for (let y: number = 0; y < map.length; y++) {
            for (let x: number = 0; x < map.length; x++) {
                increaseEnergy(x, y);
            }
        }
        
        let hasFlash: boolean = true;
        while (hasFlash) {
            hasFlash = false;
            for (let y: number = 0; y < map.length; y++) {
                for (let x: number = 0; x < map.length; x++) {
                    if (map[y][x] > 9) {
                        hasFlash = hasFlash || true;
                        flash(x, y);
                    }
                }
            }
        }

        for (let y: number = 0; y < map.length; y++) {
            for (let x: number = 0; x < map.length; x++) {
                reset(x, y);
            }
        }

        allFlashed = map.every((vy, y) => vy.every(vx => vx === 0));
    }

    return step;
}

function go(input: string, expected?: number | string): void {
    const result: number | string = doPart(input);
    console.log(`--> ${result} <--`);
    console.assert(!expected || result === expected, 'got: %s, expected: %s', result, expected);
}

void (() => {
    go(TEST1, 195);
    go(INPUT);
})();
