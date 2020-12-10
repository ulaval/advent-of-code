import * as fs from 'fs';
import * as path from 'path';
import * as _ from 'lodash';
import { numbers } from './puzzle1';



export const findContiguousNumbersThatEquals = (numbers: number[], sum: number) => {
    for (let i = 0; i < numbers.length; i++) {
        const currentNumber = numbers[i];
        const otherNumbers = numbers.slice(i + 1);
        for (let j = i + 1; j < numbers.length; j++) {
            const arrayToAdd = numbers.slice(i, j);
            if (addArray(arrayToAdd) < sum) {
                continue;
            } else if (addArray(arrayToAdd) > sum) {
                break;
            } else {
                return arrayToAdd;
            }
        }
    }
    return [];
}

export const addArray = (array: number[]) => {
    return array.reduce((a, b) => a + b, 0)
}


let results = findContiguousNumbersThatEquals(numbers, 70639851);

console.log(_.max(results)! + _.min(results)!);