const convertInput = require('../input-converter');

convertInput(__dirname, (x) => x.split(',').map((a) => parseInt(a))).then(
    (ages) => {
        ages = ages[0].reduce(
            (acc, cur) => {
                acc[cur]++;
                return acc;
            },
            { 0: 0, 1: 0, 2: 0, 3: 0, 4: 0, 5: 0, 6: 0, 7: 0, 8: 0 }
        );

        for (let index = 0; index < 256; index++) {
            const copy = { ...ages };
            ages['7'] = copy['8'];
            ages['6'] = copy['7'] + ages['0'];
            ages['5'] = copy['6'];
            ages['4'] = copy['5'];
            ages['3'] = copy['4'];
            ages['2'] = copy['3'];
            ages['1'] = copy['2'];
            ages['0'] = copy['1'];
            ages['8'] = copy['0'];
        }

        console.log(Object.keys(ages).reduce((a, c) => a + ages[c], 0));
    }
);
