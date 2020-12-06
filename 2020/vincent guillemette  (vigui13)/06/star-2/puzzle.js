const { group, groupCollapsed } = require('console');
const fs = require('fs');
const readline = require('readline');

const readInterface = readline.createInterface({
    input: fs.createReadStream('./input.txt'),
});

let groups = [[]];
let raw = [];

readInterface
    .on('line', (line) => {
        raw.push(line);
    })
    .on('close', () => {
        raw.forEach((r) => {
            if (!r) {
                groups.push([]);
                return;
            }

            groups[groups.length - 1].push(r);
        });

        groups = groups.map((g) => g.map((g) => g.split('')));

        groups = groups.reduce((acc, cur, index) => {
            acc.push({
                size: cur.length,
                answers: cur.reduce((acc, cur) => (acc || cur).concat(cur), []),
            });
            return acc;
        }, []);

        const solution = groups.reduce((acc, cur) => {
            cur.answers = cur.answers.reduce((acc, cur) => {
                acc[cur] = (acc[cur] || 0) + 1;
                return acc;
            }, {});

            Object.values(cur.answers).forEach((a) => {
                if (a === cur.size) acc++;
            });
            return acc;
        }, 0);

        console.log(solution);
    });
