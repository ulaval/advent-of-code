import { INPUT } from './input.ts';

const TEST1: string = `start-A
start-b
A-c
A-b
b-d
A-end
b-end`;

const TEST2: string = `dc-end
HN-start
start-kj
dc-start
dc-HN
LN-dc
HN-end
kj-sa
kj-HN
kj-dc`;

const TEST3: string = `fs-end
he-DX
fs-he
start-DX
pj-DX
end-zg
zg-sl
zg-pj
pj-he
RW-he
fs-DX
pj-RW
zg-RW
start-pj
he-WI
zg-he
pj-fs
start-RW`;

type Tree = { [key: string]: string[] };

function doPart(input: string): string | number {
    const lines: [string, string][] = input.split('\n').map(s => {
        const [from, to] = s.split('-');
        return [from, to];
    });

    const smallCaves: Set<string> = new Set<string>();
    lines.forEach(l => {
        const [from, to] = l;
        if (from.toLowerCase() === from) {
            smallCaves.add(from);
        }
        if (to.toLowerCase() === to) {
            smallCaves.add(to);
        }
    });
    smallCaves.delete('start');
    smallCaves.delete('end');

    const allPathsSet: Set<string> = new Set<string>();
    for (let smallCave of smallCaves) {
        const tree: Tree = {};
        const smallCaveID: string = smallCave + 'secondvisit';
        tree[smallCaveID] = [];

        lines.forEach(l => {
            const [from, to] = l;
            if (tree[from] === undefined) {
                tree[from] = [];
            }
            if (tree[from].indexOf(to) < 0) {
                tree[from].push(to);
            }

            if (tree[to] === undefined) {
                tree[to] = [];
            }
            if (tree[to].indexOf(from) < 0) {
                tree[to].push(from);
            }

            if (from === smallCave && tree[smallCaveID].indexOf(to) < 0) {
                tree[smallCaveID].push(to);
                if (tree[to].indexOf(smallCaveID) < 0) {
                    tree[to].push(smallCaveID);
                }
            }

            if (to === smallCave && tree[smallCaveID].indexOf(to) < 0) {
                tree[smallCaveID].push(from);
                if (tree[from].indexOf(smallCaveID) < 0) {
                    tree[from].push(smallCaveID);
                }
            }
        });

        const walk: (node: string, path: string[]) => void = (n, p) => {
            p.push(n);
            if (n === 'end') {
                allPathsSet.add([...path].map(s => s.replace('secondvisit', '')).join(','));
            } else {
                const dest: string[] = tree[n];
                dest.filter(f => f.toUpperCase() === f || p.indexOf(f) < 0).forEach(d => walk(d, p));
            }
            p.pop();
        };

        const start: string[] = tree['start'];
        const path: string[] = ['start'];
        start.forEach(node => walk(node, path));
    }

    return allPathsSet.size;
}

function go(input: string, expected?: number | string): void {
    const result: number | string = doPart(input);
    console.log(`--> ${result} <--`);
    console.assert(!expected || result === expected, 'got: %s, expected: %s', result, expected);
}

void (() => {
    go(TEST1, 36);
    go(TEST2, 103);
    go(TEST3, 3509);
    go(INPUT);
})();
