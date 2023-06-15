import calcMethod from "./Minimization/calcMethod.js";
import getImplicants from "./Minimization/getImplicants.js";

export default function adder(variableMap, funcType) {
    variableMap.forEach((map) => {
        let sum = Array.from(map.values()).reduce((sum, cur) => sum + cur);
        if (sum === 3) {
            map.set('sum', 1);
            map.set('over', 1);
        } else if (sum === 2) {
            map.set('sum', 0);
            map.set('over', 1);
        } else {
            map.set('sum', sum);
            map.set('over', 0);
        }
    });
    console.log(variableMap);

    let typeValue = 1;
    let inSign = '*';
    let outSign = '+';
    if (funcType === 'sknf') {
        typeValue = 0;
        [inSign, outSign] = [outSign, inSign];
    }

    const results = ['sum', 'over'].map((resultType) => {
        let func = '';
        variableMap.forEach((map) => {
            if (map.get(resultType) === typeValue) {
                let group = '(';
                map.forEach((value, key) => {
                    if (['sum', 'over'].includes(key)) return;
                    if (value !== typeValue) group += '!' + key;
                    else group += key;
                    group += inSign;
                });
                group = group.slice(0, -1) + ')';
                func += group + outSign;
            }
        });
        return func.slice(0, -1);
    });

    const variables = Array.from(variableMap[0].keys()).slice(0, -2);
    let implicants = [
        getImplicants(variables, results[0]),
        getImplicants(variables, results[1])
    ];
    variableMap.forEach((map) => {
        map.forEach((value, key) => {
            if (!variables.includes(key)) map.delete(key);
        });
    });

    return implicants.map((arr, index) => {
        if (variables.every(variable => arr[0].includes(variable))) return results[index];
        return calcMethod(arr, 'sdnf', variableMap);
    });
}