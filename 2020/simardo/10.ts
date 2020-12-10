// https://github.com/simardo/adventofcode2020/tree/main/src/10

console.log('10 décembre');

// part 1
function doPart1(input: string): void {
    const adapters: number[] = input.split('\n').map(a => Number.parseInt(a)).sort((a, b) => a - b);
    adapters.push(adapters[adapters.length - 1] + 3);

    let r = adapters.reduce((t, a) => {
        let [diff1, diff3, prev]: [number, number, number] = t;
        if ((a - prev) === 1) {
            diff1++;
        } else if ((a - prev) === 3) {
            diff3++;
        }
        return [diff1, diff3, a] as [number, number, number];
    }, [0, 0, 0] as [number, number, number]);

    console.log(r[0] * r[1]);
}

doPart1(INPUT);

function doPart2(input: string): void {
    const adapters: number[] = input.split('\n').map(a => Number.parseInt(a)).sort((a, b) => a - b);
    adapters.push(adapters[adapters.length - 1] + 3);

    const r = adapters.reduce((ls, a) => {
        let [last, pot, acc] = ls;
        if ((a - last) === 3) {
            const c: number = comb(pot - 1);
            acc = c === 0 ? acc : acc * c;
            pot = 0;
        } else {
            pot++;
        }
        return [a, pot, acc] as [number, number, number];
    }, [0, 0, 1] as [number, number, number]);

    console.log(r[2]);
}

function comb(o: number): number {
    const fact = (n: number) => {
        let r: number = 1;
        for (let nn: number = n; nn > 0; nn--) {
            r *= nn;
        }
        return r;
    }

    let poss: number = o < 3 ? 1 : 0;
    for (let d: number = o; d > 0; d--) {
        poss += fact(o) / ((fact(d)) * fact(o - d));
    }

    return poss;
}

doPart2(INPUT);
