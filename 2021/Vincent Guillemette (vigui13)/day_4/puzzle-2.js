const convertInput = require('../input-converter');

convertInput(__dirname).then((bingo) => {
    const numbers = bingo
        .shift()
        .split(',')
        .map((cn) => parseInt(cn));

    const cards = bingo
        .reduce((acc, cur) => {
            if (!cur) {
                acc.push([]);
            } else {
                acc[acc.length - 1].push(
                    cur
                        .split(' ')
                        .map((c) => c.trim())
                        .filter((c) => !!c)
                        .map((c) => ({ value: parseInt(c), marked: false }))
                );
            }

            return acc;
        }, [])
        .map((c) => ({ won: false, rows: c }));

    const reversedCard = (card) =>
        card[0].map((_, ci) => card.map((row) => row[ci]));

    const playNumber = (card, number) => {
        if (card.won) return;

        let winner = null;

        [card.rows, reversedCard(card.rows)].every((c) =>
            c.every((row) =>
                row.every((square) => {
                    if (square.value === number) {
                        square.marked = true;
                    }

                    if (row.every((square) => square.marked)) {
                        card.won = true;
                        winner = { card, number };
                        return false;
                    }
                    return true;
                })
            )
        );

        return winner;
    };

    const lastWinner = numbers
        .map((n) => cards.map((c) => playNumber(c, n)).find((e) => !!e))
        .filter((w) => !!w)
        .pop();

    console.log(lastWinner);

    const unmarkedSum = lastWinner.card.rows.reduce(
        (accRow, curRow) => (
            console.log(curRow),
            accRow +
                curRow
                    .filter((square) => !square.marked)
                    .map((s) => s.value)
                    .reduce((acc, cur) => acc + cur, 0)
        ),
        0
    );

    console.log(unmarkedSum * lastWinner.number);
});
