import fs from 'fs';

const grid: string[][] = fs.readFileSync(__dirname + '/data-3.txt', 'utf8').split('\n').map(value => value.split(''));

const countTreesEncountered = (grid: string[][], xSpeed: number, ySpeed: number): number => {
    const width: number = grid[0].length;
    const height: number = grid.length;

    let x: number = 0;
    let y: number = 0;
    let trees: number = 0;

    while (y < height) {
        if (grid[y][x % width] === '#') {
            trees += 1;
        }
        x += xSpeed;
        y += ySpeed;
    }

    return trees;
}

console.log(countTreesEncountered(grid, 3, 1));


const tracks: [number, number][] = [[1, 1], [3, 1], [5, 1], [7, 1], [1, 2]]

const treesProduct = tracks.map(([xSpeed, ySpeed]) => countTreesEncountered(grid, xSpeed, ySpeed))
    .reduce((acc: number, treeCount: number) => acc * treeCount, 1);


console.log(treesProduct);
