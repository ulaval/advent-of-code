import * as fs from 'fs';
import * as path from 'path';
import * as _ from 'lodash';

export const input = fs.readFileSync('input.txt', 'utf8').toString().replace(/\r\n/g, '\n');

export const instructions = input.split('\n');


export const parseInstruction = (instruction: string): {
    instruction: 'nop' | 'acc' | 'jmp';
    value: number;
} => {
    return {
        instruction: instruction.split(' ')[0] as 'nop' | 'acc' | 'jmp',
        value: Number(instruction.split(' ')[1])
    };
}


export const runProgram = (instructions: string[]): number => {

    let acc = 0;
    let currAddrIndex = 0;
    let visitedAddrIndexes: number[] = [];


    while (visitedAddrIndexes.find(value => value == currAddrIndex) == undefined && currAddrIndex < instructions.length) {
        // console.log(`${currAddrIndex}  visitedAddrIndexes = ${visitedAddrIndexes} ${visitedAddrIndexes.find(value => value == currAddrIndex) == undefined}`);
        const currentInstruction = parseInstruction(instructions[currAddrIndex]);

        visitedAddrIndexes.push(currAddrIndex);

        switch (currentInstruction.instruction) {
            case 'nop':
                currAddrIndex++;
                break;
            case 'acc':
                acc += currentInstruction.value;
                currAddrIndex++;
                break;
            case 'jmp':
                currAddrIndex += currentInstruction.value;
                break;

            default:
                throw new Error('unknown instruction!');
                break;
        }


    }

    return acc;
}




//console.log(instructions[633]);
//console.log(runProgram(instructions));