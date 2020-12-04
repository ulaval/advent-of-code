import * as fs from 'fs';
import * as path from 'path';
import * as _ from 'lodash';

const lines = fs.readFileSync('input.txt', 'utf8').toString().replace(/\r\n/g, '\n').split('\n');

console.log(lines.length);
console.log(lines[0].length);

let trees = 0;
let posY = 1;
let posX = 1;

let ruleIndex = 0;
const traverseRules = 
[ [1,1], [3,1], [5,1], [7,1], [1,2] ]


while (posY < (lines.length)) {
    

    let [moveX, moveY] = traverseRules[ruleIndex];


    posY = (posY + moveY);
    posX = ((posX-1) + moveX) % lines[posY-1].length;
console.log(`posY = ${posY} ,posX = ${posX}, line = ${lines[posY-1]}, moveX =${moveX} , moveY =${moveY} => value = ${lines[posY-1][posX]}`)
    if(lines[posY-1][posX] == '#'){
        trees++;
    }

    ruleIndex = (ruleIndex + 1) % traverseRules.length ;
}

console.log(trees);


