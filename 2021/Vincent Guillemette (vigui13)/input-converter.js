// si vous le voulez prennez le :P

const readline = require('readline');
const path = require('path');
const fs = require('fs');

const convertInput = (
    inputDir,
    elementConverter = (x) => x,
    arrayConverter = (x) => x
) => {
    return new Promise((res) => {
        const readInterface = readline.createInterface({
            input: fs.createReadStream(path.join(inputDir, 'input.txt')),
        });

        const input = [];

        readInterface
            .on('line', (line) => input.push(elementConverter(line)))
            .on('close', () => res(arrayConverter(input)));
    });
};

module.exports = convertInput;
