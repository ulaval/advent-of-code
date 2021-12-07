export function countDepthIncreases(inputs: Array<number>): string {
  let increasesCount = 0;
  for (let i = 1; i < inputs.length; i++) {
    if (inputs[i] > inputs[i - 1]) {
      increasesCount += 1;
    }
  }
  return increasesCount.toString();
}

export function countSlidingWindowDepthIncreases(
  inputs: Array<number>,
  slidingWindowMeasurement: number = 3
): string {
  let slidingWindowSums: Array<number> = [];
  const maxIndex = inputs.length - (slidingWindowMeasurement - 1);
  for (let i = 0; i <= maxIndex; i++) {
    let value = 0;
    for (let j = i; j < slidingWindowMeasurement + i; j++) {
      value += inputs[j];
    }
    slidingWindowSums.push(value);
  }
  return countDepthIncreases(slidingWindowSums).toString();
}
