const { group, groupCollapsed } = require('console');
const { createCipher } = require('crypto');
const fs = require('fs');
const readline = require('readline');
const path = require('path');
const readInterface = readline.createInterface({
    input: fs.createReadStream(path.join(__dirname, 'input.txt')),
});

let og = [];

readInterface
    .on('line', (line) => {
        og.push({
            op: line.split(' ')[0],
            value: parseInt(line.split(' ')[1]),
            done: false,
        });
    })
    .on('close', () => {
        let acc = 0;
        let index = 0;
        let loop = false;
        let fixed = false;
        let lastNopToJmpIndex = -1;
        let lastJmpToNopIndex = -1;

        while (!fixed) {
            let instructions = [...og.map((o) => Object.assign({}, o))];
            acc = 0;
            index = 0;
            loop = false;
            instructions.forEach((i) => (i.done = false));

            const stillNopToJmp = instructions
                .map((i) => i.op)
                .some((i, index) => {
                    let still = false;
                    if (i === 'nop' && index > lastNopToJmpIndex) {
                        still = true;
                        lastNopToJmpIndex = index;
                    }
                    return still;
                });

            if (!stillNopToJmp) {
                instructions
                    .map((i) => i.op)
                    .some((i, index) => {
                        let still = false;
                        if (i === 'jmp' && index > lastJmpToNopIndex) {
                            lastJmpToNopIndex = index;
                            still = true;
                        }
                        return still;
                    });
                instructions[lastJmpToNopIndex].op = 'nop';
            } else {
                instructions[lastNopToJmpIndex].op = 'jmp';
            }

            while (!loop || !fixed) {
                if (index >= instructions.length) {
                    fixed = true;
                    console.log(acc);
                    break;
                }

                const instruction = instructions[index];
                if (instruction.done) {
                    break;
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
        }
    });
