const map = require('./2-input');

const slops = [
    {
        x: 1,
        y: -1,
    },
    {
        x: 3,
        y: -1,
    },
    {
        x: 5,
        y: -1,
    },
    {
        x: 7,
        y: -1,
    },
    {
        x: 1,
        y: -2,
    },
];
const pos = {
    x: 0,
    y: 0,
};

console.log(
    slops.reduce((acc, cur) => {
        pos.x = 0;
        pos.y = 0;

        acc *= map.reduce((acc) => {
            pos.x = (pos.x + cur.x) % map[0].length;
            pos.y += cur.y * -1;

            if (pos.y >= map.length) {
                return acc;
            }

            if (map[pos.y][pos.x] === '#') {
                acc++;
            }

            return acc;
        }, 0);

        return acc;
    }, 1)
);
