import * as fs from 'fs';
import * as path from 'path';


const numbers = fs.readFileSync('input.txt', 'utf8').toString().replace(/\r\n/g, '\n').split('\n');

numbers.forEach((number1, index1) => {


    numbers.forEach((number2, index2) => {
        numbers.forEach((number3, index3) => {
            if (index1 !== index2 && index1 !== index3 && index2 !== index3) {
                if ((Number(number1)) + (Number(number2)) + (Number(number3)) === 2020) {
                    console.log(`number 1 = ${number1}  number 2 = ${number2}  number 3 = ${number3}  => multiplcation ${Number(number1) * Number(number2) * Number(number3)}`);
                }
            }
        })
    })
});