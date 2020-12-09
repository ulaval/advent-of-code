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

        let invalidIndex;
        numbers.every((n, i, a) => {
            if (i < preambleLength) {
                return true;
            }

            const preamble = [...a].slice(i - preambleLength, i);

            if (
                !preamble.find((p, i, a) => {
                    const copy = [...a];
                    copy.splice(i, 1);
                    return copy.some((e) => e + p === n);
                })
            ) {
                invalidIndex = i;
                return false;
            } else {
                return true;
            }
        });

        const hay = numbers.slice(0, invalidIndex);
        const needle = numbers[invalidIndex];

        hay.find((h, i, a) => {
            let pos = i;
            let sum = [];
            let found = false;

            while (
                pos < invalidIndex &&
                sum.reduce((a, c) => ((a += c), a), 0) < needle &&
                !found
            ) {
                sum.push(a[pos]);
                found = sum.reduce((a, c) => ((a += c), a), 0) === needle;
                pos++;
            }

            if (found) {
                sum.sort((a, b) => (a > b ? 1 : a < b ? -1 : 1));
                console.log(sum[0] + sum[sum.length - 1]);
            }
        });
    });
