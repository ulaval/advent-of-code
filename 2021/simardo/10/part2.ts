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

    const pointsMap: Map<string, number> = new Map([
        ['[', 2],
        ['{', 3],
        ['<', 4],
        ['(', 1],
    ]);

    let points: number[] = [];
    lines.forEach(l => {
        const stack: string[] = [];
        const corrupted: boolean = [...l].some(v => {
            if (openBrackets.has(v)) {
                stack.push(v);
            } else {
                const onStack: string | undefined = stack.pop();
                return bracketMap.get(v) !== onStack;
            }
        });
        if (!corrupted) {
            points.push(stack.reverse().reduce((p,v) => p * 5 + pointsMap.get(v)!, 0));
        }
    });

    points.sort((a,b) => a < b ? -1 : a > b ? 1 : 0);

    return points[Math.floor(points.length / 2)];
}

function go(input: string, expected?: number | string): void {
    const result: number | string = doPart(input);
    console.log(`--> ${result} <--`);
    console.assert(!expected || result === expected, 'got: %s, expected: %s', result, expected);
}

void (() => {
    go(TEST1, 288957);
    go(INPUT);
})();
