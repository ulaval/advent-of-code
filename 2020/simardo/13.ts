// https://github.com/simardo/adventofcode2020/tree/main/src/13

console.log('13 décembre');

// part 1
function doPart1(input: string): void {
    const a: string[] = input.split('\n');

    const exp: number = Number.parseInt(a[0]);
    const bus: number[] = a[1].split(',').map(b => Number.parseInt(b));

    const r = bus.reduce((s, b) => {
        let [id, time] = s;
        if (!Number.isNaN(b)) {
            const t: number = exp + (b - exp % b);
            if (t < time) {
                id = b;
                time = t;
            }
        }
        return [id, time];
    }, [Number.MAX_VALUE, Number.MAX_VALUE]);

    console.log((r[1] - exp) * r[0])
}

doPart1(INPUT);

// part 2
function doPart2(input: string): void {
    const a: string[] = input.split('\n');

    const bus: [number, number, number][] = a[1].split(',').map((b, i) => [Number.parseInt(b), i, Number.parseInt(b)]);

    const filter = bus.filter(b => !Number.isNaN(b[0]));
    let x: number = 1;
    let start: number = 0;

    filter.forEach(f => {
        while ((f[1] + start) % f[0] !== 0) {
            start += x;
        }
        x *= f[0];
    });

    console.log(start);
}

doPart2(INPUT);
