const convertInput = require('../input-converter');

convertInput(
    __dirname,
    (x) => ({
        from: x.split('-')[0],
        to: x.split('-')[1],
    }),
    (x) =>
        x
            .concat(x.map((l) => ({ from: l.to, to: l.from })))
            .filter((l) => l.to !== 'start')
            .filter((l) => l.from !== 'end')
).then((caves) => {
    const isBigCave = (cave) => {
        return /[A-Z]/.test(cave);
    };

    let paths = [];

    const buildPaths = (pos = 'start', path = []) => {
        path.push(pos);

        const options = caves
            .filter((c) => c.from === pos)
            .filter((c) => {
                const smallCavesInPath = path.filter((p) => !isBigCave(p));
                const alreadyHaveASmallCaveVisitedTwice =
                    new Set(smallCavesInPath).size !== smallCavesInPath.length;

                if (alreadyHaveASmallCaveVisitedTwice) {
                    return !smallCavesInPath.includes(c.to);
                }
                return true;
            });

        if (!options.length) {
            paths = paths.filter((p) => p.includes('end'));
            return;
        }

        return options.forEach((o) => {
            const copy = [...path];

            paths.push(copy);

            buildPaths(o.to, copy);
        });
    };

    buildPaths();

    console.log(paths.length);
});
