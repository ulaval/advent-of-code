// https://github.com/simardo/adventofcode2020/tree/main/src/03

console.log('3 décembre');

function buildMap(input: string): string[][] {
    return input.split('\n').map((l, y) => [...l]);
}

// part 1
function doPart1(input: string): void {
    const map: string[][] = buildMap(input);
    const mapWidth: number = map[0].length;

    let count: number = 0;
    let pos: number[] = [0, 0];
    while (pos[1] < map.length - 1) {
        pos = [pos[0] + 3, pos[1] + 1];
        if (map[pos[1]][(pos[0] % mapWidth)] === '#') {
            count++;
        }
    }

    console.log(count);
}

doPart1(INPUT);

// part 2
function doPart2(input: string): void {
    const map: string[][] = buildMap(input);
    const mapWidth: number = map[0].length;

    const slopes: number[][] = [[1,1],[3,1],[5,1],[7,1],[1,2]];
    const result: number = slopes.reduce((p,s) => {
        let count: number = 0;
        let pos: number[] = [0, 0];
        while (pos[1] < map.length - 1) {
            pos = [pos[0] + s[0], pos[1] + s[1]];
            if (map[pos[1]][(pos[0] % mapWidth)] === '#') {
                count++;
            }
        }
        return p * count;
    }, 1);

    console.log(result);
}

doPart2(INPUT);
