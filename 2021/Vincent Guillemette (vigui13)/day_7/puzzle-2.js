const convertInput = require('../input-converter');

convertInput(
    __dirname,
    (x) => x,
    (x) => x[0].split(',').map((x) => parseInt(x))
).then((positions) => {
    const min = Math.min(...positions);
    const max = Math.max(...positions);
    const addRec = (n, s = 0) => {
        if (n === 0) return s;

        s += n;

        return addRec(n - 1, s);
    };

    const fuelCosts = [];

    for (let index = 0; index <= max - min; index++) {
        const target = min + index;

        fuelCosts.push(
            positions.reduce(
                (a, c) => a + addRec(Math.max(c, target) - Math.min(c, target)),
                0
            )
        );
    }

    console.log(Math.min(...fuelCosts));
});
