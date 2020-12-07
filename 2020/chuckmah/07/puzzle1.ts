import * as fs from 'fs';
import * as path from 'path';
import * as _ from 'lodash';

export const input = fs.readFileSync('input.txt', 'utf8').toString().replace(/\r\n/g, '\n');




// console.log(rules[3]);
// console.log(rules[3].split('contain')[0].replace('bags', '').trim());
// let contain = rules[3].split('contain')[1].split(',')[0].trim();
// console.log(contain.substring(0, contain.lastIndexOf("bag")));
// let containText = contain.substring(0, contain.lastIndexOf("bag")).trim();
// console.log(containText.substring(0, containText.indexOf(' ')).trim());
// console.log(containText.substring(containText.indexOf(' ') + 1).trim());

export interface RuleContain {
    type: string
    quantity: number
}

export interface Rule {
    name: string
    contains: RuleContain[]
}

export interface Rules {
    [name: string]: Rule
}

export const parseRule = (ruleText: string): Rule => {
    const name = ruleText.split('contain')[0].replace('bags', '').trim();
    const containsTexts = ruleText.split('contain')[1].split(',');

    let contains: RuleContain[] = [];
    if (!containsTexts[0].includes('no other')) {
        contains = containsTexts.map(_containsText => {
            //remove the part bagXX
            let containsText = _containsText.trim().substring(0, _containsText.lastIndexOf("bag") - 1).trim();
            //get the type & quantity
            return {
                type: containsText.substring(containsText.indexOf(' ') + 1).trim(),
                quantity: Number(containsText.substring(0, containsText.indexOf(' ')).trim())
            }

        });
    }

    return {
        name: name,
        contains: contains
    };
}



export const rulesTexts = input.split('\n');


export const parseRules = (): Rules => {
    const rules: Rules = {};
    rulesTexts.forEach(rulesText => {
        const parsedRule = parseRule(rulesText);
        rules[parsedRule.name] = parsedRule;
    })
    return rules;
}


// console.log(rulesTexts.length);
// console.log(Object.keys(parseRules()).length);
// console.log(JSON.stringify(parseRules()['muted blue']));



export const findNumberOfBag = (bagName: string): number => {

    let parsedRules: Rules = parseRules();
    let result = 0;
    Object.keys(parsedRules).forEach(parsedRuleName => {
        // pour chaque parsedRuleName visiter toute les regles a savoir si on trouve un bagName
        let rule: Rule = parsedRules[parsedRuleName];
        if (rule.name !== bagName) {
            if (findBagInRule(bagName, rule, parsedRules)) {
                result++;
            }
        }
    })
    return result;
}


export const findBagInRule = (bagName: string, rule: Rule, parsedRules: Rules): boolean => {
    if (bagName === rule.name) {
        // si la regle actuel est bagName ca veut dire quon a trouver
        return true;
    } else {
        // sinon on doit visite tout les contains
        if (rule.contains.length > 0) {
            let isFound = false;
            rule.contains.forEach(contain => {

                if (findBagInRule(bagName, parsedRules[contain.type], parsedRules)) {
                    isFound = true;
                }
            });
            return isFound;
        } else {
            return false;
        }
    }
}

// console.log(findNumberOfBag('shiny gold'));