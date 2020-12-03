import fs from 'fs';

const data: number[] = fs.readFileSync(__dirname + '/data-1.txt', 'utf8').split('\n').map((value) => Number(value));

console.log(data);

const findSumOfTwoElements = (data: number[], target: number = 2020): [number, number] => {
    return data.reduce((acc: [number, number], value, _, data) => data.includes(target - value) ? [value, target - value] : acc, [-1, -1]);
}

const findSumOfThreeElements = (data: number[], target: number = 2020): [number, number, number] => {
    return data.reduce((acc: [number, number, number], value, _, data) => {
        const [a, b] = findSumOfTwoElements(data, target - value);
        if (value > 0 && a != -1) {
            return [value, a, b];
        }
        return acc;
    }, [-1, -1, -1]);
};

const [a, b] = findSumOfTwoElements(data, 2020);

console.log(a + b, a * b);

const [d, e, f] = findSumOfThreeElements(data, 2020);

console.log(d + e + f, d * e * f);