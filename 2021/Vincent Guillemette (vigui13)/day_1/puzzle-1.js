const inputConverter = require('../input-converter');

inputConverter(__dirname, parseInt).then((depths) => {
    const increaseCount = depths.filter((d, i, a) => {
        return !!i && d > a[i - 1];
    }).length;

    console.log(increaseCount);
});
