// https://github.com/simardo/adventofcode2020/tree/main/src/17

console.log('17 décembre');

type Cube = {
    x: number,
    y: number,
    z: number,
    w?: number;
    active: boolean;
    next: boolean;
}

type Space = { [key: string]: Cube };

function getCoord(x: number, y: number, z: number, w?: number): string {
    return w? `x:${x},y:${y},z:${z},w:${w}` : `x:${x},y:${y},z:${z}`;
}

function getNeighbor(space: Space, x: number, y: number, z: number, w?: number): Cube {
    const coord: string = getCoord(x, y, z, w);

    let result: Cube = space[coord];
    if (!result) {
        result = { x: x, y: y, z: z, w:w, active: false, next: false };
        space[coord] = result;
    }

    return result;
}

type PermutFn = (x: number) => number;
type PermutResultFn = (x: number[]) => void;

function permute(v: number[], i: number, fn: PermutResultFn) {
    const poss: PermutFn[] = [x => x, x => x + 1, x => x - 1];
    poss.forEach(p => {
        const vv = [...v];
        vv[i] = p(vv[i]);
        if (i < v.length - 1) {
            permute(vv, i + 1, fn)
        } else {
            fn(vv);
        }
    });
}

// part 1
function doPart1(input: string): void {
    const space: Space = {};
    input.split('\n').map((l, y) => [...l].forEach((ll, x) => space[getCoord(x, y, 0)] = { x: x, y: y, z: 0, active: ll === '#', next: ll === '#' }));

    Object.values(space).forEach(cube => {
        permute([cube.x, cube.y, cube.z], 0, per => getNeighbor(space, per[0], per[1], per[2]));
    });

    let cycle: number = 0;
    while (cycle++ < 6) {
        Object.values(space).forEach(cube => {
            let activity: number = 0;
            permute([cube.x, cube.y, cube.z], 0, per => {
                if (per[0] !== cube.x || per[1] !== cube.y || per[2] !== cube.z) {
                    activity = getNeighbor(space, per[0], per[1], per[2]).active ? activity + 1 : activity
                }
            });

            if (cube.active) {
                cube.next = activity === 2 || activity === 3;
            } else {
                cube.next = activity === 3;
            }
        });

        Object.values(space).forEach(cube => cube.active = cube.next);
    }
    const c = Object.values(space).reduce((a, cube) => cube.active ? a + 1 : a, 0);
    console.log(c);
}

doPart1(INPUT);

// part 2
function doPart2(input: string): void {
    const space: Space = {};
    input.split('\n').map((l, y) => [...l].forEach((ll, x) => space[getCoord(x, y, 0, 0)] = { x: x, y: y, z: 0, w: 0, active: ll === '#', next: ll === '#' }));

    Object.values(space).forEach(cube => {
        permute([cube.x, cube.y, cube.z, cube.w!], 0, per => getNeighbor(space, per[0], per[1], per[2], per[3]));
    });

    let cycle: number = 0;
    while (cycle++ < 6) {
        Object.values(space).forEach(cube => {
            let activity: number = 0;
            permute([cube.x, cube.y, cube.z, cube.w!], 0, per => {
                if (per[0] !== cube.x || per[1] !== cube.y || per[2] !== cube.z || per[3] !== cube.w) {
                    activity = getNeighbor(space, per[0], per[1], per[2], per[3]).active ? activity + 1 : activity
                }
            });

            if (cube.active) {
                cube.next = activity === 2 || activity === 3;
            } else {
                cube.next = activity === 3;
            }
        });

        Object.values(space).forEach(cube => cube.active = cube.next);
    }
    const c = Object.values(space).reduce((a, cube) => cube.active ? a + 1 : a, 0);
    console.log(c);
}

doPart2(INPUT);
