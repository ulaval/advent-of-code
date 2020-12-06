import * as fs from 'fs';
import * as path from 'path';
import * as _ from 'lodash';

export const input = fs.readFileSync('input.txt', 'utf8').toString().replace(/\r\n/g, '\n');

export const groupAnswers = input.split('\n\n').map(groupAnswersInput => groupAnswersInput.split('\n').map(groupAnswersInput => groupAnswersInput.split('')));

export const groupAnswersFlattens = groupAnswers.map(groupAnswer => _.flatten(groupAnswer));

export const groupAnswersFlattenUniqs = groupAnswersFlattens.map(groupAnswersFlatten => _.uniq(groupAnswersFlatten));

// console.log(_.flatten(groupAnswersFlattenUniqs).length);
