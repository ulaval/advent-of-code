const convertInput = require('../input-converter');

convertInput(__dirname, (x) => x.split('').map((x) => parseInt(x))).then(
    (map) => {
        const getNorth = (point) => {
            if (!map[point.y - 1]) return null;
            return { ...point, ...{ y: point.y - 1 } };
        };
        const getSouth = (point) => {
            if (!map[point.y + 1]) return null;
            return { ...point, ...{ y: point.y + 1 } };
        };
        const getEast = (point) => {
            if (typeof map[point.y][point.x + 1] === 'undefined') return null;
            return { ...point, ...{ x: point.x + 1 } };
        };
        const getWest = (point) => {
            if (typeof map[point.y][point.x - 1] === 'undefined') return null;
            return { ...point, ...{ x: point.x - 1 } };
        };
        const getNorhtEast = (point) => {
            if (
                !map[point.y - 1] ||
                typeof map[point.y - 1][point.x + 1] === 'undefined'
            )
                return null;
            return { ...point, ...{ x: point.x + 1, y: point.y - 1 } };
        };
        const getSouthEast = (point) => {
            if (
                !map[point.y + 1] ||
                typeof map[point.y + 1][point.x + 1] === 'undefined'
            )
                return null;
            return { ...point, ...{ x: point.x + 1, y: point.y + 1 } };
        };
        const getSouthWest = (point) => {
            if (
                !map[point.y + 1] ||
                typeof map[point.y + 1][point.x - 1] === 'undefined'
            )
                return null;
            return { ...point, ...{ x: point.x - 1, y: point.y + 1 } };
        };
        const getNorthWest = (point) => {
            if (
                !map[point.y - 1] ||
                typeof map[point.y - 1][point.x - 1] === 'undefined'
            )
                return null;
            return { ...point, ...{ x: point.x - 1, y: point.y - 1 } };
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

        const getFlowAdjacents = (point) =>
            [getNorth, getEast, getSouth, getWest].map((f) => f(point));

        const lowPoints = map.reduce((a, r, ri) => {
            r.forEach((p, pi) => {
                if (
                    p ===
                    Math.min(
                        p,
                        ...getAdjacents({ x: pi, y: ri })
                            .filter((p) => p !== null)
                            .map((p) => map[p.y][p.x])
                    )
                ) {
                    a.push({ x: pi, y: ri });
                }
            });
            return a;
        }, []);

        console.log(
            lowPoints
                .map((lp) => {
                    let filled = false;
                    let cursor = lp;
                    let basin = [cursor];

                    while (!filled) {
                        const expand = (point) => {
                            const adjacents = getFlowAdjacents(point)
                                .filter((a) => !!a)
                                .filter((a) => map[a.y][a.x] < 9)
                                .filter(
                                    (a) =>
                                        !basin
                                            .map((b) => JSON.stringify(b))
                                            .includes(JSON.stringify(a))
                                );
                            basin = basin.concat(adjacents);
                        };
                        const before = basin.length;

                        basin.forEach((b) => expand(b));

                        if (before === basin.length) filled = true;
                    }
                    return basin.length;
                })
                .sort((a, b) => (a > b ? -1 : a < b ? 1 : 0))
                .slice(0, 3)
                .reduce((a, c) => a * c, 1)
        );
    }
);
