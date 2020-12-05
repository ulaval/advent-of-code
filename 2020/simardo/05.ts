// https://github.com/simardo/adventofcode2020/tree/main/src/05

console.log('5 décembre');

// part 1
function doPart1(input: string): void {
    const passes: string[] = input.split('\n');
    const max: number = passes.reduce((aa, pp) => {
        const pass: string[] = [...pp];

        const [, row] = pass.slice(0, 7).reduce((a, p) => {
            if (p === 'F') {
                return [a[0], a[0] + Math.floor((a[1] - a[0]) / 2)];
            } else {
                return [a[0] + Math.ceil((a[1] - a[0]) / 2), a[1]];
            }
        }, [0, 127]);

        const [, seat] = pass.slice(7).reduce((a, p) => {
            if (p === 'L') {
                return [a[0], a[0] + Math.floor((a[1] - a[0]) / 2)];
            } else {
                return [a[0] + Math.ceil((a[1] - a[0]) / 2), a[1]];
            }
        }, [0, 7]);

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
        const pass: string[] = [...pp];

        const [, row] = pass.slice(0, 7).reduce((a, p) => {
            if (p === 'F') {
                return [a[0], a[0] + Math.floor((a[1] - a[0]) / 2)];
            } else {
                return [a[0] + Math.ceil((a[1] - a[0]) / 2), a[1]];
            }
        }, [0, 127]);

        const [, seat] = pass.slice(7).reduce((a, p) => {
            if (p === 'L') {
                return [a[0], a[0] + Math.floor((a[1] - a[0]) / 2)];
            } else {
                return [a[0] + Math.ceil((a[1] - a[0]) / 2), a[1]];
            }
        }, [0, 7]);

        const seatID: number = row * 8 + seat;
        allSeats.push(seatID);
    });

    allSeats.sort((a, b) => a - b);
    const seatID: number = allSeats.reduce((r, s, i) => (i > 0 && s === allSeats[i - 1] + 2) ? s - 1 : r, -1);

    console.log(seatID);
}

doPart2(INPUT);
