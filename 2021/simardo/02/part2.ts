import { INPUT } from './input.ts';

const TEST1: string = `forward 5
down 5
forward 8
up 3
down 8
forward 2`;

type Move = [string, number];

function doPart2(input: string): void {
    const moves: Move[] = input.split('\n').map(s => {
        const [move, units] = s.split(' ');
        return [move, Number.parseInt(units)];
    });

    let horizontal: number = 0;
    let depth: number = 0;
    let aim: number = 0;
    
    moves.forEach(m => {
        const [move, unit] = m;
        if (move === 'forward') {
            horizontal += unit;
            depth += (aim * unit);
        } else if (move === 'down') {
            aim += unit;
        } else if (move === 'up') {
            aim -= unit;
        }
    });

    console.log(horizontal * depth);
}

doPart2(TEST1);
doPart2(INPUT);
