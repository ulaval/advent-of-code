// https://github.com/simardo/adventofcode2020/tree/main/src/20

console.log('20 décembre');

type Tlbr = [[number, number], [number, number], [number, number], [number, number]];

type Tile = {
    id: number;
    map: string[][];

    tlbr: Tlbr;
    sides: Set<number>;
    inPuzzle?: boolean;

    top?: Tile;
    left?: Tile;
    bottom?: Tile;
    right?: Tile;
}

function getTlbr(map: string[][]): Tlbr {
    let top1: number = 0;
    let bottom1: number = 0;
    for (let x: number = 0; x < map[0].length; x++) {
        top1 = top1 << 1;
        bottom1 = bottom1 << 1;
        if (map[0][x] === '#') {
            top1 |= 1;
        }
        if (map[map.length - 1][x] === '#') {
            bottom1 |= 1;
        }
    }

    let left1: number = 0;
    let right1: number = 0;
    for (let y: number = 0; y < map.length; y++) {
        left1 = left1 << 1;
        right1 = right1 << 1;
        if (map[y][0] === '#') {
            left1 |= 1;
        }
        if (map[y][map.length - 1] === '#') {
            right1 |= 1;
        }
    }

    return [[top1, reverse(top1)], [left1, reverse(left1)], [bottom1, reverse(bottom1)], [right1, reverse(right1)]];
}

function getSides(tlbr: Tlbr): Set<number> {
    const [[top1, top2], [left1, left2], [bottom1, bottom2], [right1, right2]] = tlbr;

    const result: Set<number> = new Set<number>();
    result.add(top1);
    result.add(top2);
    result.add(left1);
    result.add(left2);
    result.add(bottom1);
    result.add(bottom2);
    result.add(right1);
    result.add(right2);

    return result;
}

function reverse(n: number): number {
    let result: number = 0;
    for (let i: number = 1; i <= 10; i++) {
        result = result << 1;
        if ((n & 1) === 1) {
            result |= 1;
        }
        n = n >> 1;
    }
    return result;
}

// part 1
function doPart1(input: string): void {
    const tiles: { [key: number]: Tile } = {};

    input.split('\n\n').map(t => {
        const lines: string[] = t.split('\n');
        const [, idS] = lines[0].match(/Tile\s(\d+):/)!;
        const map: string[][] = lines.slice(1).map((l, y) => [...l]);

        const id: number = Number.parseInt(idS);
        const tlbr = getTlbr(map);
        const sides = getSides(tlbr);
        const tile: Tile = {
            id: id,
            map: map,
            tlbr: tlbr,
            sides: sides
        };

        tiles[id] = tile;
    });

    const corners: Tile[] = [];
    Object.values(tiles).forEach(t => {
        let used: number = Object.values(tiles).filter(tt => tt.id !== t.id).reduce((u, tt) => {
            const [[top1, top2], [left1, left2], [bottom1, bottom2], [right1, right2]] = t.tlbr;
            if (tt.sides.has(top1)
                || tt.sides.has(top2)
                || tt.sides.has(left1)
                || tt.sides.has(left2)
                || tt.sides.has(bottom1)
                || tt.sides.has(bottom2)
                || tt.sides.has(right1)
                || tt.sides.has(right2)
            ) {
                return u + 1;
            }
            return u;
        }, 0);
        if (used === 2) {
            corners.push(t);
        }
    });

    const r = corners.reduce((a, c) => c.id * a, 1);

    console.log(r);
}

doPart1(INPUT);

const TOP: number = 0;
const LEFT: number = 1;
const BOTTOM: number = 2;
const RIGHT: number = 3;

function rotateMap(map: string[][]): string[][] {
    const newMap: string[][] = [];
    for (let x: number = 0; x < map[0].length; x++) {
        const line: string[] = [];
        newMap.push(line);
        for (let y: number = map[0].length - 1; y >= 0; y--) {
            line.push(map[y][x])
        }
    }

    return newMap;
}

function rotateTile(tile: Tile, times: number): void {
    for (let time: number = 1; time <= times; time++) {
        tile.map = rotateMap(tile.map);
        tile.tlbr = getTlbr(tile.map);
        tile.sides = getSides(tile.tlbr);
    }
}

function flipHMap(map: string[][]): string[][] {
    const newMap: string[][] = [];
    for (let y: number = map.length - 1; y >= 0; y--) {
        const line: string[] = [];
        newMap.push(line);
        for (let x: number = 0; x < map[y].length; x++) {
            line.push(map[y][x]);
        }
    }

    return newMap;
}

function flipHTile(tile: Tile): void {
    tile.map = flipHMap(tile.map);
    tile.tlbr = getTlbr(tile.map);
    tile.sides = getSides(tile.tlbr);
}

function flipVMap(map: string[][]): string[][] {
    const newMap: string[][] = [];
    for (let y: number = 0; y < map.length; y++) {
        const line: string[] = [];
        newMap.push(line);
        for (let x: number = map[y].length - 1; x >= 0; x--) {
            line.push(map[y][x]);
        }
    }

    return newMap;
}

function flipVTile(tile: Tile): void {
    tile.map = flipVMap(tile.map);
    tile.tlbr = getTlbr(tile.map);
    tile.sides = getSides(tile.tlbr);
}

function connectTop(from: Tile, to: Tile): void {
    const [fromTop1, fromTop2] = from.tlbr[TOP];
    const [[top1, top2], [left1, left2], [bottom1, bottom2], [right1, right2]] = to.tlbr;

    if (fromTop1 === left1 || fromTop2 === left2) {
        rotateTile(from, 1);
        to.left = from;
        from.right = to;
    } else if (fromTop1 === left2 || fromTop2 === left1) {
        rotateTile(from, 1);
        flipHTile(from);
        to.left = from;
        from.right = to;
    } else if (fromTop1 === bottom1 || fromTop2 === bottom2) {
        to.bottom = from;
        from.top = to;
    } else if (fromTop1 === bottom2 || fromTop2 === bottom1) {
        flipVTile(from);
        to.bottom = from;
        from.top = to;
    } else if (fromTop1 === right1 || fromTop2 === right2) {
        rotateTile(from, 3);
        flipHTile(from);
        to.right = from;
        from.left = to;
    } else if (fromTop1 === right2 || fromTop2 === right1) {
        rotateTile(from, 3);
        to.right = from;
        from.left = to;
    } else if (fromTop1 === top1 || fromTop2 === top2) {
        flipHTile(from)
        to.top = from;
        from.bottom = to;
    } else if (fromTop1 === top2 || fromTop2 === top1) {
        flipHTile(from);
        flipVTile(from);
        to.top = from;
        from.bottom = to;
    }
}

function connectLeft(from: Tile, to: Tile): void {
    const [fromLeft1, fromLeft2] = from.tlbr[LEFT];
    const [[top1, top2], [left1, left2], [bottom1, bottom2], [right1, right2]] = to.tlbr;

    if (fromLeft1 === top1 || fromLeft2 === top2) {
        rotateTile(from, 3);
        to.top = from;
        from.bottom = to;
    } else if (fromLeft1 === top2 || fromLeft2 === top1) {
        rotateTile(from, 3);
        flipVTile(from);
        to.top = from;
        from.bottom = to;
    } else if (fromLeft1 === bottom1 || fromLeft2 === bottom2) {
        rotateTile(from, 1);
        flipVTile(from);
        to.bottom = from;
        from.top = to;
    } else if (fromLeft1 === bottom2 || fromLeft2 === bottom1) {
        rotateTile(from, 1);
        to.bottom = from;
        from.top = to;
    } else if (fromLeft1 === right1 || fromLeft2 === right2) {
        to.right = from;
        from.left = to;
    } else if (fromLeft1 === right2 || fromLeft2 === right1) {
        flipHTile(from);
        to.right = from;
        from.left = to;
    } else if (fromLeft1 === left1 || fromLeft2 === left2) {
        flipVTile(from)
        to.left = from;
        from.right = to;
    } else if (fromLeft1 === left2 || fromLeft2 === left1) {
        flipVTile(from);
        flipHTile(from);
        to.left = from;
        from.right = to;
    }
}

function connectBottom(from: Tile, to: Tile): void {
    const [fromBottom1, fromBottom2] = from.tlbr[BOTTOM];
    const [[top1, top2], [left1, left2], [bottom1, bottom2], [right1, right2]] = to.tlbr;

    if (fromBottom1 === left1 || fromBottom2 === left2) {
        rotateTile(from, 3);
        flipHTile(from);
        to.left = from;
        from.right = to;
    } else if (fromBottom1 === left2 || fromBottom2 === left1) {
        rotateTile(from, 3);
        to.left = from;
        from.right = to;
    } else if (fromBottom1 === top1 || fromBottom2 === top2) {
        to.top = from;
        from.bottom = to;
    } else if (fromBottom1 === top2 || fromBottom2 === top1) {
        flipVTile(from);
        to.top = from;
        from.bottom = to;
    } else if (fromBottom1 === right1 || fromBottom2 === right2) {
        rotateTile(from, 1);
        to.right = from;
        from.left = to;
    } else if (fromBottom1 === right2 || fromBottom2 === right1) {
        rotateTile(from, 1);
        flipHTile(from);
        to.right = from;
        from.left = to;
    } else if (fromBottom1 === bottom1 || fromBottom2 === bottom2) {
        flipHTile(from)
        to.bottom = from;
        from.top = to;
    } else if (fromBottom1 === bottom2 || fromBottom2 === bottom1) {
        flipHTile(from);
        flipVTile(from);
        to.bottom = from;
        from.top = to;
    }
}

function connectRight(from: Tile, to: Tile): void {
    const [fromRight1, fromRight2] = from.tlbr[RIGHT];
    const [[top1, top2], [left1, left2], [bottom1, bottom2], [right1, right2]] = to.tlbr;

    if (fromRight1 === top1 || fromRight2 === top2) {
        rotateTile(from, 1);
        flipVTile(from);
        to.top = from;
        from.bottom = to;
    } else if (fromRight1 === top2 || fromRight2 === top1) {
        rotateTile(from, 1);
        to.top = from;
        from.bottom = to;
    } else if (fromRight1 === bottom1 || fromRight2 === bottom2) {
        rotateTile(from, 3);
        to.bottom = from;
        from.top = to;
    } else if (fromRight1 === bottom2 || fromRight2 === bottom1) {
        rotateTile(from, 3);
        flipVTile(from);
        to.bottom = from;
        from.top = to;
    } else if (fromRight1 === left1 || fromRight2 === left2) {
        to.left = from;
        from.right = to;
    } else if (fromRight1 === left2 || fromRight2 === left1) {
        flipHTile(from);
        to.left = from;
        from.right = to;
    } else if (fromRight1 === right1 || fromRight2 === right2) {
        flipVTile(from)
        to.right = from;
        from.left = to;
    } else if (fromRight1 === right2 || fromRight2 === right1) {
        flipVTile(from);
        flipHTile(from);
        to.right = from;
        from.left = to;
    }
}

// part 2
function doPart2(input: string): void {
    const tiles: { [key: number]: Tile } = {};

    input.split('\n\n').map(t => {
        const lines: string[] = t.split('\n');
        const [, idS] = lines[0].match(/Tile\s(\d+):/)!;
        const map: string[][] = lines.slice(1).map((l, y) => [...l]);

        const id: number = Number.parseInt(idS);
        const tlbr = getTlbr(map);
        const sides = getSides(tlbr);
        const tile: Tile = {
            id: id,
            map: map,
            tlbr: tlbr,
            sides: sides
        };

        tiles[id] = tile;
    });

    const puzzle: Tile[] = [];

    while (puzzle.length < Object.values(tiles).length) {
        Object.values(tiles).forEach(t => {
            if (!t.inPuzzle) {
                if (puzzle.length === 0) {
                    t.inPuzzle = true;
                    puzzle.push(t);
                } else {
                    let connect: boolean = false;
                    puzzle.forEach(tt => {
                        const [[top1, top2], [left1, left2], [bottom1, bottom2], [right1, right2]] = t.tlbr;

                        if (tt.sides.has(top1) && tt.sides.has(top2)) {
                            connectTop(t, tt);
                            connect = true;
                        }
                        if (tt.sides.has(left1) && tt.sides.has(left2)) {
                            connectLeft(t, tt);
                            connect = true;
                        }
                        if (tt.sides.has(bottom1) && tt.sides.has(bottom2)) {
                            connectBottom(t, tt);
                            connect = true;
                        }
                        if (tt.sides.has(right1) && tt.sides.has(right2)) {
                            connectRight(t, tt);
                            connect = true;
                        }
                    });
                    if (connect) {
                        t.inPuzzle = true;
                        puzzle.push(t);
                    }
                }
            }
        });
    }

    const topLeft: Tile = puzzle.find(t => !t.top && !t.left)!;

    let image: string[][] = [];
    let bottom: Tile | undefined = topLeft;

    let z: number = 0;
    while (bottom) {
        let right: Tile | undefined = bottom;
        for (let i: number = 1; i <= 8; i++) {
            image.push([]);
        }
        while (right) {
            let c: number = 0;
            right.map.forEach((l, i) => {
                if (i > 0 && i < 9) {
                    image[z + c++].push(...l.slice(1, l.length - 1));
                }
            });
            right = right.right;
        }
        bottom = bottom.bottom;
        z += 8;
    }

    const sharpCount: number = image.reduce((a, l) => {
        return a + l.reduce((aa, ll) => ll === '#' ? aa + 1 : aa,0)
    }, 0);

    let mc: number = 0;
    let iter: number = 0;
    do {
        iter++;
        if (iter % 3 === 0) {
            mc = countMonsters(image);
            image = rotateMap(image);
        } else if (iter % 2 === 0) {
            mc = countMonsters(flipHMap(image));
        } else {
            mc = countMonsters(flipVMap(image));
        }
    } while (mc === 0);

    const MONSTER_SHARP_COUNT: number = 15;

    console.log(sharpCount - (MONSTER_SHARP_COUNT * mc));
}

function countMonsters(map: string[][]): number {
    let monsterCount: number = 0;
    for (let i: number = 1; i < map.length - 1; i++) {
        let gap: number = 0;
        const prev: string[] = map[i - 1];
        const line: string[] = map[i];
        const next: string[] = map[i + 1];
        while (gap < line.length - 20) {
            if (line[gap] === '#' && line[gap + 5] === '#' && line[gap + 6] === '#' && line[gap + 11] === '#' && line[gap + 12] === '#' && line[gap + 17] === '#' && line[gap + 18] === '#' && line[gap + 19] === '#'
                && prev[gap + 18] === '#'
                && next[gap + 1] === '#' && next[gap + 4] === '#' && next[gap + 7] === '#' && next[gap + 10] === '#' && next[gap + 13] === '#' && next[gap + 16] === '#') {
                monsterCount++;
            }
            gap++
        }
    }

    return monsterCount;
}

doPart2(INPUT);