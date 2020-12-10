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
        adaptersJoltages.unshift(0);
        adaptersJoltages.push(
            adaptersJoltages[adaptersJoltages.length - 1] + 3
        );
        let test = 0;

        const solve = (currentCharge = adaptersJoltages[0]) => {
            if (
                currentCharge === adaptersJoltages[adaptersJoltages.length - 1]
            ) {
                test++;
                return;
            }

            adaptersJoltages
                .slice(
                    adaptersJoltages.indexOf(
                        adaptersJoltages.find((j) => j > currentCharge)
                    )
                )
                .forEach((j) => {
                    if (j - currentCharge <= 3) {
                        solve(j);
                    }
                });
        };

        solve();

        console.log(test);
    });
