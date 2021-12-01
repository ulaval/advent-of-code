const SONAR_SWEEPS = [199, 200, 208, 210, 200, 207, 240, 269, 260, 263];

const largerMeasurements = SONAR_SWEEPS.reduce((acc, curr, index, array) => 
    array[!index ? 0 : index - 1] < curr ? acc + 1 : acc, 0);

console.log(largerMeasurements);
console.log(`There are ${largerMeasurements} measurements that are larger than the previous measurement.`);
