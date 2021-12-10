const convertInput = require('../input-converter');

convertInput(__dirname, (x) => x.split('')).then((lines) => {
    const openCloseMap = {
        '[': ']',
        '(': ')',
        '<': '>',
        '{': '}',
    };

    const priceMap = {
        ')': 1,
        ']': 2,
        '}': 3,
        '>': 4,
    };

    const scores = lines
        .filter((l) => {
            const opens = [];

            return l.every((s) => {
                if (Object.keys(openCloseMap).includes(s)) {
                    opens.push(s);
                } else if (openCloseMap[opens[opens.length - 1]] === s) {
                    opens.pop();
                } else {
                    return false;
                }
                return true;
            });
        })
        .map((l) => {
            const opens = [];

            l.forEach((s) => {
                if (Object.keys(openCloseMap).includes(s)) {
                    opens.push(s);
                } else if (openCloseMap[opens[opens.length - 1]] === s) {
                    opens.pop();
                }
            });

            return opens
                .reverse()
                .map((s) => openCloseMap[s])
                .map((s) => priceMap[s])
                .reduce((a, c) => a * 5 + c, 0);
        })
        .sort((a, b) => (a > b ? 1 : a < b ? -1 : 0));

    console.log(scores[Math.floor(scores.length / 2)]);
});
