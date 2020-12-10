import fs from 'fs';

const boardingPasses: string[] = fs.readFileSync(__dirname + '/data-5.txt', 'utf8').split('\n')

const binaryToBase10 = (binary: string): number => {
    let value: number = 0;
    let index: number = 0;
    while (index < binary.length) {
        if (binary.charAt(index) === '1') {
            value += Math.pow(2, binary.length - index - 1);
        }
        index += 1;
    }

    return value;
}

const boardingPassCodeToBinary = (bordingPassCode: string): [string, string] => {
    const binaryCodeBoardingPass: string = bordingPassCode.replace(/F|L/g, '0')
        .replace(/B|R/g, '1');
    return [binaryCodeBoardingPass.substr(0, 7), binaryCodeBoardingPass.substr(7)];
}

const calculateId = (seat: number[]): number => {
    return seat[0] * 8 + seat[1];
}

const seatsIDs: number[] = boardingPasses.map(boardingPassCodeToBinary)
    .map((boardingPass: string[]) => boardingPass.map(binaryToBase10))
    .map(calculateId).sort((a, b) => a - b);

const lastId: number = Math.max(...seatsIDs);

console.log(lastId);

const mySeat: number = seatsIDs.reduce((missingSeatId: number, currentValue: number, index: number) => {
    if (index < 2 || missingSeatId !== - 1) { return missingSeatId; }
    if (seatsIDs[index - 1] !== currentValue - 1 && seatsIDs[index + 1] === currentValue + 1) {
        return currentValue - 1;
    }
    return missingSeatId;
}, -1);

console.log(mySeat);



