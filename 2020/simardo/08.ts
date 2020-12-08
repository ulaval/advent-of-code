// https://github.com/simardo/adventofcode2020/tree/main/src/08

console.log('8 décembre');

const instRx: RegExp = /(nop|acc|jmp)\s([\+|\-]?\d+)/;

// part 1
function doPart1(input: string): void {
    const loop: string[] = input.split('\n');

    const prog = loop.map(l => l.match(instRx)!);

    let acc: number = 0;

    let i: number = 0;
    const runs: Set<number> = new Set();
    while (!runs.has(i)) {
        const [,ins, q] = prog[i];
        runs.add(i);
        if (ins === 'acc') {
            acc += Number.parseInt(q);
            i += 1;
        } else if (ins === 'jmp') {
            i += Number.parseInt(q);
        } else if (ins === 'nop') {
            i += 1;
        }
    };

    console.log(acc);
}

doPart1(INPUT);

function doPart2(input: string): void {
    const loop: string[] = input.split('\n');

    for(let im: number = 0; im < loop.length; im++) {
        const progMain = loop.map(l => {
            const [, ins, q] = l.match(instRx)!;
            return [ins, q]
        });

        let [insm] = progMain[im];
        if (insm === 'nop' || insm === 'jmp') {
            const prog = [...progMain];
            prog[im][0] = prog[im][0] === 'nop' ? 'jmp' : 'nop';

            let acc: number = 0;

            let i: number = 0;
            const runs: Set<number> = new Set();

            while (!runs.has(i) && i < prog.length) {
                const [ins, q] = prog[i];
                runs.add(i);
                if (ins === 'acc') {
                    acc += Number.parseInt(q);
                    i += 1;
                } else if (ins === 'jmp') {
                    i += Number.parseInt(q);
                } else if (ins === 'nop') {
                    i += 1;
                }
            };

            if (i === prog.length) {
                console.log(acc);
            }
        }
    }

    console.log();
}

doPart2(INPUT);
