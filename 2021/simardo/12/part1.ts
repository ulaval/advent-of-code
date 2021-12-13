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

    const tree: Tree = {};
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
    });

    const allPaths: string[][] = [];
    const walk: (node: string, path: string[]) => void = (n, p) => {
        p.push(n);
        if (n === 'end') {
            allPaths.push([...path]);
        } else {
            const dest: string[] = tree[n];
            dest.filter(f => f.toUpperCase() === f || p.indexOf(f) < 0).forEach(d => walk(d, p));
        }
        p.pop();
    };

    const start: string[] = tree['start'];
    const path: string[] = ['start'];
    start.forEach(node => walk(node, path));

    return allPaths.length;
}

function go(input: string, expected?: number | string): void {
    const result: number | string = doPart(input);
    console.log(`--> ${result} <--`);
    console.assert(!expected || result === expected, 'got: %s, expected: %s', result, expected);
}

void (() => {
    go(TEST1, 10);
    go(TEST2, 19);
    go(TEST3, 226);
    go(INPUT);
})();
