// https://github.com/simardo/adventofcode2020/tree/main/src/23

console.log('23 décembre');

type Cup = [number, Cup | undefined];

// part 1 & part 2
function doPart12(labelsInit: number[], moves: number, part2: boolean): void {
    const lowest: number = Math.min(...labelsInit);
    let highest: number = Math.max(...labelsInit);

    if (part2) {
        while (highest < 1000000) {
            labelsInit.push(++highest);
        }
    }

    const labels: number[] = labelsInit;

    const cups: { [key: number]: Cup } = {};

    let currentCup: Cup = undefined!;
    labels.slice().reverse().forEach(c => {
        const [lbl, next]: Cup = [c, currentCup];
        cups[c] = [lbl, next];
        currentCup = cups[c];
    });

    cups[labels[labels.length - 1]][1] = cups[labels[0]];

    let move: number = 0;
    while (move++ < moves) {
        let [, curNext] = currentCup;
        const pick: Cup = curNext!;

        let i: number = 0;

        const pickValues: Set<number> = new Set();
        let pickNext: Cup = pick;
        while (i++ < 3) {
            curNext = curNext![1];
            pickValues.add(pickNext[0]);
            if (i < 3) {
                pickNext = pickNext[1]!;
            } else {
                pickNext[1] = undefined;
            }
        }

        currentCup[1] = curNext;

        let destination: number = currentCup[0];
        do {
            destination--;
            if (destination < lowest) {
                destination = highest;
            }
        }
        while (pickValues.has(destination));

        const destCup: Cup = cups[destination];
        pickNext[1] = destCup[1];
        destCup[1] = pick;

        currentCup = currentCup[1]!;
    }

    if (!part2) {
        const result: number[] = [];
        let cup: Cup = cups[1][1]!;
        while (cup !== cups[1]) {
            result.push(cup[0]);
            cup = cup[1]!;
        }
        console.log(result.join(''));
    } else {
        const cup1: Cup = cups[1][1]!;
        const cup2: Cup = cup1[1]!;
        console.log(cup1[0] * cup2[0]);
    }
}

doPart12([...'598162734'].map(n => Number.parseInt(n)), 100, false);
doPart12([...'598162734'].map(n => Number.parseInt(n)), 10000000, true);
