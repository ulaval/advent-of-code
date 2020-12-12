// https://github.com/simardo/adventofcode2020/tree/main/src/12

console.log('12 décembre');

type MoveFn = (d: number) => void;
type MovesFn = [MoveFn, MovesFn | undefined, MovesFn | undefined];

// part 1
function doPart1(input: string): void {
    const directions: [string, number][] = input.split('\n').map(d => [d[0], Number.parseInt(d.substr(1))]);

    let coord: [number, number] = [0, 0];

    const moveEast: MovesFn = [(d: number) => coord[0] = coord[0] + d, undefined, undefined];
    const moveNorth: MovesFn = [(d: number) => coord[1] = coord[1] - d, undefined, undefined];
    const moveWest: MovesFn = [(d: number) => coord[0] = coord[0] - d, undefined, undefined];
    const moveSouth: MovesFn = [(d: number) => coord[1] = coord[1] + d, undefined, undefined];

    moveEast[1] = moveNorth;
    moveEast[2] = moveSouth;
    moveNorth[1] = moveWest;
    moveNorth[2] = moveEast;
    moveWest[1] = moveSouth;
    moveWest[2] = moveNorth;
    moveSouth[1] = moveEast;
    moveSouth[2] = moveWest;

    let main = moveEast;

    directions.forEach(d => {
        const [dir, num] = d;
        if (dir === 'F') {
            main[0](num);
        } else if (dir === 'N') {
            moveNorth[0](num);
        } else if (dir === 'S') {
            moveSouth[0](num);
        } else if (dir === 'E') {
            moveEast[0](num);
        } else if (dir === 'W') {
            moveWest[0](num);
        } else if ((dir === 'L' && num === 90) || (dir === 'R' && num === 270)) {
            main = main[1]!;
        } else if (num === 180) {
            main = main[1]![1]!;
        } else if ((dir === 'R' && num === 90) || (dir === 'L' && num === 270)) {
            main = main[2]!;
        }
    });

    console.log(Math.abs(coord[0]) + Math.abs(coord[1]));
}

doPart1(TEST_1);
doPart1(INPUT);

// part 2
function doPart2(input: string): void {
    const directions: [string, number][] = input.split('\n').map(d => [d[0], Number.parseInt(d.substr(1))]);

    let waypoint = [10, -1];
    let coord = [0, 0];

    const moveEast = (d: number) => waypoint[0] = waypoint[0] + d;
    const moveNorth = (d: number) => waypoint[1] = waypoint[1] - d;
    const moveWest = (d: number) => waypoint[0] = waypoint[0] - d;
    const moveSouth = (d: number) => waypoint[1] = waypoint[1] + d;

    directions.forEach(d => {
        const [dir, num] = d;
        if (dir === 'F') {
            coord[0] = coord[0] + waypoint[0] * num;
            coord[1] = coord[1] + waypoint[1] * num;
        } else if (dir === 'N') {
            moveNorth(num);
        } else if (dir === 'S') {
            moveSouth(num);
        } else if (dir === 'E') {
            moveEast(num);
        } else if (dir === 'W') {
            moveWest(num);
        } else if ((dir === 'L' && num === 90) || (dir === 'R' && num === 270)) {
            const [e, n] = waypoint;
            waypoint[0] = n;
            waypoint[1] = -e;
        } else if (num === 180) {
            const [e, n] = waypoint;
            waypoint[0] = -e;
            waypoint[1] = -n;
        } else if ((dir === 'R' && num === 90) || (dir === 'L' && num === 270)) {
            const [e, n] = waypoint;
            waypoint[0] = -n;
            waypoint[1] = e;
        }
    });

    console.log(Math.abs(coord[0]) + Math.abs(coord[1]));
}

doPart2(TEST_1);
doPart2(INPUT);