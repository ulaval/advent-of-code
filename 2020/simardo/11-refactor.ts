// https://github.com/simardo/adventofcode2020/tree/main/src/11

console.log('11 décembre');

function buildMap(input: string): [string, string][][] {
    return input.split('\n').map((l, y) => [...l].map(x => [x, x] as [string, string]));
}

function isOccupied(x: number, y: number, map: [string, string][][]): boolean {
    if (x < 0 || y < 0 || y >= map.length || x >= map[y].length) {
        return false;
    }
    return map[y][x][0] === '#';
}

type RuleFn = (x: number, y: number) => boolean;

function render(map: [string, string][][]): void {
    map.forEach(l => console.log(l.map(c => c[0]).join('')));
    console.log();
}

// part 1
function doPart1(input: string): void {
    const map: [string, string][][] = buildMap(input);

    const rules: RuleFn[] = [
        (x, y) => isOccupied(x - 1, y, map),
        (x, y) => isOccupied(x - 1, y - 1, map),
        (x, y) => isOccupied(x, y - 1, map),
        (x, y) => isOccupied(x + 1, y - 1, map),
        (x, y) => isOccupied(x + 1, y, map),
        (x, y) => isOccupied(x + 1, y + 1, map),
        (x, y) => isOccupied(x, y + 1, map),
        (x, y) => isOccupied(x - 1, y + 1, map)
    ];

    let round: number = 0;
    let same: boolean = false;
    while (!same) {
        round++;
        map.forEach((line, y) => {
            line.forEach((col, x) => {
                let [from, to] = col;
                if (from === 'L') {
                    const occ: number = rules.reduce((count, r) => !r(x, y) ? count + 1 : count, 0);
                    if (occ === 8) {
                        to = '#';
                    }
                } else if (from === '#') {
                    const occ: number = rules.reduce((count, r) => r(x, y) ? count + 1 : count, 0);
                    if (occ >= 4) {
                        to = 'L';
                    }
                }
                map[y][x] = [from, to];
            });
        });

        same = true;
        map.forEach((line, y) => {
            line.forEach((col, x) => {
                same = same && map[y][x][0] === map[y][x][1];
                map[y][x][0] = map[y][x][1];
            })
        })

        // render(map);
    }

    console.log(round);

    const r: number = map.reduce((count, line, y) =>
        count + line.reduce((c, col, x) =>
            map[y][x][0] === '#' ? c + 1 : c
            , 0)
        , 0);

    console.log(r);
}

doPart1(TEST_1);
doPart1(INPUT);


// part 2
function look(x: number, y: number, xFn: (x: number) => number, yFn: (y: number) => number, map: [string, string][][]): boolean {
    x = xFn(x);
    y = yFn(y);
    while (y >= 0 && x >= 0 && y < map.length && x < map[y].length && map[y][x][0] === '.') {
        x = xFn(x);
        y = yFn(y);
    }
    return y >= 0 && x >= 0 && y < map.length && x < map[y].length && map[y][x][0] === '#';
}

function doPart2(input: string): void {
    const map: [string, string][][] = buildMap(input);

    const rules: RuleFn[] = [
        (x, y) => look(x, y, x => x - 1, y => y, map),
        (x, y) => look(x, y, x => x - 1, y => y - 1, map),
        (x, y) => look(x, y, x => x, y => y - 1, map),
        (x, y) => look(x, y, x => x + 1, y => y - 1, map),
        (x, y) => look(x, y, x => x + 1, y => y, map),
        (x, y) => look(x, y, x => x + 1, y => y + 1, map),
        (x, y) => look(x, y, x => x, y => y + 1, map),
        (x, y) => look(x, y, x => x - 1, y => y + 1, map)
    ];

    let round: number = 0;
    let same: boolean = false;
    while (!same) {
        round++;
        map.forEach((line, y) => {
            line.forEach((col, x) => {
                let [from, to] = col;
                if (from === 'L') {
                    const occ: number = rules.reduce((count, r) => !r(x, y) ? count + 1 : count, 0);
                    if (occ === 8) {
                        to = '#';
                    }
                } else if (from === '#') {
                    const occ: number = rules.reduce((count, r) => r(x, y) ? count + 1 : count, 0);
                    if (occ >= 5) {
                        to = 'L';
                    }
                }
                map[y][x] = [from, to];
            });
        });

        same = true;
        map.forEach((line, y) => {
            line.forEach((col, x) => {
                same = same && map[y][x][0] === map[y][x][1];
                map[y][x][0] = map[y][x][1];
            })
        })

        // render(map);
    }

    const r: number = map.reduce((count, line, y) =>
        count + line.reduce((c, col, x) =>
            map[y][x][0] === '#' ? c + 1 : c
            , 0)
        , 0);

    console.log(r);
}

doPart2(TEST_1);
doPart2(INPUT);
