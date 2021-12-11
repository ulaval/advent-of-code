import { INPUT } from './input.ts';

const TEST1: string = `[({(<(())[]>[[{[]{<()<>>
[(()[<>])]({[<{<<[]>>(
{([(<{}[<>[]}>{[]{[(<()>
(((({<>}<{<{<>}{[]{[]{}
[[<[([]))<([[{}[[()]]]
[{[{({}]{}}([{[{{{}}([]
{<[[]]>}<{[{[{[]{()[[[]
[<(<(<(<{}))><([]([]()
<{([([[(<>()){}]>(<<{{
<{([{{}}[<[[[<>{}]]]>[]]`;

function doPart(input: string): string | number {
    const lines: string[] = input.split('\n').map(s => s);

    const openBrackets: Set<string> = new Set<string>(['[', '{', '<', '(']);

    const bracketMap: Map<string, string> = new Map([
        [']', '['],
        ['}', '{'],
        ['>', '<'],
        [')', '('],
    ]);

    const pointsMap: Map<string, number> = new Map<string, number>([
        [')', 3],
        [']', 57],
        ['}', 1197],
        ['>', 25137],
    ]);

    return lines.reduce((p,l) => {
        let points: number = 0;
        const stack: string[] = [];
        for (let i: number = 0; i < l.length; i++) {
            const v: string = l[i];
            if (openBrackets.has(v)) {
                stack.push(v);
            } else {
                const onStack: string | undefined = stack.pop();
                if (bracketMap.get(v) !== onStack) {
                    points += pointsMap.get(v)!;
                    break;
                }
            }
        }
        return p + points;
    }, 0);
}

function go(input: string, expected?: number | string): void {
    const result: number | string = doPart(input);
    console.log(`--> ${result} <--`);
    console.assert(!expected || result === expected, 'got: %s, expected: %s', result, expected);
}

void (() => {
    go(TEST1, 26397);
    go(INPUT);
})();
