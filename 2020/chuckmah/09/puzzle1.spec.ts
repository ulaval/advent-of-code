import { findNumber } from "./puzzle1";

const input = [
    35,
    20,
    15,
    25,
    47,
    40,
    62,
    55,
    65,
    95,
    102,
    117,
    150,
    182,
    127,
    219,
    299,
    277,
    309,
    576
]

test('given the input , correct output!', () => {
    expect(findNumber(input, 5)).toBe(127);
})
