export function getPowerConsumption(
  input: string[],
  binaryLength: number = 12
): string {
  const gammaRate = getGammaRate(input, binaryLength);
  const epsilonRate = getEpsilonRate(gammaRate);
  return (
    binaryStringToNumber(gammaRate) * binaryStringToNumber(epsilonRate)
  ).toString();
}

export function getLifeSupportRating(input: string[]): string {
  return (
    binaryStringToNumber(getOxygenGeneratorRating(input)) *
    binaryStringToNumber(getCO2ScrubberRating(input))
  ).toString();
}

function binaryStringToNumber(binaryString: string): number {
  return parseInt(binaryString, 2);
}

function getGammaRate(input: string[], binaryLength: number): string {
  let valuesCount = getValuesCount(input, binaryLength);
  let gammaRate: string = '';
  for (let i = 0; i < valuesCount.length; i++) {
    if (valuesCount[i] > input.length / 2) {
      gammaRate += '1';
    } else {
      gammaRate += '0';
    }
  }
  return gammaRate.toString();
}

function getValuesCountAtPosition(input: string[], position: number): number {
  let valuesCount: number = 0;
  for (let i = 0; i < input.length; i++) {
    valuesCount += +input[i][position];
  }
  return valuesCount;
}

function getValuesCount(input: string[], binaryLength: number): number[] {
  let valuesCount: number[] = [];
  for (let i = 0; i < binaryLength; i++) {
    valuesCount[i] = 0;
  }
  for (let i = 0; i < input.length; i++) {
    for (let j = 0; j < binaryLength; j++) {
      valuesCount[j] += +input[i][j];
    }
  }
  return valuesCount;
}
function getEpsilonRate(gammaRate: string): string {
  let epsilonRate: string = ' ';
  for (let i = 0; i < gammaRate.length; i++) {
    if (gammaRate[i] === '0') {
      epsilonRate += '1';
    } else {
      epsilonRate += '0';
    }
  }
  return epsilonRate;
}

function getOxygenGeneratorRating(inputs: string[]): string {
  let currentInputs: string[] = inputs;
  let currentPosition: number = 0;
  while (currentInputs.length > 1) {
    const mostCommonValue = getMostCommonValue(currentInputs, currentPosition);
    const constCurrentPosition = currentPosition;
    currentInputs = currentInputs.filter(
      (value) => value[constCurrentPosition] === mostCommonValue
    );
    currentPosition += 1;
  }
  return currentInputs[0];
}

function getCO2ScrubberRating(inputs: string[]): string {
  let currentInputs: string[] = inputs;
  let currentPosition: number = 0;
  while (currentInputs.length > 1) {
    const mostCommonValue = getMostCommonValue(currentInputs, currentPosition);
    const constCurrentPosition = currentPosition;
    currentInputs = currentInputs.filter(
      (value) => value[constCurrentPosition] !== mostCommonValue
    );
    currentPosition += 1;
  }
  return currentInputs[0];
}

function getMostCommonValue(inputs: string[], position: number): string {
  const valuesCountAtCurrentPosition: number = getValuesCountAtPosition(
    inputs,
    position
  );
  let currentFilteredValue: string = '0';
  if (valuesCountAtCurrentPosition >= inputs.length / 2) {
    currentFilteredValue = '1';
  }
  return currentFilteredValue;
}
