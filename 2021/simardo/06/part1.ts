import { INPUT } from './input.ts';

const TEST1: string = `3,4,3,1,2`;

function doPart(input: string): string | number {
    let nums: number[] = input.split(',').map(s => Number.parseInt(s));

    const days: number = 80;
    for (let i: number = 1; i <= days; i++) {
        const spawn: number[] = [];
        for (let j: number = 0; j < nums.length; j++) {
            if (nums[j] === 0) {
                spawn.push(8);
                nums[j] = 6;
            } else {
                nums[j] = nums[j] - 1;
            }
        }
        nums = nums.concat(spawn);
    }

    return nums.length;
}

function go(input: string, expected?: number | string): void {
    const result: number | string = doPart(input);
    console.log(`--> ${result} <--`);
    console.assert(!expected || result === expected, 'got: %s, expected: %s', result, expected);
}

void (() => {
    go(TEST1, 5934);
    go(INPUT);
})();
