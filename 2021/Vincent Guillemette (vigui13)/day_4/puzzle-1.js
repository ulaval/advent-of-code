const convertInput = require('../input-converter');

convertInput(__dirname).then((bingo) => {
    const numbers = bingo
        .shift()
        .split(',')
        .map((cn) => parseInt(cn));

    const cards = bingo.reduce((acc, cur) => {
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
    }, []);

    const reversedCard = (card) =>
        card[0].map((_, ci) => card.map((row) => row[ci]));

    const playNumber = (card, number) => {
        let winner = null;

        [card, reversedCard(card)].every((c) =>
            c.every((row) =>
                row.every((square) => {
                    if (square.value === number) {
                        square.marked = true;
                    }

                    if (row.every((square) => square.marked)) {
                        winner = { card, number };
                        return false;
                    }
                    return true;
                })
            )
        );

        return winner;
    };

    numbers.every((n) => {
        const winner = cards.map((c) => playNumber(c, n)).find((e) => !!e);

        if (winner) {
            const unmarkedSum = winner.card.reduce(
                (accRow, curRow) =>
                    accRow +
                    curRow
                        .filter((square) => !square.marked)
                        .map((s) => s.value)
                        .reduce((acc, cur) => acc + cur, 0),
                0
            );

            console.log(unmarkedSum * n);

            return false;
        }

        return true;
    });
});
