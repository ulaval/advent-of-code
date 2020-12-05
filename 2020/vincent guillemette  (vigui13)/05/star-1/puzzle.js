const input = require('./input.js');

let solution = 0;

input.forEach((i, index) => {
    i = i.split('');

    const rowChars = i.slice(0, 7);
    const colChars = i.slice(7);
    const rowSpan = {
        lowerBound: 0,
        upperBound: 127,
    };
    const colSpan = {
        lowerBound: 0,
        upperBound: 8,
    };

    rowChars.forEach((rc) => {
        if (rc === 'F') {
            rowSpan.upperBound =
                rowSpan.lowerBound +
                Math.floor((rowSpan.upperBound - rowSpan.lowerBound) / 2);
        } else if (rc === 'B') {
            rowSpan.lowerBound =
                rowSpan.lowerBound +
                Math.ceil((rowSpan.upperBound - rowSpan.lowerBound) / 2);
        }
    });

    colChars.forEach((cc) => {
        if (cc === 'L') {
            colSpan.upperBound =
                colSpan.lowerBound +
                Math.floor((colSpan.upperBound - colSpan.lowerBound) / 2);
        } else if (cc === 'R') {
            colSpan.lowerBound =
                colSpan.lowerBound +
                Math.ceil((colSpan.upperBound - colSpan.lowerBound) / 2);
        }
    });

    solution =
        rowSpan.lowerBound * 8 + colSpan.lowerBound > solution
            ? rowSpan.lowerBound * 8 + colSpan.lowerBound
            : solution;
});

console.log(solution);
