import * as fs from 'fs';
import * as path from 'path';
import * as _ from 'lodash';

const lines = fs.readFileSync('input.txt', 'utf8').toString().replace(/\r\n/g, '\n').split('\n');

console.log(lines.length);

let valids = 0;

lines.forEach((line:string) => {

    let [rule, value] = _.split(line, ': ');
    let [minMax, char] = _.split(rule, ' ');
    let [min, max] = _.split(minMax, '-');
    let count = ( _.split(value, char).length -1 );

     // console.log(`min=${min} max=${max} char=${char} value=${value} count=${count}`);

    if((Number(count) >= Number(min) &&  Number(count) <= Number(max))){
        valids++;
    }
});

console.log(`numbers valids = ${valids}`);