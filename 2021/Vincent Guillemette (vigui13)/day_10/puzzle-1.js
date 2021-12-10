const convertInput = require('../input-converter');

convertInput(__dirname, (x) => x.split('')).then((lines) => {
    const openCloseMap = {
        '[': ']',
        '(': ')',
        '<': '>',
        '{': '}',
    };

    const priceMap = {
        ')': 3,
        ']': 57,
        '}': 1197,
        '>': 25137,
    };

    const price = lines.reduce((a, l) => {
        const opens = [];

        l.every((s) => {
            if (Object.keys(openCloseMap).includes(s)) {
                opens.push(s);
            } else if (openCloseMap[opens[opens.length - 1]] === s) {
                opens.pop();
            } else {
                a += priceMap[s];
                return false;
            }
            return true;
        });
        return a;
    }, 0);

    console.log(price);
});
