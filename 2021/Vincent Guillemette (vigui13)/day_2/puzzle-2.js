const convertInput = require('../input-converter');

convertInput(__dirname, (x) => {
    const axis = x.split(' ')[0];
    const value = parseInt(x.split(' ')[1]);

    return {
        axis,
        value,
    };
}).then((nav) => {
    const trajectory = nav.reduce(
        (a, c) => {
            switch (c.axis) {
                case 'forward':
                    a.x += c.value;
                    a.y += a.aim * c.value;
                    break;
                case 'up':
                    a.aim -= c.value;
                    break;
                case 'down':
                    a.aim += c.value;
                    break;
            }

            return a;
        },
        { x: 0, y: 0, aim: 0 }
    );

    console.log(trajectory.x * trajectory.y);
});
