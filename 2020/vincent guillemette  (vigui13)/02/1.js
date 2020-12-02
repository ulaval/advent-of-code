const input = require('./1-input.js');

let solution = 0;

input.forEach(i => {
    const parts = i.split(' ');
    const min = parseFloat(parts[0].split('-')[0]);
    const max = parseFloat(parts[0].split('-')[1]);
    const needle = parts[1].replace(':', '');
    const hay = parts[2].split('');

    const striped = hay.filter(c => c === needle);

    if (striped.length >= min && striped.length <= max) {
        solution++;
    }
});

console.log(solution);