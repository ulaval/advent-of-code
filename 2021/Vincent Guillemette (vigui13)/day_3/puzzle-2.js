const convertInput = require('../input-converter');

convertInput(__dirname, (e) => e.split('').map((s) => parseInt(s))).then(
    (report) => {
        const mostCommonRating = (compareFn, remainer = [...report], i = 0) => {
            if (remainer.length === 1) {
                return parseInt(remainer[0].join(''), 2);
            }

            const [zeros, ones] = [0, 1].map((b) =>
                remainer.filter((e) => e[i] === b)
            );

            return mostCommonRating(compareFn, compareFn(ones, zeros), i + 1);
        };

        const [oxygenGeneretorRating, CO2ScrubberRating] = [
            (x, y) => (x.length >= y.length ? x : y),
            (x, y) => (x.length < y.length ? x : y),
        ].map((fn) => mostCommonRating(fn));

        const lifeSupportRating = oxygenGeneretorRating * CO2ScrubberRating;

        console.log(lifeSupportRating);
    }
);
