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
                .sort((a, b) => (a > b ? 1 : a < b ? -1 : 0))
                .reverse()[0] + 1
    );

    board = [];

    for (let index = 0; index < boardHeight; index++) {
        board.push([]);

        for (let index = 0; index < boardWidth; index++) {
            board[board.length - 1].push(0);
        }
    }

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
        } else {
            const p1 = l.p1.x < l.p2.x ? l.p1 : l.p2;
            const p2 = l.p1.x < l.p2.x ? l.p2 : l.p1;

            const stepY = p1.y < p2.y ? 1 : -1;

            for (let index = 0; index <= p2.x - p1.x; index++) {
                board[p1.y + index * stepY][p1.x + index]++;
            }
        }
    });

    const atLeast2OverlapsCount = board
        .map((r) => r.filter((c) => c >= 2).length)
        .reduce((a, c) => a + c, 0);

    console.log(atLeast2OverlapsCount);
});
