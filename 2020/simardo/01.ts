// https://github.com/simardo/adventofcode2020/tree/main/src/01

console.log('1er décembre');

// part 1
function doPart1(input: string): void {
    const nums: number[] = input.split('\n').map(s => Number.parseInt(s));

    const result: number = nums.reduce((p, n) => {
        const match: number | undefined = nums.find(nn => nn + n === 2020);
        return match ? n * match : p;
    }, 0);

    console.log(result);
}

// doPart1(INPUT);

// part 2
function doPart2(input: string): void {
    const map: Set<number> = new Set();
    const nums: number[] = input.split('\n').map(s => {
        const n: number = Number.parseInt(s)
        map.add(n);
        return n;
    });

    const result: number = nums.reduce((p, n) => {
        const match: number | undefined = nums.find(nn => map.has(2020 - n - nn) ? nn : undefined);
        return match ? n * match * (2020 - n - match) : p;
    }, 0);

    console.log(result);
}

// doPart2(INPUT);
