const { group, groupCollapsed } = require('console');
const { createCipher } = require('crypto');
const fs = require('fs');
const readline = require('readline');
const path = require('path');

const readInterface = readline.createInterface({
    input: fs.createReadStream(path.join(__dirname, 'input.txt')),
});

let numbers = [];

readInterface
    .on('line', (line) => {
        numbers.push(parseInt(line));
    })
    .on('close', () => {
        const preambleLength = 25;

        console.log(
            numbers.find((n, i, a) => {
                if (i < preambleLength) {
                    return;
                }

                const preamble = [...a].slice(i - preambleLength, i);
                console.log(preamble);

                if (
                    !preamble.find((p, i, a) => {
                        const copy = [...a];
                        copy.splice(i, 1);
                        return copy.some((e) => e + p === n);
                    })
                ) {
                    return true;
                }
            })
        );
    });
