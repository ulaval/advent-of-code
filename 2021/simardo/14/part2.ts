import { INPUT } from './input.ts';

const TEST1: string = `NNCB

CH -> B
HH -> N
CB -> H
NH -> C
HB -> C
HC -> B
HN -> C
NN -> C
BH -> H
NC -> B
NB -> B
BN -> B
BB -> N
BC -> B
CC -> N
CN -> C`;

function doPart(input: string): string | number {
    const [template, lines] = input.split('\n\n').map(s => s);
    const insertions: Map<string, [string, number[]]> = new Map(lines.split('\n').map(s => {
        const [pair, ins] = s.split(' -> ');
        return [pair, [ins, new Array<number>(41).fill(0)]];
    }));

    const counts: { [key: string]: number } = {};
    const count: (elem: string, value: number) => void = (e, v) => {
        if (counts[e] === undefined) {
            counts[e] = 0;
        }
        counts[e] += v;
    }

    [...template].forEach((elem, i, a) => {
        count(elem, 1);
        if (i < a.length - 1) {
            const combination: string = elem + a[i + 1];
            const [_, tot] = insertions.get(combination)!;
            tot[0]++;
        }
    });

    for (let step: number = 1; step <= 40; step++) {
        for (const [pattern, [insertion, tot]] of insertions.entries()) {
            if (tot[step - 1] > 0) {
                const combA: string = pattern[0] + insertion;
                const [, totA] = insertions.get(combA)!;
                totA[step] += tot[step - 1];
                const combB: string = insertion + pattern[1];
                const [, totB] = insertions.get(combB)!;
                totB[step] += tot[step - 1];

                count(insertion, tot[step - 1]);
            }
        }
    }

    let min: number = Number.MAX_VALUE;
    let max: number = Number.MIN_VALUE;

    Object.values(counts).forEach(v => {
        min = Math.min(min, v);
        max = Math.max(max, v);
    });

    return max - min;
}

function go(input: string, expected?: number | string): void {
    const result: number | string = doPart(input);
    console.log(`--> ${result} <--`);
    console.assert(!expected || result === expected, 'got: %s, expected: %s', result, expected);
}

void (() => {
    go(TEST1, 2188189693529);
    go(INPUT);
})();
