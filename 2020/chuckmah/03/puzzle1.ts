import * as fs from 'fs';
import * as path from 'path';
import * as _ from 'lodash';

const lines = fs.readFileSync('input.txt', 'utf8').toString().replace(/\r\n/g, '\n').split('\n');

console.log(lines.length);

let trees = 0;
let posY = 1;
let posX = 0;

lines.forEach((line:string, index: number) => {
    if(index > 0){ //start line 2
        posX = (posX + 3) % (line.length);
        console.log(`pos = ${index+1} , ${posX} => value = ${line[(posX)]}`)
        if(line[(posX)] == '#'){
            trees++;
        }

    }

});

console.log(trees);
