console.log('18 décembre');

type OperStack = [number[], OpFn | undefined];
type OpFn = (a: number, b: number) => number;

// part 1
function doPart1(input: string): void {
    const operations: string[] = input.split('\n').map(s => s.replaceAll(' ', ''));

    const add: OpFn = (a, b) => a + b;
    const mul: OpFn = (a, b) => a * b;

    const compute: (n: number, stack: OperStack) => void = (n, stack) => {
        let [stackNum, op] = stack;
        if (stackNum.length === 0) {
            stackNum.push(n);
        } else {
            stackNum.push(op!(stackNum.pop()!, n));
        }
        stack = [stackNum, op];
    }

    const r = operations.reduce((a, oper) => {
        const stacks: [number[], OpFn | undefined][] = [];

        stacks.push([[], undefined]);
        let curStack: number = 0;

        [...oper].forEach(instr => {
            let [stackNum, op] = stacks[curStack];
            if (instr === '+') {
                op = add;
                stacks[curStack] = [stackNum, op];
            } else if (instr === '*') {
                op = mul;
                stacks[curStack] = [stackNum, op];
            } else if (instr === '(') {
                stacks.push([[], undefined]);
                curStack++;
            } else if (instr === ')') {
                const [stack] = stacks.pop()!;
                curStack--;
                compute(stack[0], stacks[curStack]);
            } else {
                compute(Number.parseInt(instr), stacks[curStack]);
            }
        });

        return a + stacks[0][0][0];
    }, 0);

    console.log(r);
}

doPart1(INPUT);

// part 2
function doPart2(input: string): void {
    const operations: string[] = input.split('\n').map(s => s.replaceAll(' ', ''));

    const add: OpFn = (a, b) => a + b;

    const compute: (n: number, stack: OperStack) => void = (n, stack) => {
        let [stackNum, op] = stack;
        if (op === undefined) {
            stackNum.push(n);
        } else {
            stackNum.push(op!(stackNum.pop()!, n));
        }
        stack = [stackNum, op];
    }

    const r = operations.reduce((a, oper) => {
        const stacks: [number[], OpFn | undefined][] = [];

        stacks.push([[], undefined]);
        let curStack: number = 0;

        [...oper].forEach(instr => {
            let [stackNum, op] = stacks[curStack];
            if (instr === '+') {
                op = add;
                stacks[curStack] = [stackNum, op];
            } else if (instr === '*') {
                op = undefined;
                stacks[curStack] = [stackNum, op];
            } else if (instr === '(') {
                stacks.push([[], undefined]);
                curStack++;
            } else if (instr === ')') {
                const [stack] = stacks.pop()!;
                curStack--;
                compute(stack.reduce((a, n) => a * n, 1), stacks[curStack]);
            } else {
                compute(Number.parseInt(instr), stacks[curStack]);
            }
        });

        return a + stacks[0][0].reduce((a, n) => a * n, 1);
    }, 0);

    console.log(r);
}

doPart2(INPUT);