const convertInput = require('../input-converter');

convertInput(__dirname, parseInt).then((depths) => {
    const increaseCount = depths.filter((d, i, a) => {
        return !!i && d > a[i - 1];
    }).length;

    console.log(increaseCount);
});
