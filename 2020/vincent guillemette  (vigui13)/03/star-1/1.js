const map = require('./1-input');

const slop = {
    x: 3,
    y: -1,
};
const pos = {
    x: 0,
    y: 0,
};

console.log(
    map.reduce((acc) => {
        pos.x = (pos.x + slop.x) % map[0].length;
        pos.y += slop.y * -1;

        if (pos.y >= map.length) {
            return acc;
        }

        if (map[pos.y][pos.x] === '#') {
            acc++;
        }

        return acc;
    }, 0)
);
