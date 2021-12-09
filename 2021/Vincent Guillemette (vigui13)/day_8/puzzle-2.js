const convertInput = require('../input-converter');

convertInput(__dirname, (x) =>
    x.split('|').map((x) => x.split(' ').filter((x) => !!x))
).then((input) => {
    let sum = 0;

    input.forEach((i) => {
        const [patterns, output] = i;
        const one = patterns.find((p) => p.length === 2);
        const seven = patterns.find((p) => p.length === 3);
        const four = patterns.find((p) => p.length === 4);
        const height = patterns.find((p) => p.length === 7);
        const three = patterns.find(
            (p) =>
                p.length === 5 &&
                one.split('').every((l) => p.split('').includes(l))
        );
        const top = seven.split('').find((l) => !one.includes(l));
        const topLeft = four
            .split('')
            .find(
                (f) =>
                    !one.split('').includes(f) && !three.split('').includes(f)
            );
        const middle = four
            .split('')
            .find((f) => !one.split('').includes(f) && f !== topLeft);
        const five = patterns.find(
            (p) =>
                p.length === 5 &&
                p.includes(topLeft) &&
                !one.split('').every((o) => p.includes(o))
        );
        const bottomRight = one
            .split('')
            .find((o) => five.split('').includes(o));
        const topRight =
            one.split('')[0] === bottomRight
                ? one.split('')[1]
                : one.split('')[0];
        const six = patterns.find(
            (p) => p.length === 6 && !p.includes(topRight)
        );
        const two = patterns.find(
            (p) =>
                p.length === 5 &&
                p.includes(topRight) &&
                !p.includes(bottomRight)
        );
        const nine = patterns.find(
            (p) =>
                p.length === 6 &&
                p.includes(topLeft) &&
                p.includes(topRight) &&
                p.includes(bottomRight) &&
                p.includes(middle)
        );
        const zero = patterns.find(
            (p) => p.length === 6 && !p.includes(middle)
        );

        // console.log('0', zero);
        // console.log('1', one);
        // console.log('2', two);
        // console.log('3', three);
        // console.log('4', four);
        // console.log('5', five);
        // console.log('6', six);
        // console.log('7', seven);
        // console.log('8', height);
        // console.log('9', nine);

        sum += parseInt(
            output.reduce((a, c) => {
                if (
                    c.split('').every((c) => zero.split('').includes(c)) &&
                    c.length === zero.length
                ) {
                    return a + '0';
                }
                if (
                    c.split('').every((c) => one.split('').includes(c)) &&
                    c.length === one.length
                ) {
                    return a + '1';
                }
                if (
                    c.split('').every((c) => two.split('').includes(c)) &&
                    c.length === two.length
                ) {
                    return a + '2';
                }
                if (
                    c.split('').every((c) => three.split('').includes(c)) &&
                    c.length === three.length
                ) {
                    return a + '3';
                }
                if (c.split('').every((c) => four.split('').includes(c))) {
                    return a + '4';
                }
                if (
                    c.split('').every((c) => five.split('').includes(c)) &&
                    c.length === five.length
                ) {
                    return a + '5';
                }
                if (
                    c.split('').every((c) => six.split('').includes(c)) &&
                    c.length === six.length
                ) {
                    return a + '6';
                }
                if (
                    c.split('').every((c) => seven.split('').includes(c)) &&
                    c.length === seven.length
                ) {
                    return a + '7';
                }
                if (
                    c.split('').every((c) => height.split('').includes(c)) &&
                    c.length === height.length
                ) {
                    return a + '8';
                }
                if (
                    c.split('').every((c) => nine.split('').includes(c)) &&
                    c.length === nine.length
                ) {
                    return a + '9';
                }
                return a;
            }, '')
        );
    });

    console.log(sum);
});
