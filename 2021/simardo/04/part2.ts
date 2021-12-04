import { INPUT } from './input.ts';

const TEST1: string = `7,4,9,5,11,17,23,2,0,14,21,24,10,16,13,6,15,25,12,22,18,20,8,19,3,26,1

22 13 17 11  0
 8  2 23  4 24
21  9 14 16  7
 6 10  3 18  5
 1 12 20 15 19

 3 15  0  2 22
 9 18 13 17  5
19  8  7 25 23
20 11 10 24  4
14 21 16 12  6

14 21 17 24  4
10 16 15  9 19
18  8 23 26 20
22 11 13  6  5
 2  0 12  3  7`;

function doPart(input: string): string | number {
    const lines: string[] = input.split('\n\n').map(s => s);

    const draft: number[] = lines[0].split(',').map(s => Number.parseInt(s));
    const cards: (number | null)[][][] = lines.slice(1).map(c => c.split('\n').map(n => n.split(' ').filter(s => s != '').map(nn => Number.parseInt(nn))));

    const winningCards: Set<number> = new Set<number>();

    let result: number = 0;

    draft.some(d => {
        return cards.some((c, ci) => {
            c.forEach((l, y) => {
                l.forEach((n, x) => {
                    if (n === d) {
                        c[y][x] = null
                    }
                });
            });

            const hasRow: boolean = c.some(l => l.every(n => n === null));
            const hasCol: boolean = c[0].map((_, col) => c.map(row => row[col])).some(l => l.every(n => n === null));

            if (hasRow || hasCol) {
                winningCards.add(ci);
            }

            if (winningCards.size === cards.length) {
                result = c.reduce((p, l) => p + l.filter(n => n !== null).reduce((pp, n) => pp! + n!, 0)! * d, 0);
                return true;
            }
            return false;
        });
    });

    return result;
}

function go(input: string, expected?: number | string): void {
    const result: number | string = doPart(input);
    console.log(`--> ${result} <--`);
    if (expected && result !== expected) {
        throw -1;
    }
}

void (() => {
    go(TEST1, 1924);
    go(INPUT);
})();
