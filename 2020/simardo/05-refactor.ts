// https://github.com/simardo/adventofcode2020/tree/main/src/05

console.log('5 décembre');

type BoundFn = (t: [number, number]) => [number, number];

const lobound: BoundFn = t => {
    let [lo, hi] = t;
    return [lo, lo + Math.floor((hi - lo) / 2)]
}

const hibound: BoundFn = t => {
    let [lo, hi] = t;
    return [lo + Math.ceil((hi - lo) / 2), hi];
}

// part 1
function doPart1(input: string): void {
    const passes: string[] = input.split('\n');

    const max: number = passes.reduce((aa, pp) => {
        const [, row] = [...pp].slice(0, 7).reduce((a, p) => p === 'F' ? lobound(a) : hibound(a), [0, 127]);
        const [, seat] = [...pp].slice(7).reduce((a, p) => p === 'L' ? lobound(a) : hibound(a), [0, 7]);

        return Math.max(aa, row * 8 + seat);
    }, 0);

    console.log(max);
}

doPart1(INPUT);

// part 2
function doPart2(input: string): void {
    const allSeats: number[] = [];
    const passes: string[] = input.split('\n');
    passes.forEach(pp => {
        const [, row] = [...pp].slice(0, 7).reduce((a, p) => p === 'F' ? lobound(a) : hibound(a), [0, 127]);
        const [, seat] = [...pp].slice(7).reduce((a, p) => p === 'L' ? lobound(a) : hibound(a), [0, 7]);

        allSeats.push(row * 8 + seat);
    });

    allSeats.sort((a, b) => a - b);
    const seatID: number = allSeats.find((s, i) => i > 0 && s === allSeats[i - 1] + 2)! - 1;

    console.log(seatID);
}

doPart2(INPUT);