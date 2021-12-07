export function getDepthMultipliedByHorizontalPosition(
  inputs: Array<[string, number]>
): string {
  let horizontalPosition = 0;
  let depth = 0;
  for (let i = 0; i < inputs.length; i++) {
    switch (inputs[i][0]) {
      case 'forward':
        horizontalPosition += inputs[i][1];
        break;
      case 'down':
        depth += inputs[i][1];
        break;
      case 'up':
        depth -= inputs[i][1];
        break;
    }
  }
  return (horizontalPosition * depth).toString();
}

export function getDepthMultipliedByHorizontalPositionWithAim(
  inputs: Array<[string, number]>
): string {
  let horizontalPosition = 0;
  let depth = 0;
  let aim = 0;
  for (let i = 0; i < inputs.length; i++) {
    switch (inputs[i][0]) {
      case 'forward':
        horizontalPosition += inputs[i][1];
        depth += aim * inputs[i][1];
        break;
      case 'down':
        aim += inputs[i][1];
        break;
      case 'up':
        aim -= inputs[i][1];
        break;
    }
  }
  return (horizontalPosition * depth).toString();
}
