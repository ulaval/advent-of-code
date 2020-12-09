const { group, groupCollapsed } = require('console');
const { createCipher } = require('crypto');
const fs = require('fs');
const readline = require('readline');

const readInterface = readline.createInterface({
    input: fs.createReadStream('./input.txt'),
});

let instructions = [];

readInterface
    .on('line', (line) => {
        instructions.push({
            op: line.split(' ')[0],
            value: parseInt(line.split(' ')[1]),
            done: false,
        });
    })
    .on('close', () => {
        let acc = 0;
        let index = 0;
        let loop = false;

        while (!loop) {
            const instruction = instructions[index];
            if (instruction.done) {
                console.log(acc);
                loop = true;
            }

            instruction.done = true;

            switch (instruction.op) {
                case 'acc': {
                    acc += instruction.value;
                    index++;
                    continue;
                }
                case 'jmp': {
                    index += instruction.value;
                    continue;
                }
                case 'nop': {
                    index++;
                    continue;
                }
            }
        }
    });
