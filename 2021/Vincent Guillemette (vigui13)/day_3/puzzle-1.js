const convertInput = require('../input-converter');

convertInput(__dirname, (e) =>
    e.split('').map((f) => parseInt(f.replace('0', '-1')))
).then((report) => {
    const gammaRateBinFlags = report
        .reduce((acc, cur) => {
            for (let index = 0; index < cur.length; index++) {
                acc[index] += cur[index];
            }
            return acc;
        }, new Array(report[0].length).fill(0))
        .map((gr) => (gr < 0 ? 0 : 1));

    const epsilonRateBinFlags = gammaRateBinFlags.map((f) => (f === 0 ? 1 : 0));

    const powerConsumption = [gammaRateBinFlags, epsilonRateBinFlags]
        .map((bf) =>
            parseInt(
                bf.reduce((a, c) => a + c, ''),
                2
            )
        )
        .reduce((a, c) => a * c);

    console.log(powerConsumption);
});
