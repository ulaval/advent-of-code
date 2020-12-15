// https://github.com/simardo/adventofcode2020/tree/main/src/15

console.log('15 décembre');

// part 1&2
function doPart12(numbers: number[], turns: number): void {
    const history: { [key: number]: number } = {};
    let turn: number = 0;
    let last: number;

    numbers.slice(0, numbers.length - 1).forEach((n, i) => {
        history[n] = i + 1;
    });

    last = numbers[numbers.length - 1];
    turn = numbers.length;

    let spoken: number;
    while (turn < turns) {
        turn++;

        let h: number | undefined = history[last];

        if (h === undefined) {
            spoken = 0;
        } else {
            spoken = (turn - 1) - h;
        }
        history[last] = turn - 1;

        last = spoken;
    }
    console.log(turn, spoken!);
}

doPart12([0, 3, 6], 2020);
doPart12([1, 3, 2], 2020);
doPart12([2, 1, 3], 2020);
doPart12([1, 2, 3], 2020);
doPart12([20, 0, 1, 11, 6, 3], 2020);
doPart12([20, 0, 1, 11, 6, 3], 30000000);
