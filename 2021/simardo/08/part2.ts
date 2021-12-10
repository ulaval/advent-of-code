import { INPUT } from './input.ts';

const TEST1: string = `be cfbegad cbdgef fgaecd cgeb fdcge agebfd fecdb fabcd edb | fdgacbe cefdb cefbgd gcbe
edbfga begcd cbg gc gcadebf fbgde acbgfd abcde gfcbed gfec | fcgedb cgb dgebacf gc
fgaebd cg bdaec gdafb agbcfd gdcbef bgcad gfac gcb cdgabef | cg cg fdcagb cbg
fbegcd cbd adcefb dageb afcb bc aefdc ecdab fgdeca fcdbega | efabcd cedba gadfec cb
aecbfdg fbg gf bafeg dbefa fcge gcbea fcaegb dgceab fcbdga | gecf egdcabf bgf bfgea
fgeab ca afcebg bdacfeg cfaedg gcfdb baec bfadeg bafgc acf | gebdcfa ecba ca fadegcb
dbcfg fgd bdegcaf fgec aegbdf ecdfab fbedc dacgb gdcebf gf | cefg dcbef fcge gbcadfe
bdfegc cbegaf gecbf dfcage bdacg ed bedf ced adcbefg gebcd | ed bcgafe cdgba cbgef
egadfb cdbfeg cegd fecab cgb gbdefca cg fgcdab egfdb bfceg | gbdfcae bgc cg cgb
gcafb gcf dcaebfg ecagb gf abcdeg gaef cafbge fdbac fegbdc | fgae cfgab fg bagce`;

function intersection<T>(setA: Set<T>, setB: Set<T>) {
    let _intersection = new Set<T>();
    for (let elem of setB) {
        if (setA.has(elem)) {
            _intersection.add(elem);
        }
    }
    return _intersection
}

function doPart(input: string): string | number {

    const lines: [string[], string[]][] = input.split('\n').map(s => {
        const [patterns, output] = s.split(' | ');
        return [patterns.split(' '), output.split(' ')];
    });

    const wellKwownLength: [number, number][] = [
        [1, 2], // number, length
        [7, 3],
        [4, 4],
        [8, 7]
    ];

    const notWellKnown: [number, number, [number, number, number][]][] = [
        [5, 2, [[3, 1, 2], [5, 4, 3]]], //length, default, [number, compareWith, expectedLength]
        [6, 0, [[9, 3, 5], [6, 5, 5]]]
    ];

    const result: number = lines.reduce((p, l) => {
        const [patterns, output] = l;

        const numbers: Set<string>[] = new Array<Set<string>>(10);

        wellKwownLength.forEach(wkl => {
            const [num, length] = wkl;
            const pattern: string = patterns.find(s => s.length === length)!;
            numbers[num] = new Set<string>([...pattern]);
        });

        notWellKnown.forEach(nwk => {
            const [length, deflt, guesses] = nwk;
            patterns.filter(s => s.length === length).forEach(p => {
                const numSet: Set<string> = new Set<string>([...p]);
                const guess = guesses.find(g => {
                    const [_, compareWith, expectedLength] = g;
                    return intersection(numSet, numbers[compareWith]).size === expectedLength;
                });
                if (guess !== undefined) {
                    const [num] = guess;
                    numbers[num] = numSet;
                } else {
                    numbers[deflt] = numSet;
                }
            });
        });

        const out: string = output.reduce((p, o) => {
            const outputSet: Set<string> = new Set<string>([...o]);
            let index: number;
            for (let i: number = 0; i < numbers.length; i++) {
                if (numbers[i].size === outputSet.size && intersection(numbers[i], outputSet).size === outputSet.size) {
                    index = i;
                    break;
                }
            }
            return p + index!.toString();
        }, '');

        return p + Number.parseInt(out);
    }, 0);

    return result;
}

function go(input: string, expected?: number | string): void {
    const result: number | string = doPart(input);
    console.log(`--> ${result} <--`);
    console.assert(!expected || result === expected, 'got: %s, expected: %s', result, expected);
}

void (() => {
    go(TEST1, 61229);
    go(INPUT);
})();
