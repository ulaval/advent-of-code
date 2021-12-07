export function countLanternfishAfterDays(
  input: number[],
  days: number = 256,
  timerNewFish = 8,
  timerFishAfterDuplicate = 6
): string {
  let timers: number[] = [];
  for (let i = 0; i <= timerNewFish; i++) {
    timers[i] = 0;
  }
  for (let i = 0; i < input.length; i++) {
    timers[input[i]]++;
  }
  for (let day = 0; day < days; day++) {
    const timersEnding = timers[0];
    for (let i = 1; i <= timerNewFish; i++) {
      timers[i - 1] = timers[i];
    }
    timers[timerNewFish] = timersEnding;
    timers[timerFishAfterDuplicate] += timersEnding;
  }

  return timers.reduce((acc, curr) => curr + acc, 0).toString();
}
