const convertInput = require('../input-converter');

convertInput(__dirname, (x) => ({
    p1: {
        x: parseInt(x.split(' -> ')[0].split(',')[0]),
        y: parseInt(x.split(' -> ')[0].split(',')[1]),
    },
    p2: {
        x: parseInt(x.split(' -> ')[1].split(',')[0]),
        y: parseInt(x.split(' -> ')[1].split(',')[1]),
    },
})).then((lines) => {
    const [boardHeight, boardWidth] = ['y', 'x'].map(
        (axis) =>
            lines
                .map((l) => Math.max(l.p1[axis], l.p2[axis]))
                .sort((a, b) => (a > b ? -1 : a < b ? 1 : 0))[0] + 1
    );

    board = new Array(boardHeight)
        .fill(undefined)
        .map((_) => new Array(boardWidth).fill(undefined).map((_) => 0));

    lines.forEach((l) => {
        if (l.p1.y === l.p2.y) {
            const minX = Math.min(l.p1.x, l.p2.x);
            const maxX = Math.max(l.p1.x, l.p2.x);

            for (let index = 0; index <= maxX - minX; index++) {
                board[l.p1.y][minX + index]++;
            }
        } else if (l.p1.x === l.p2.x) {
            const minY = Math.min(l.p1.y, l.p2.y);
            const maxY = Math.max(l.p1.y, l.p2.y);

            for (let index = 0; index <= maxY - minY; index++) {
                board[minY + index][l.p1.x]++;
            }
        }
    });

    const atLeast2OverlapsCount = board
        .map((r) => r.filter((c) => c >= 2).length)
        .reduce((a, c) => a + c, 0);

    console.log(atLeast2OverlapsCount);
});
