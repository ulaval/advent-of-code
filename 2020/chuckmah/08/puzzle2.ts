import { instructions, parseInstruction } from './puzzle1';
import * as _ from 'lodash';


export const detectInfineLoop = (instructions: string[], modifyJmpAnddNopNumber: number): boolean => {

    let acc = 0;
    let currAddrIndex = 0;
    let visitedAddrIndexes: number[] = [];
    let jmpOrNopCount = 0;


    while (currAddrIndex < instructions.length) {

        if (visitedAddrIndexes.find(value => value == currAddrIndex) != undefined) {
            console.log('Infinite loop');
            return true;
        }


        const currentInstruction = parseInstruction(instructions[currAddrIndex]);

        if (currentInstruction.instruction === 'nop' || currentInstruction.instruction === 'jmp') {
            jmpOrNopCount++;


            if (jmpOrNopCount === modifyJmpAnddNopNumber) {
                if (currentInstruction.instruction === 'jmp') {
                    currentInstruction.instruction = 'nop';
                } else if (currentInstruction.instruction === 'nop') {
                    currentInstruction.instruction = 'jmp';
                } else {
                    throw new Error('not supposed!' + currentInstruction.instruction);
                }
            }


        }

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
    console.log('accumulator = ' + acc);
    return false;
}


// export const modifyJmpAndNop = (instructions: string[]): void => {

//     let lastJmpOrNopModifiedIndex = 0;

// }


export const modifiyNopAndJmpSequentially = (instructions: string[]) => {
    let modifyJmpAnddNopNumber = 1;
    while(detectInfineLoop(instructions, modifyJmpAnddNopNumber)){
        modifyJmpAnddNopNumber++;
    }
    
}

console.log(modifiyNopAndJmpSequentially(instructions));