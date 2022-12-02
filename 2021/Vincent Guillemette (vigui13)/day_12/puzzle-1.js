const convertInput = require('../input-converter');

convertInput(__dirname, (x) => ({
    from: x.split('-')[0],
    to: x.split('-')[1],
})).then((caves) => {
    const isBigCave = (cave) => {
        return /[A-Z]/.test(cave);
    };

    const pathCompare = (a, b) => {
        return a.length === b.length && a.every((e) => b.include(e));
    };

    caves = caves
        .concat(caves.map((l) => ({ from: l.to, to: l.from })))
        .filter((l) => l.to !== 'start')
        .filter((l) => l.from !== 'end');

    let paths = [];

    const buildPaths = (pos = 'start', path = []) => {
        path.push(pos);

        const options = caves
            .filter((l) => l.from === pos)
            .filter((l) => !path.filter((p) => !isBigCave(p)).includes(l.to));

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

    console.log(paths, paths.length);
});
