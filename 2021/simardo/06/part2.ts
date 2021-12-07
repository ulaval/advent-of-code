import { INPUT } from './input.ts';

const TEST1: string = `3,4,3,1,2`;

function doPart(input: string): string | number {
    let nums: number[] = input.split(',').map(s => Number.parseInt(s));

    const population: [number, number][] = new Array(9);
    for (let i: number = 0; i < population.length; i++) {
        population[i] = [0, 0];
    }

    nums.forEach(n => {
        const [remain, spawn] = population[n];
        population[n] = [remain + 1, spawn];
    });

    for (let d: number = 1; d <= 256; d++) {
        for (let p: number = 0; p < population.length; p++) {
            const [remain, spawn] = population[p];

            if (p === 0) {
                const [remain2, spawn2] = population[8];
                population[8] = [remain2, spawn2 + remain];
            }
            const nextPopulation: number = p === 0 ? 6 : p - 1;
            const [remain2, spawn2] = population[nextPopulation];
            population[nextPopulation] = [remain2, spawn2 + remain];

            population[p] = [0, spawn];
        }
        for (let p: number = 0; p < population.length; p++) {
            const [, spawn] = population[p];
            population[p] = [spawn, 0];
        }
    }

    return population.reduce((p, v) => p + v[0], 0);
}

function go(input: string, expected?: number | string): void {
    const result: number | string = doPart(input);
    console.log(`--> ${result} <--`);
    console.assert(!expected || result === expected, 'got: %s, expected: %s', result, expected);
}

void (() => {
    go(TEST1, 26984457539);
    go(INPUT);
})();
