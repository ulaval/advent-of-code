const convertInput = require('../input-converter');

convertInput(__dirname, (x) => x.split('').map((x) => parseInt(x))).then(
    (lines) => {
        const getNorth = (point) => {
            if (!lines[point.y - 1]) return null;
            return { ...point, ...{ y: point.y - 1 } };
        };
        const getSouth = (point) => {
            if (!lines[point.y + 1]) return null;
            return { ...point, ...{ y: point.y + 1 } };
        };
        const getEast = (point) => {
            if (typeof lines[point.y][point.x + 1] === 'undefined') return null;
            return { ...point, ...{ x: point.x + 1 } };
        };
        const getWest = (point) => {
            if (typeof lines[point.y][point.x - 1] === 'undefined') return null;
            return { ...point, ...{ x: point.x - 1 } };
        };
        const getNorhtEast = (point) => {
            if (
                !lines[point.y - 1] ||
                typeof lines[point.y - 1][point.x + 1] === 'undefined'
            )
                return null;
            return { x: point.x + 1, y: point.y - 1 };
        };
        const getSouthEast = (point) => {
            if (
                !lines[point.y + 1] ||
                typeof lines[point.y + 1][point.x + 1] === 'undefined'
            )
                return null;
            return { x: point.x + 1, y: point.y + 1 };
        };
        const getSouthWest = (point) => {
            if (
                !lines[point.y + 1] ||
                typeof lines[point.y + 1][point.x - 1] === 'undefined'
            )
                return null;
            return { x: point.x - 1, y: point.y + 1 };
        };
        const getNorthWest = (point) => {
            if (
                !lines[point.y - 1] ||
                typeof lines[point.y - 1][point.x - 1] === 'undefined'
            )
                return null;
            return { x: point.x - 1, y: point.y - 1 };
        };

        const getAdjacents = (point) =>
            [
                getNorth,
                getNorhtEast,
                getEast,
                getSouthEast,
                getSouth,
                getSouthWest,
                getWest,
                getNorthWest,
            ].map((f) => f(point));

        let flashes = 0;

        for (let index = 0; index < 200; index++) {
            lines.forEach((l, li) => {
                l.forEach((_, ei) => {
                    lines[li][ei]++;
                });
            });

            let newFlash = true;
            let flashed = [];

            while (newFlash) {
                const flashings = lines.reduce(
                    (a, c, li) =>
                        a.concat(
                            c
                                .map((_, ci) => ({ x: ci, y: li }))
                                .filter((_, ci) => lines[li][ci] > 9)
                                .filter(
                                    (c) =>
                                        !flashed.some(
                                            (f) => f.x === c.x && f.y === c.y
                                        )
                                )
                        ),
                    []
                );

                flashed = flashed.concat(flashings);
                newFlash = !!flashings.length;

                flashings.forEach((f) => {
                    const adjacents = getAdjacents(f).filter((a) => a !== null);

                    adjacents.forEach((a) => {
                        lines[a.y][a.x]++;
                    });
                });

                flashes += flashings.length;
            }

            flashed.forEach((f) => (lines[f.y][f.x] = 0));
        }

        console.table(lines);
        console.log(flashes);
    }
);
