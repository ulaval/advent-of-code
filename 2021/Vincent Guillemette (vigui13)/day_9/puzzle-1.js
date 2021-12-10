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

        const answer = map.reduce((a, r, ri) => {
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
                    a += p + 1;
                }
            });
            return a;
        }, 0);
        console.log(answer);
    }
);
