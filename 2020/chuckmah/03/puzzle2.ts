import * as fs from 'fs';
import * as path from 'path';
import * as _ from 'lodash';

const lines = fs.readFileSync('input.txt', 'utf8').toString().replace(/\r\n/g, '\n').split('\n');

console.log(lines.length);

const traverseRules = 
 [ [1,1], [3,1], [5,1], [7,1], [1,2] ]
// const traverseRules = 
// [  [3,1]]

let result = 1;

traverseRules.forEach(rule => {
    let [moveX, moveY] = rule;
    let trees = 0;



    let posY = 1;
    let posX = 0;
    while (posY < (lines.length)) {
        posY = (posY + moveY);
        posX = (posX + moveX) % (lines[posY-1].length);
        //console.log(`pos = ${posY} , ${posX} line ${lines[posY-1]} => value = ${lines[posY-1][(posX)]}`)
        if(lines[posY-1][posX] == '#'){
            trees++;
        }

    }
    console.log(`moveX = ${moveX}, moveY = ${moveY} result => ${trees}`);

    result = trees * result;

});

console.log(result);


