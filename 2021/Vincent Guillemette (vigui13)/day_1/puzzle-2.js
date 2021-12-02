const convertInput = require('../input-converter');

convertInput(__dirname, parseInt).then((depths) => {
    function computeWindows(windows = [], i = 0) {
        const remainer = depths.slice(i);

        if (remainer.length < 3) return windows;

        windows.push(remainer.slice(0, 3));

        return computeWindows(windows, i + 1);
    }

    const windowsSum = computeWindows().map((w) =>
        w.reduce((a, c) => (a += c), 0)
    );

    const increaseCount = windowsSum.filter((ws, i, a) => {
        return !!i && ws > a[i - 1];
    }).length;

    console.log(increaseCount);
});
