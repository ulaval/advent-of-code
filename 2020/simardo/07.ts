// https://github.com/simardo/adventofcode2020/tree/main/src/07

console.log('7 décembre');

const mainRx: RegExp = /(.+)?\sbags contain\s(.+)?/g;
const contentRx: RegExp = /(\d+)\s(.+)\sbag[s]?/;

type Bags = { [key: string]: Bag };
type Bag = {
    color: string,
    content?: [string, number][]
}

function buildBags(input: string): Bags {
    let match: RegExpMatchArray | null;

    const bags: Bags = {};

    while ((match = mainRx.exec(input)) !== null) {
        let [, bag, content] = match;

        const b: Bag = {
            color: bag
        }

        content = content.substr(0, content.length - 1);
        if (content !== 'no other bags') {
            const cinfo: [string, number][] = content.split(',').map(s => {
                const [, qty, color] = s.trim().match(contentRx)!;
                return [color, Number.parseInt(qty)];
            });
            b.content = cinfo;
        }
        bags[bag] = b;
    }

    return bags;
}

// part 1
function doPart1(input: string): void {
    const bags: Bags = buildBags(input);

    const hasShinyBag: (b: Bag) => boolean =
        b => b.content !== undefined && (b.content.find(f => f[0] === 'shiny gold') !== undefined || b.content!.some(bb => hasShinyBag(bags[bb[0]])));

    const r: number = Object.values(bags).reduce((a, b) => hasShinyBag(b) ? a + 1 : a, 0);

    console.log(r);
}

doPart1(INPUT);

// part 2
function doPart2(input: string): void {
    const bags: Bags = buildBags(input);

    const contains: (b: Bag) => number = b => b.content !== undefined ? b.content.reduce((a,bb) => a + (bb[1] + bb[1] * contains(bags[bb[0]])), 0) : 0;

    console.log(contains(bags['shiny gold']));
}

doPart2(INPUT);
