import { readFileSync } from "fs";

const data = readFileSync("./input.txt", "utf8");
const forestMap = data
  .split("\n")
  .map((line) => Array.from(line.replace(new RegExp("[\r]"), "")));
const lineLength: number = forestMap[0].length;
const mapLength: number = forestMap.length;

const slope = (moveX: number, moveY: number): number => {
  let trees: number = 0;
  let posX: number = 0;
  let posY: number = 0;

  while (posY < mapLength) {
    if (forestMap[posY][posX] === "#") trees++;
    posY += moveY;
    posX = (posX + moveX) % lineLength;
  }

  return trees;
};

console.log(
  slope(1, 1) * slope(3, 1) * slope(5, 1) * slope(7, 1) * slope(1, 2)
);
