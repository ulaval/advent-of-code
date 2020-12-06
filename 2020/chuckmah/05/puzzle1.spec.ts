import { getRow, getComlumn, getSeatId } from './puzzle1';

test('FBFBBFFRLR should return row 44', () => {
  expect(getRow('FBFBBFFRLR')).toBe(44);
})


test('BFFFBBFRRR should return row 70', () => {
  expect(getRow('BFFFBBFRRR')).toBe(70);
})

test('FFFBBBFRRR should return row 14', () => {
  expect(getRow('FFFBBBFRRR')).toBe(14);
})

test('BBFFBBFRLL should return row 102', () => {
  expect(getRow('BBFFBBFRLL')).toBe(102);
})

test('FBFBBFFRLR should return column 5', () => {
  expect(getComlumn('FBFBBFFRLR')).toBe(5);
})

test('BFFFBBFRRR should return column 7', () => {
  expect(getComlumn('BFFFBBFRRR')).toBe(7);
})

test('FFFBBBFRRR should return column 7', () => {
  expect(getComlumn('FFFBBBFRRR')).toBe(7);
})

test('BBFFBBFRLL should return column 7', () => {
  expect(getComlumn('BBFFBBFRLL')).toBe(4);
})

test('BFFFBBFRRR should return seatId 567', () => {
  expect(getSeatId(getRow('BFFFBBFRRR'), getComlumn('BFFFBBFRRR'))).toBe(567);
})