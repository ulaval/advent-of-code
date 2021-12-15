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

type Element = {
    id: string;
    next: Element | undefined;
}

// on se fait plaisir avec une liste chaînée!
function doPart(input: string): string | number {
    const [template, lines] = input.split('\n\n').map(s => s);
    const insertions: Map<string, string> = new Map(lines.split('\n').map(s => {
        const [pair, ins] = s.split(' -> ');
        return [pair, ins];
    }));

    const counts: { [key: string]: number } = {};
    const count: (elem: string) => void = e => {
        if (counts[e] === undefined) {
            counts[e] = 0;
        }
        counts[e]++;
    }

    let chain: Element;
    let element: Element | undefined = undefined;
    [...template].forEach(el => {
        const current: Element = {
            id: el,
            next: undefined
        }
        if (element === undefined) {
            chain = current;
        } else {
            element.next = current;
        }
        element = current;
        count(el);
    });

    for (let step: number = 1; step <= 10; step++) {
        let current: Element = chain!;
        while (current.next !== undefined) {
            const pair: string = current.id + current.next.id;
            const insertion: string = insertions.get(pair)!;
            const oldNext: Element = current.next;
            current.next = {
                id: insertion,
                next: oldNext
            }
            current = oldNext;
            count(insertion);
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
    go(TEST1, 1588);
    go(INPUT);
})();
