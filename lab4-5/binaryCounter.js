import getImplicants from "./Minimization/getImplicants.js";
import { allowedVariables } from "./config.js";

export default function binaryCounter(outputsCount) {

    const transitionTable = {
        'q': [[0], [0], [0]],
        'V': [0],
        'Q': [[0], [0], [0]],
        'h': [[0], [0], [0]]
    };

    let nextq;
    for (let transitionIndex = 1; transitionIndex < outputsCount**2; transitionIndex++) {
        if (transitionTable.V[transitionIndex - 1] == 0) {
            transitionTable.V.push(1);
            transitionTable.q.forEach(q => q.push(q[transitionIndex - 1]));
            transitionTable.Q.forEach(Q => Q.push(Q[transitionIndex - 1]));
            let cur = transitionTable.q.map(q => q[transitionIndex - 1]);
            nextq = sum(cur, [0, 0, 1]);
            cur.forEach((elem, index) => {
                if (elem !== nextq[index]) transitionTable.h[index].push(1);
                else transitionTable.h[index].push(0);
            });
        } else {
            transitionTable.V.push(0);
            nextq.forEach((elem, index) => {
                transitionTable.q[index].push(elem);
                transitionTable.Q[index].push(elem);
            });
            transitionTable.h.forEach(h => h.push(0));
        }
    }
    printTransitionTable(transitionTable);

    const sdnfs = [];
    transitionTable.h.forEach(h => {
        let sdnf = [];
        h.forEach((value, index) => {
            if (value == 1) {
                let constituent = '';
                transitionTable.q.forEach((q, qIndex) => {
                    if (q[index] == 0) constituent += '!';
                    constituent += allowedVariables[qIndex] + '*';
                });
                if (transitionTable.V[index] == 0) constituent += '!';
                constituent += 'V';
                sdnf.push(constituent);
            }
        });
        sdnfs.push(getImplicants(['A', 'B', 'C', 'V'], '(' + sdnf.join(')+(') + ')'));
    });
    console.log(sdnfs);
}

function sum(num1, num2) {
    if (num1.length < num2.length) [num1, num2] = [num2, num1];
    while (num1.length !== num2.length) num2.unshift(0);
    let result = [];
    let reminder = 0;
    for (let i = num1.length - 1; i >= 0; i--) {
        let sum = num1[i] + num2[i] + reminder;
        if (sum <= 1) {
            result.unshift(sum);
            reminder = 0;
        } else if (sum === 2) {
            result.unshift(0);
            reminder = 1;
        } else if (sum === 3) {
            result.unshift(1);
        }
    } return result;
}

function printTransitionTable(transitionTable) {
    console.log('q1 ', 'q2 ', 'q3 ', 'V  ', 'Q1 ', 'Q2 ', 'Q3 ', 'h1 ', 'h2 ', 'h3 ');
    for (let i = 0; i < transitionTable.q[0].length; i++) {
        console.log(
            transitionTable.q[0][i], ' ', transitionTable.q[1][i], ' ', transitionTable.q[2][i], ' ',
            transitionTable.V[i], ' ',
            transitionTable.Q[0][i], ' ', transitionTable.Q[1][i], ' ', transitionTable.Q[2][i], ' ',
            transitionTable.h[0][i], ' ', transitionTable.h[1][i], ' ', transitionTable.h[2][i]
        );
    }
}