import * as fs from 'fs';
import * as path from 'path';
import * as _ from 'lodash';

export const input = fs.readFileSync('input.txt', 'utf8').toString().replace(/\r\n/g, '\n');

export const numbers = input.split('\n').map(s => Number(s));

export const findNumber = (numbers: number[], iteration: number = 25) => {
    for (let index = iteration; index < numbers.length; index++) {
        const currentNumber = numbers[index];
        const possibleNumbers = createPossibleNumber(_.slice(numbers, index - iteration, index));

        if (!possibleNumbers.includes(currentNumber)) {
            return currentNumber;
        }
    }
    return -1
}

// create an array of all possible number
export const createPossibleNumber = (previousNumbers: number[]): number[] => {
    let results: number[] = [];
    for (let i = 0; i < previousNumbers.length; i++) {
        let resultsForThisPreviousNumber: number[] = [];
        for (let j = 0; j < previousNumbers.length; j++) {
            if (i !== j) {
                resultsForThisPreviousNumber.push(previousNumbers[i] + previousNumbers[j])
            }
        }
        results = results.concat(resultsForThisPreviousNumber);
    }
    return results;
}


//console.log(findNumber(numbers));