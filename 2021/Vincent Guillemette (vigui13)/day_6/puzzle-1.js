const convertInput = require('../input-converter');

convertInput(__dirname, (x) => x.split(',').map((a) => parseInt(a))).then(
    (ages) => {
        [ages] = [[8]];

        for (let index = 0; index < 80; index++) {
            const zeroCount = ages.filter((a) => a === 0).length;

            ages = ages.map((a) => {
                if (a === 0) {
                    a = 6;
                } else {
                    a--;
                }

                return a;
            });

            for (let index = 0; index < zeroCount; index++) {
                ages.push(8);
            }
        }

        console.log(ages.length);
    }
);
