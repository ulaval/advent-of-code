const { group, groupCollapsed } = require('console');
const { createCipher } = require('crypto');
const fs = require('fs');
const readline = require('readline');
const path = require('path');

const readInterface = readline.createInterface({
    input: fs.createReadStream(path.join(__dirname, 'input.txt')),
});

let adaptersJoltages = [];

readInterface
    .on('line', (line) => {
        adaptersJoltages.push(parseInt(line));
    })
    .on('close', () => {
        adaptersJoltages.sort((a, b) => (a > b ? 1 : a < b ? -1 : 0));

        const outletJoltage = 0;

        let currentCharge = outletJoltage;

        const joltsDiffs = adaptersJoltages.reduce(
            (acc, cur) => {
                if (cur - currentCharge <= 3) {
                    acc[cur - currentCharge] = acc[cur - currentCharge] || 0;
                    acc[cur - currentCharge]++;
                    currentCharge = cur;
                }
                return acc;
            },
            { 3: 1 }
        );

        console.log(joltsDiffs['1'] * joltsDiffs['3']);
    });
