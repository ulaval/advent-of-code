import { runProgram } from "./puzzle1";

const input = [
    'nop +0',
    'acc +1',
    'jmp +4',
    'acc +3',
    'jmp -3',
    'acc -99',
    'acc +1',
    'jmp -4',
    'acc +6',
]

test('given the input , correct output!', () => {
    expect(runProgram(input)).toBe(5);
})
