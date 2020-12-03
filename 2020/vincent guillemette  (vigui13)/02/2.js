const input = require('./1-input.js');

const XOR = (a, b) => {
    return (a || b) && !(a && b);
};

let solution = 0;

input.forEach((i) => {
    const parts = i.split(' ');
    const pos1 = parseFloat(parts[0].split('-')[0]);
    const pos2 = parseFloat(parts[0].split('-')[1]);
    const needle = parts[1].replace(':', '');
    const hay = parts[2].split('');

    if (XOR(hay[pos1 - 1] === needle, hay[pos2 - 1] === needle)) {
        solution++;
    }
});

console.log(solution);
