import * as fs from 'fs';
import * as path from 'path';
import * as _ from 'lodash';

const lines = fs.readFileSync('input.txt', 'utf8').toString().replace(/\r\n/g, '\n').split('\n');

console.log(lines.length);

let valids = 0;

lines.forEach((line:string) => {

    let [rule, value] = _.split(line, ': ');
    let [positionAandB, char] = _.split(rule, ' ');
    let [positionA, positionB] = _.split(positionAandB, '-');

    let isPositionA = value.charAt(Number(positionA)-1) === char;
    let isPositionB = value.charAt(Number(positionB)-1) === char;

   // console.log(`positionA=${positionA} positionB=${positionB}  char=${char} value=${value} isPositionA=${isPositionA} isPositionB=${isPositionB}`);
    if((isPositionA || isPositionB) && !(isPositionA && isPositionB)){
        // console.log(`positionA=${positionA} positionB=${positionB}  char=${char} value=${value} isPositionA=${isPositionA} isPositionB=${isPositionB}`);
        valids++;
    }
});

console.log(`numbers valids = ${valids}`);