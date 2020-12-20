// https://github.com/simardo/adventofcode2020/tree/main/src/19

console.log('19 décembre');

type Rule = {
    index: number;
    char: string | undefined;
    refs: number[][] | undefined;
    loop?: boolean;
}

// part 1
function doPart1(input: string): void {
    const [rulesRaw, messages] = input.split('\n\n');

    const rules: { [key: number]: Rule } = {};

    rulesRaw.split('\n').forEach(r => {
        const index: number = Number.parseInt(r.substr(0, r.indexOf(':')));
        let char: string | undefined;
        let refs: number[][] | undefined;
        if (r.indexOf('"') >= 0) {
            const [, ch] = r.match(/\"(\w)\"/)!
            char = ch;
        } else {
            refs = r.substr(r.indexOf(':') + 2).split('|').map(r => r.trim().split(' ').map(rr => Number.parseInt(rr)));
        }
        rules[index] = {
            index: index,
            char: char,
            refs: refs
        }
    });

    const compute = (x: number, v: string[], lvl: number, msg: string) => {
        const rule = rules[x];
        if (rule.char !== undefined) {
            v.push(rule.char);
            return msg.indexOf(v.join('')) === 0;
        } else {
            const len: number = v.length;
            const some: boolean = rule.refs!.some(vr => {
                const len2: number = v.length;
                const all: boolean = vr.every(vrv => compute(vrv, v, lvl + 1, msg));
                if (!all) {
                    while (v.length > len2) {
                        v.pop();
                    }
                }
                return all;
            });
            if (!some) {
                while (v.length > len) {
                    v.pop();
                }
            }
            return some;
        }
    }

    const validate = (message: string) => {
        const r0: Rule = rules[0];
        const p: string[] = [];
        const all: boolean = r0.refs![0].every(r => compute(r, p, 1, message));

        return all && p.length === message.length;
    }

    const r = messages.split('\n').reduce((v, m) => validate(m) ? v + 1 : v, 0);
    console.log(r);
}

doPart1(INPUT_1);

// part 2
function doPart2(input: string): void {
    const [rulesRaw, messages] = input.split('\n\n');

    const rules: { [key: number]: Rule } = {};

    rulesRaw.split('\n').forEach(r => {
        const index: number = Number.parseInt(r.substr(0, r.indexOf(':')));
        let char: string | undefined;
        let refs: number[][] | undefined;
        if (r.indexOf('"') >= 0) {
            const [, ch] = r.match(/\"(\w)\"/)!
            char = ch;
        } else {
            refs = r.substr(r.indexOf(':') + 2).split('|').map(r => r.trim().split(' ').map(rr => Number.parseInt(rr)));
        }
        rules[index] = {
            index: index,
            char: char,
            refs: refs,
            loop: refs && refs.some(r => r.indexOf(index) >= 0)
        }
    });

    const compute = (x: number, v: string[], lvl: number, msg: string, iter: number) => {
        const rule = rules[x];
        if (rule.char !== undefined) {
            v.push(rule.char);
            return msg.indexOf(v.join('')) === 0;
        } else {
            let len: number = v.length;

            let some: boolean;
            let loopCount: number = 0;
            if (rule.loop) {
                some = false;
                let some2: boolean = false;
                do {
                    ++loopCount;
                    len = v.length;
                    some2 = rule.refs!.some(vr => {
                        const ll: number = v.length;
                        const all: boolean = vr.every(vrv => compute(vrv, v, lvl + 1, msg, iter));
                        if (!all) {
                            while (v.length > ll) {
                                v.pop();
                            }
                        }
                        return all;
                    });
                    some = some || some2;
                } while (some2 && ((rule.index === 8 && loopCount < iter)));
            } else {
                some = rule.refs!.some(vr => {
                    const len2: number = v.length;
                    const all: boolean = vr.every(vrv => compute(vrv, v, lvl + 1, msg, iter));
                    if (!all) {
                        while (v.length > len2) {
                            v.pop();
                        }
                    }
                    return all;
                });
            }
            if (!some) {
                while (v.length > len) {
                    v.pop();
                }
            }
            return some;
        }
    }

    const validate = (message: string) => {
        const r0: Rule = rules[0];
        let iter: number = 6; // ajouter tant qu'on trouve des résultats additionnels
        let all: boolean;
        let p: string[] = [];
        do {
            p = [];
            --iter;
            all = r0.refs![0].every(r => compute(r, p, 1, message, iter));
        } while (!(all && p.length === message.length) && iter > 0);

        return all && p.length === message.length;
    }

    const r = messages.split('\n').reduce((v, m) => validate(m) ? v + 1 : v, 0);
    console.log(r);
}

doPart2(INPUT_2);
