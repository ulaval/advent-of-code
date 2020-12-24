// https://github.com/simardo/adventofcode2020/tree/main/src/24

console.log('24 décembre');

const re: RegExp = /(nw|ne|sw|se|w|e)/g;

type Coord = [number, number];

type Tile = {
    coord: Coord;
    black?: boolean;
    next?: boolean
}

function getKey(coord: Coord): string {
    const [x, y] = coord;
    return `x:${x},y:${y}`;
}

type DirectionFn = (tile: Tile) => Coord;

// part 1 & part 2
function doPart12(input: string, part2: boolean): void {
    const tilesInstr: string[] = input.split('\n');

    const tiles: { [key: string]: Tile } = {};

    const nw: DirectionFn = t => {
        const [x, y] = t.coord;
        return [x - 1, y - 1];
    }

    const w: DirectionFn = t => {
        const [x, y] = t.coord;
        return [x - 2, y];
    }

    const sw: DirectionFn = t => {
        const [x, y] = t.coord;
        return [x - 1, y + 1];
    }

    const se: DirectionFn = t => {
        const [x, y] = t.coord;
        return [x + 1, y + 1];
    }

    const e: DirectionFn = t => {
        const [x, y] = t.coord;
        return [x + 2, y];
    }

    const ne: DirectionFn = t => {
        const [x, y] = t.coord;
        return [x + 1, y - 1];
    }

    const fns: { [key: string]: DirectionFn } = {};
    fns['nw'] = nw;
    fns['w'] = w;
    fns['sw'] = sw;
    fns['se'] = se;
    fns['e'] = e;
    fns['ne'] = ne;

    const ref: Tile = {
        coord: [0, 0]
    };

    tiles[getKey(ref.coord)] = ref;

    tilesInstr.forEach(t => {
        let match: RegExpMatchArray | null;

        let current: Tile = ref;

        while ((match = re.exec(t)) !== null) {
            const [, direction] = match;

            const nextCoord: Coord = fns[direction](current);
            const key: string = getKey(nextCoord);

            let next: Tile | undefined;
            next = tiles[key];
            if (!next) {
                next = { coord: nextCoord };
                tiles[key] = next;
            }

            current = next;
        }

        current.black = !current.black;
    });

    // part 1
    const r = Object.values(tiles).reduce((b, t) => t.black ? b + 1 : b, 0);
    console.log(r);

    const directions: string[] = ['nw', 'w', 'sw', 'se', 'e', 'ne'];

    const adj = (tile: Tile) => {
        return directions.reduce((a, d) => {
            const coord: Coord = fns[d](tile);
            const adjt: Tile | undefined = tiles[getKey(coord)];
            if (adjt) {
                a.push(adjt);
            }
            return a;
        }, [] as Tile[]);
    }

    const expand = (tile: Tile) => {
        return directions.forEach(d => {
            const coord: Coord = fns[d](tile);
            let adjt: Tile | undefined = tiles[getKey(coord)];
            if (!adjt) {
                adjt = {
                    coord: coord
                }
                tiles[getKey(coord)] = adjt;
            }
        });
    }

    if (part2) {
        let times: number = 0;
        while (times++ < 100) {
            Object.values(tiles).forEach(t => expand(t));

            Object.values(tiles).forEach(t => {
                t.next = t.black;

                const ajdb: number = adj(t).reduce((b, a) => a.black ? b + 1 : b, 0);
                if (t.black && (ajdb === 0 || ajdb > 2)) {
                    t.next = false;
                } else if (!t.black && ajdb === 2) {
                    t.next = true;
                }
            });

            Object.values(tiles).forEach(t => {
                t.black = t.next;
            });
        }

        // part 2
        const r = Object.values(tiles).reduce((b, t) => t.black ? b + 1 : b, 0);
        console.log(r);
    }
}

doPart12(INPUT, false);
doPart12(INPUT, true);
