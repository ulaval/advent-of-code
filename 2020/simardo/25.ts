// https://github.com/simardo/adventofcode2020/tree/main/src/25

console.log('25 décembre');

// part 1
function doPart1(pkc: number, pkd: number): void {

    const computeLoop: (pk: number) => number = pk => {
        let k: number = 1;
        let loop: number = 0;
        do {
            loop++;
            k *= 7;
            k = k % 20201227;
        } while (k !== pk);
        return loop;
    };

    const computeEncryptionKey: (sn: number, loop: number) => number = (sn, loop) => {
        let k: number = 1;
        for (let i: number = 1; i <= loop; i++) {
            k *= sn;
            k = k % 20201227;
        }
        return k;
    };

    const cardLoop: number = computeLoop(pkc);
    const doorLoop: number = computeLoop(pkd);

    const ekd: number = computeEncryptionKey(pkd, cardLoop);
    const ekc: number = computeEncryptionKey(pkc, doorLoop);

    console.log(ekd, ekc);
}

doPart1(17115212, 3667832);
