import fs from 'fs';

type PasswordPolicy = [[number, number], string, string];

const passwords: PasswordPolicy[] = fs.readFileSync(__dirname + '/data-2.txt', 'utf8')
    .split('\n')
    .map((line: string) => line.split(' '))
    .map((parts: string[]) => {
        return [
            parts[0].split('-')
                .map(v => Number(v))
                .reduce((obj, value) => obj[0] === -1 ? [value, obj[1]] : [obj[0], value], [-1, -1]),
            parts[1].replace(':', ''),
            parts[2]
        ]
    });

function replaceAll(string: string, search: string, replace: string) {
    return string.split(search).join(replace);
}

const sledPasswordPolicyChecker = (passwords: PasswordPolicy[]) => {
    return passwords.reduce((sumPasswordValids: number, password: PasswordPolicy) => {

        const passwordWithoutLetter = replaceAll(password[2], password[1], '');
        const difference = password[2].length - passwordWithoutLetter.length;

        if (difference >= password[0][0] && difference <= password[0][1]) {
            sumPasswordValids += 1;
        }

        return sumPasswordValids

    }, 0)
};


const toboganPasswordPolicyChecker = (passwords: PasswordPolicy[]) => {
    return passwords.reduce((sumValidPasswords: number, password: PasswordPolicy) => {

        if ((password[2].charAt(password[0][0] - 1) === password[1]) !== (password[2].charAt(password[0][1] - 1) === password[1])) {
            sumValidPasswords += 1;
        }

        return sumValidPasswords
    }, 0);
}
console.log(sledPasswordPolicyChecker(passwords));
console.log(toboganPasswordPolicyChecker(passwords));
