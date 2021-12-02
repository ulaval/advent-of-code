const readline = require('readline');
const path = require('path');
const fs = require('fs');

const inputConverter = (inputDir, converter) => {
    return new Promise((res) => {
        const readInterface = readline.createInterface({
            input: fs.createReadStream(path.join(inputDir, 'input.txt')),
        });

        const input = [];

        readInterface
            .on('line', (line) => input.push(converter(line)))
            .on('close', () => res(input));
    });
};

module.exports = inputConverter;
