const { group, groupCollapsed } = require('console');
const { createCipher } = require('crypto');
const fs = require('fs');
const readline = require('readline');

const readInterface = readline.createInterface({
    input: fs.createReadStream('./input.txt'),
});

let rules = {};

readInterface
    .on('line', (line) => {
        rules[line.split('contain')[0].trim().replace('bags', 'bag')] = line
            .split('contain')[1]
            .split(',')
            .map((b) => {
                b = b.trim().replace('.', '');
                let count = b.slice(0, b.indexOf(' '));
                if (count !== 'no') {
                    b = b.slice(b.indexOf(count) + 1).trim();
                    count = parseInt(count);
                    return {
                        qty: count,
                        childType: b.replace('bags', 'bag'),
                    };
                }
                return {
                    qty: 0,
                    childType: null,
                };
            });
    })
    .on('close', () => {});
