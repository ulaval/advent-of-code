// https://github.com/simardo/adventofcode2020/tree/main/src/09

console.log('9 décembre');

// part 1
function doPart1(input: string, preamble: number): number {
    const nums: number[] = input.split('\n').map(n=> Number.parseInt(n));

    const result: number = nums.slice(preamble).find((n,i) => {
        const ref: number[] = nums.slice(i, i + preamble);

        return !ref.some((r, ii) => ref.find((rr, iii) => ii != iii && r + rr === n));
    })!;

    console.log(result);
    return result;
}

doPart1(TEST_1, 5);
doPart1(INPUT, 25);

function doPart2(input: string, preamble: number): void {
    const invalid: number = doPart1(input, preamble);

    const nums: number[] = input.split('\n').map(n=> Number.parseInt(n));
    nums.find((n, i) => {
        let sum: number = 0;
        let min: number = Number.MAX_VALUE;
        let max: number = 0;
        let ii: number = i;
        while (sum < invalid && ii < nums.length) {
            sum += nums[ii];
            min = Math.min(min, nums[ii]);
            max = Math.max(max, nums[ii]);
            ii++;
        }
        if (sum === invalid) {
            console.log(min + max);
        }
        return sum === invalid;
    });
}

doPart2(TEST_1, 5);
doPart2(INPUT, 25);