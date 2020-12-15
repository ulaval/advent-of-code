// https://github.com/simardo/adventofcode2020/tree/main/src/14

console.log('14 décembre');

const instRx: RegExp = /mem\[(\d+)\]\s\=\s(\d+)/;

// part 1
function doPart1(input: string): void {
    const prog: string[] = input.split('\n');

    let maskRoot: string[];
    let overrides: Set<number>;

    const mem: { [key: string]: any } = {};

    prog.forEach(p => {
        if (p.startsWith('mask')) {
            maskRoot = [...p.substr('mask = '.length)];
            overrides = new Set<number>();
            for (let b: number = maskRoot.length - 1; b >= 0; b--) {
                if (maskRoot[b] !== 'X') {
                    overrides.add(b);
                }
            }
        } else {
            const mask: string[] = [...maskRoot];
            const [, addrS, valueS] = p.match(instRx)!;

            let value: number = Number.parseInt(valueS);
            for (let b: number = mask.length - 1; b >= 0; b--) {
                if (!overrides.has(b)) {
                    mask[b] = (value & 1) === 1 ? '1' : '0';
                }
                value = value >> 1;
            }

            let memValue: BigInt = 0n;
            for (let b: number = 0; b < mask.length; b++) {
                memValue = BigInt(memValue) << BigInt(1);
                memValue = BigInt(memValue) | BigInt(Number.parseInt(mask[b]));
            }

            mem[addrS] = memValue;
        }
    });

    const r = Object.values(mem).reduce((s, v) => BigInt(s) + BigInt(v), 0n);
    console.log(r);
}

doPart1(TEST_1);
doPart1(INPUT);

// part 2
function doPart2(input: string): void {
    const prog: string[] = input.split('\n');

    let maskRoot: string[];

    const mem: { [key: string]: any } = {};
    let permutations: [string, number][];

    prog.forEach(p => {
        if (p.startsWith('mask')) {
            maskRoot = [...p.substr('mask = '.length)];
            permutations = [];
            for (let b: number = maskRoot.length - 1; b >= 0; b--) {
                if (maskRoot[b] === 'X') {
                    permutations.push(['0', b]);
                }
            }
        } else {
            const mask: string[] = [...maskRoot];
            const [, addrS, valueS] = p.match(instRx)!;

            let addr: number = Number.parseInt(addrS);
            const value: number = Number.parseInt(valueS);

            for (let b: number = mask.length - 1; b >= 0; b--) {
                if (mask[b] === '0' && (addr & Math.pow(2, mask.length - b - 1)) > 0) {
                    mask[b] = '1';
                }
            }

            permute(permutations, 0, m => {
                m.forEach(mm => {
                    const [bit, pos] = mm;
                    mask[pos] = bit;
                });
                mem[mask.join('')] = value;
            });
        }
    });

    const r = Object.values(mem).reduce((s, v) => BigInt(s) + BigInt(v), 0n);
    console.log(r);
}

type PermutFn = (per: [string, number][]) => void;

function permute(per: [string, number][], i: number, fn: PermutFn) {
    const poss = ['0', '1'];
    poss.forEach(p => {
        const res = [...per];
        res[i][0] = p;
        if (i < per.length - 1) {
            permute(res, i + 1, fn)
        } else {
            fn(res);
        }
    });
}

doPart2(TEST_2);
doPart2(INPUT);
