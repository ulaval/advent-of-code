import { printResults } from "./print-results.js";

const day01P1 = (async() => {
    const response = await fetch('data.txt');
    const text = await response.text();
    const binaryNumbers = text.split('\r\n');

    const powerConsumptionDiagnostic = [...binaryNumbers[0]].reduce((acc, curr, index, array) => {
        const positiveNumber = binaryNumbers.filter(b => b[index] === '1').length;
        const hasMorePositiveNumber = positiveNumber > binaryNumbers.length - positiveNumber;
        acc.gamaRate.binary += hasMorePositiveNumber ? '1': '0';
        acc.epsilonRate.binary += hasMorePositiveNumber ? '0': '1';
        if (index === array.length - 1) {
            acc.gamaRate.decimal = parseInt(acc.gamaRate.binary, 2);
            acc.epsilonRate.decimal = parseInt(acc.epsilonRate.binary, 2);
            acc.powerConsumtion = acc.gamaRate.decimal * acc.epsilonRate.decimal
        }
        return acc;
    }, { gamaRate: { binary: '', decimal: 0 }, epsilonRate: { binary: '', decimal: 0 },  powerConsumtion: 0});

    console.log(powerConsumptionDiagnostic.powerConsumtion);
    printResults(1, powerConsumptionDiagnostic);
})();